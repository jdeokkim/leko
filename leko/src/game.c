/*
    Copyright (c) 2022 jdeokkim

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "leko.h"

/* | `game` 모듈 매크로 정의... | */

#define BLOCK_SIZE           48

#define WIDTH_IN_BLOCKS      15
#define HEIGHT_IN_BLOCKS     14

#define MAX_ADJACENTS_COUNT  4

#define GRAVITY_CONSTANT     480.0f

/* | `game` 모듈 상수... | */

const float FADE_DURATION = 0.25f;

const float INVERSE_BLOCK_SIZE = 1.0f / BLOCK_SIZE;
const float INVERSE_FADE_DURATION = 1.0f / FADE_DURATION;

const Rectangle GRID_RECTANGLE = {
    .x = 260.0f,
    .y = 49.0f,
    .width = WIDTH_IN_BLOCKS * BLOCK_SIZE,
    .height = HEIGHT_IN_BLOCKS * BLOCK_SIZE
};

const Block EMPTY_BLOCK = { .type = BLT_EMPTY };

/* | `game` 모듈 변수... | */

static Block blocks[HEIGHT_IN_BLOCKS][WIDTH_IN_BLOCKS];

static Block *adjacents[MAX_ADJACENTS_COUNT];
static Block *selected_block;

static GameAsset *ast_blocks;
static GameAsset *ast_frame;

static int result = 0;

/* | `game` 모듈 함수... | */

/* 레벨 위치 `indexes`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair indexes, BlockType type);

/* 게임 플레이 화면에 블록을 그린다. */
static void DrawBlock(Block *block);

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block);

/* 블록 `block`이 마우스로 이동 가능한지 확인한다. */
static bool CanBeDragged(Block *block);

/* 블록 `block`의 화면 기준 경계 범위를 반환한다. */
static Rectangle GetBlockBounds(Block *block);

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetGridCoordinates(Vector2 v);

/* 블록 `block`의 X 좌표를 기준으로 마우스가 어느 방향에 있는지 확인한다. */
static int GetMouseDirection(Block *block);

/* 레벨 위치 `indexes`를 게임 화면의 위치로 변환한다. */
static Vector2 GetWorldCoordinates(CPair indexes);

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void);

/* 게임 플레이 화면을 초기화한다. */
void InitGameScreen(void) {
    ast_blocks = GetGameAsset(2);
    ast_frame = GetGameAsset(3);

    /* TODO: 레벨 불러오기 */
}

/* 게임 플레이 화면을 업데이트한다. */
void UpdateGameScreen(void) {
    ClearBackground(BLACK);

    DrawTextureV(
        ast_frame->data.texture,
        (Vector2) { 0.0f, 0.0f },
        WHITE
    );

    DrawLevel();
}

/* 게임 플레이 화면을 종료한다. */
int FinishGameScreen(void) {
    return result;
}

