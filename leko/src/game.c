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

#define BLOCK_SIZE        48

#define WIDTH_IN_BLOCKS   15
#define HEIGHT_IN_BLOCKS  14

/* | `game` 모듈 상수... | */

const float INVERSE_BLOCK_SIZE = 1.0f / BLOCK_SIZE;

const Rectangle GRID_RECTANGLE = {
    .x = 260.0f,
    .y = 49.0f,
    .width = WIDTH_IN_BLOCKS * BLOCK_SIZE,
    .height = HEIGHT_IN_BLOCKS * BLOCK_SIZE
};

/* | `game` 모듈 변수... | */

static Block blocks[HEIGHT_IN_BLOCKS][WIDTH_IN_BLOCKS];

static GameAsset *ast_blocks;
static GameAsset *ast_frame;

static int result = 0;

/* | `game` 모듈 함수... | */

/* 레벨 위치 `position`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair position, BlockType type);

/* 게임 플레이 화면에 블록을 그린다. */
static void DrawBlock(Block *block);

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block);

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetGridCoordinates(Vector2 v);

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void);

/* 게임 플레이 화면을 초기화한다. */
void InitGameScreen(void) {
    ast_blocks = GetGameAsset(2);
    ast_frame = GetGameAsset(3);
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

/* 레벨 위치 `position`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair position, BlockType type) {
    if (type == BLT_EMPTY || position.x > WIDTH_IN_BLOCKS - 1 
        || position.y > HEIGHT_IN_BLOCKS - 1) return;

    blocks[position.y][position.x] = (Block) {
        .type = type,
        .state = BLS_NORMAL,
        .position = (Vector2) {
            GRID_RECTANGLE.x + (position.x * BLOCK_SIZE),
            GRID_RECTANGLE.y + (position.y * BLOCK_SIZE)
        }
    };
}

/* 게임 플레이 화면에 블록을 그린다. */
static void DrawBlock(Block *block) {
    if (block == NULL || block->type == BLT_EMPTY) return;

    DrawTextureRec(
        ast_blocks->data.texture,
        (Rectangle) {
            ((block->type - 1) % 7) * BLOCK_SIZE,
            (block->type > BLT_COLOR_07) * BLOCK_SIZE,
            BLOCK_SIZE,
            BLOCK_SIZE
        },
        block->position,
        WHITE
    );
}

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block) {
    /* TODO: ... */
}

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetGridCoordinates(Vector2 v) {
    CPair result = {
        .x = (v.x - GRID_RECTANGLE.x) * INVERSE_BLOCK_SIZE,
        .y = (v.y - GRID_RECTANGLE.y) * INVERSE_BLOCK_SIZE
    };

    if (result.x < 0) result.x = 0;
    else if (result.x > WIDTH_IN_BLOCKS - 1) result.x = WIDTH_IN_BLOCKS - 1;

    if (result.y < 0) result.y = 0;
    else if (result.y > HEIGHT_IN_BLOCKS - 1) result.y = HEIGHT_IN_BLOCKS - 1;

    return result;
}

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void) {
    for (int y = 0; y < HEIGHT_IN_BLOCKS; y++) {
        for (int x = 0; x < WIDTH_IN_BLOCKS; x++) {
            UpdateBlock(&blocks[y][x]);
            
            DrawBlock(&blocks[y][x]);
        }
    }
}