/* 레벨 위치 `indexes`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair indexes, BlockType type) {
    if (type == BLT_EMPTY || indexes.x > WIDTH_IN_BLOCKS - 1 
        || indexes.y > HEIGHT_IN_BLOCKS - 1) return;

    blocks[indexes.y][indexes.x] = (Block) {
        .type = type,
        .state = BLS_NORMAL,
        .position = GetWorldCoordinates(indexes)
    };
}

/* 게임 플레이 화면에 블록을 그린다. */
static void DrawBlock(Block *block) {
    if (block == NULL) return;

    DrawTextureRec(
        ast_blocks->data.texture,
        (Rectangle) {
            (block->type % 8) * BLOCK_SIZE,
            (block->type > BLT_COLOR_07) * BLOCK_SIZE,
            BLOCK_SIZE,
            BLOCK_SIZE
        },
        block->position,
        WHITE
    );

    if (CanBeDragged(block)) {
        DrawTextureRec(
            ast_blocks->data.texture,
            (Rectangle) {
                0.0f,
                2.0f * BLOCK_SIZE,
                BLOCK_SIZE,
                BLOCK_SIZE
            },
            block->position,
            WHITE
        );
    } else {
        if (block->state == BLS_DRAGGED) {
            DrawTextureRec(
                ast_blocks->data.texture,
                (Rectangle) {
                    BLOCK_SIZE,
                    2.0f * BLOCK_SIZE,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                },
                block->position,
                WHITE
            );
        }
    }
}

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block) {
    if (block == NULL || block->type < BLT_COLOR_01
        || block->type > BLT_COLOR_07) return;

    CPair indexes = GetGridCoordinates(block->position);

    switch (block->state) {
        case BLS_NORMAL:
            if (indexes.y < HEIGHT_IN_BLOCKS - 1) {
                Block *bottom = &blocks[indexes.y + 1][indexes.x];

                if (bottom->type == BLT_EMPTY || bottom->state == BLS_FALLING) {
                    block->state = BLS_FALLING;

                    break;
                }
            }

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CanBeDragged(block)) {
                block->state = BLS_DRAGGED;
                selected_block = block;
            }

            break;
        
        case BLS_MARKED:
            if (block->timer >= FADE_DURATION) {
                blocks[indexes.y][indexes.x] = EMPTY_BLOCK;

                break;
            } else {
                block->timer += GetFrameTime();

                DrawTextureRec(
                    ast_blocks->data.texture,
                    (Rectangle) {
                        (block->type % 8) * BLOCK_SIZE,
                        (block->type > BLT_COLOR_07) * BLOCK_SIZE,
                        BLOCK_SIZE,
                        BLOCK_SIZE
                    },
                    block->position,
                    Fade(WHITE, (1.0f - (block->timer * INVERSE_FADE_DURATION)))
                );
            }

            break;

        case BLS_DRAGGED:
            if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
                block->state = BLS_NORMAL;
                selected_block = NULL;

                break;
            }

            Block *left = (indexes.x >= 1)
                ? &blocks[indexes.y][indexes.x - 1]
                : NULL;

            Block *right = (indexes.x < WIDTH_IN_BLOCKS - 1)
                ? &blocks[indexes.y][indexes.x + 1]
                : NULL;

            Block *bottom = (indexes.y < HEIGHT_IN_BLOCKS - 1)
                ? &blocks[indexes.y + 1][indexes.x]
                : NULL;

            if (bottom != NULL && bottom->type == BLT_EMPTY) break;

            int direction = GetMouseDirection(block);

            if (direction < 0 && left != NULL && left->type == BLT_EMPTY) {
                block->position = GetWorldCoordinates((CPair) { indexes.x - 1, indexes.y });

                blocks[indexes.y][indexes.x - 1] = blocks[indexes.y][indexes.x];
                blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
            } else if (direction > 0 && right != NULL && right->type == BLT_EMPTY) {
                block->position = GetWorldCoordinates((CPair) { indexes.x + 1, indexes.y });

                blocks[indexes.y][indexes.x + 1] = blocks[indexes.y][indexes.x];
                blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
            }

            break;

        case BLS_FALLING:
            if (indexes.y >= HEIGHT_IN_BLOCKS - 1) {
                block->state = BLS_NORMAL;

                block->velocity.y = 0.0f;
                block->position = GetWorldCoordinates(indexes);
            } else {
                Block *bottom = &blocks[indexes.y + 1][indexes.x];

                if (bottom->type != BLT_EMPTY && bottom->state != BLS_FALLING) {
                    block->state = BLS_NORMAL;

                    block->velocity.y = 0.0f;
                    block->position = GetWorldCoordinates(indexes);

                    break;
                }

                const float dt = GetFrameTime();

                block->velocity.y += GRAVITY_CONSTANT * dt;
                block->position.y += block->velocity.y * dt;

                CPair new_indexes = GetGridCoordinates(block->position);

                if (indexes.y != new_indexes.y) {
                    blocks[new_indexes.y][new_indexes.x] = blocks[indexes.y][indexes.x];
                    blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
                }
            }

            break;

        default:
            break;
    }

    adjacents[0] = (indexes.y >= 1)? &blocks[indexes.y - 1][indexes.x] : NULL;
    adjacents[1] = (indexes.x >= 1) ? &blocks[indexes.y][indexes.x - 1] : NULL;
    adjacents[2] = (indexes.y < HEIGHT_IN_BLOCKS - 1)? &blocks[indexes.y + 1][indexes.x] : NULL;
    adjacents[3] = (indexes.x < WIDTH_IN_BLOCKS - 1) ? &blocks[indexes.y][indexes.x + 1] : NULL;

    for (int i = 0; i < MAX_ADJACENTS_COUNT; i++) {
        if (adjacents[i] != NULL && block->type == adjacents[i]->type
            && adjacents[i]->state == BLS_NORMAL) {
            block->state = adjacents[i]->state = BLS_MARKED;
        }
    }
}

/* 블록 `block`이 마우스로 이동 가능한지 확인한다. */
static bool CanBeDragged(Block *block) {
    if (selected_block != NULL) return false;

    return (block != NULL && block->type >= BLT_COLOR_01 
        && block->type <= BLT_COLOR_07 && block->state == BLS_NORMAL
        && CheckCollisionPointRec(GetMousePosition(), GetBlockBounds(block)));
}

/* 블록 `block`의 화면 기준 경계 범위를 반환한다. */
static Rectangle GetBlockBounds(Block *block) {
    return (Rectangle) {
        .x = block->position.x,
        .y = block->position.y,
        BLOCK_SIZE,
        BLOCK_SIZE
    };
}

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetGridCoordinates(Vector2 v) {
    return (CPair) {
        .x = (v.x - GRID_RECTANGLE.x) * INVERSE_BLOCK_SIZE,
        .y = (v.y - GRID_RECTANGLE.y) * INVERSE_BLOCK_SIZE
    };
}

/* 블록 `block`의 X 좌표를 기준으로 마우스가 어느 방향에 있는지 확인한다. */
static int GetMouseDirection(Block *block) {
    Rectangle bounds = GetBlockBounds(block);
    Vector2 position = GetMousePosition();

    if (position.x < bounds.x) return -1;
    else if (position.x >= bounds.x && position.x <= bounds.x + bounds.width) return 0;
    else return 1;
}

/* 레벨 위치 `indexes`를 게임 화면의 위치로 변환한다. */
static Vector2 GetWorldCoordinates(CPair indexes) {
    return (Vector2) {
        GRID_RECTANGLE.x + (indexes.x * BLOCK_SIZE),
        GRID_RECTANGLE.y + (indexes.y * BLOCK_SIZE)
    };
}

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void) {
    for (int y = 0; y < HEIGHT_IN_BLOCKS; y++) {
        for (int x = 0; x < WIDTH_IN_BLOCKS; x++) {
            UpdateBlock(&blocks[y][x]);

            if (blocks[y][x].state != BLS_MARKED)
                DrawBlock(&blocks[y][x]);

            Vector2 position = GetWorldCoordinates((CPair) { x, y });
        }
    }
}