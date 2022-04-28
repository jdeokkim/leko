/*
    Copyright (c) 2022 jdeokkim

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdlib.h>
#include <string.h>

#include "leko.h"
#include "levels.h"

/* | `game` 모듈 매크로 정의... | */

#define GRAVITY_CONSTANT          600.0f

#define MAX_ADJACENTS_COUNT       4
#define MAX_SCORES_COUNT          2

#define SIDEBAR_STATS_01_TEXT    "\xEC\x8B\x9C\xEA\xB0\x84:  %02d:%02d"
#define SIDEBAR_STATS_02_TEXT     "\xEC\xA0\x90\xEC\x88\x98: %05d"
#define SIDEBAR_STATS_03_TEXT     "\xEC\xB5\x9C\xEA\xB3\xA0: %05d"

#define SIDEBAR_PROGRESS_TEXT     "%02d / %02d"

#define SIDEBAR_MENU_BUTTON_TEXT  "\xEB\xA9\x94\xEB\x89\xB4"

#define GAME_MENU_BUTTON_01_TEXT  "\xEA\xB2\x8C\xEC\x9E\x84\x20\xEA\xB3\x84" \
                                  "\xEC\x86\x8D\xED\x95\x98\xEA\xB8\xB0"

#define GAME_MENU_BUTTON_02_TEXT  "\xEB\xA0\x88\xEB\xB2\xA8\x20\xEC\x84\xA0" \
                                  "\xED\x83\x9D\x20\xED\x99\x94\xEB\xA9\xB4"

#define GAME_MENU_BUTTON_03_TEXT  "\xED\x99\x98\xEA\xB2\xBD\x20\xEC\x84\xA4" \
                                  "\xEC\xA0\x95"

/* | `game` 모듈 자료형 정의... | */

/* `char` 데이터 2개를 나타내는 구조체. */
typedef struct CPair { 
    unsigned char x;
    unsigned char y; 
} CPair;

/* 블록을 나타내는 구조체. */
typedef struct Block {
    BlockType type;    // 블록의 종류
    BlockState state;  // 블록의 상태
    Vector2 position;  // 블록의 화면 기준 위치
    Vector2 velocity;  // 블록의 화면 기준 속도
    float timer;       // 시간 측정용 변수
} Block;

/* 게임의 레벨을 나타내는 구조체. */
typedef struct Level {
    Block blocks[LEVEL_HEIGHT_IN_BLOCKS][LEVEL_WIDTH_IN_BLOCKS];  // 블록 배열
    int goals[NORMAL_BLOCK_COUNT];                                // 레벨 클리어 목표
} Level;

/* 같은 종류의 블록의 모임을 나타내는 구조체. */
typedef struct Matches { 
    BlockType type; 
    int count; 
} Matches;

/* | `game` 모듈 상수... | */

const Rectangle LEVEL_BOUNDS = {
    .x = 260.0f,
    .y = 49.0f,
    .width = LEVEL_WIDTH_IN_BLOCKS * BLOCK_SIZE,
    .height = LEVEL_HEIGHT_IN_BLOCKS * BLOCK_SIZE
};

const Rectangle GAME_MENU_BUTTON_SOURCE = {
    .x = 0.0f,
    .y = 66.0f,
    .width = 266.0f,
    .height = 86.0f
};

const Rectangle GAME_MENU_BUTTON_01_DEST = {
    .x = 392.0f,
    .y = 264.0f,
    .width = 266.0f,
    .height = 86.0f
};

const Rectangle GAME_MENU_BUTTON_02_DEST = {
    .x = 392.0f,
    .y = 354.0f,
    .width = 266.0f,
    .height = 86.0f
};

const Rectangle GAME_MENU_BUTTON_03_DEST = {
    .x = 392.0f,
    .y = 444.0f,
    .width = 266.0f,
    .height = 86.0f
};

const Rectangle SIDEBAR_MENU_BUTTON_DEST = {
    .x = 78.0f,
    .y = 640.0f,
    .width = 146.0f,
    .height = 66.0f
};

const Rectangle SIDEBAR_PROG_BLOCK_BOUNDS[NORMAL_BLOCK_COUNT] = {
    { 90.0f, 292.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 342.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 392.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 442.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 492.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 542.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE },
    { 90.0f, 592.0f, 0.5f * BLOCK_SIZE, 0.5f * BLOCK_SIZE }
};

const Vector2 SIDEBAR_PROGRESS_TEXT_POSITIONS[NORMAL_BLOCK_COUNT] = {
    { 133.0f, 294.0f },
    { 133.0f, 344.0f },
    { 133.0f, 394.0f },
    { 133.0f, 444.0f },
    { 133.0f, 494.0f },
    { 133.0f, 544.0f },
    { 133.0f, 594.0f }
};

const Vector2 GAME_MENU_BUTTON_01_TEXT_OFFSET = { 436.0f, 286.0f };
const Vector2 GAME_MENU_BUTTON_02_TEXT_OFFSET = { 436.0f, 376.0f };
const Vector2 GAME_MENU_BUTTON_03_TEXT_OFFSET = { 466.0f, 466.0f };

const Vector2 SIDEBAR_MENU_BUTTON_TEXT_OFFSET = { 132.0f, 658.0f };

const Vector2 SIDEBAR_STATS_TEXT_POSITIONS[3] = {
    { 56.0f, 88.0f },
    { 56.0f, 141.0f },
    { 56.0f, 194.0f }
};

const Block EMPTY_BLOCK = { .type = BLT_EMPTY };

const double INVERSE_SIXTY = 1.0 / 60.0;

const float FADE_DURATION = 0.25f;

const float INVERSE_BLOCK_SIZE = 1.0f / BLOCK_SIZE;
const float INVERSE_FADE_DURATION = 1.0f / FADE_DURATION;

/* | `game` 모듈 변수... | */

static GameAsset *ast_font_16pt, *ast_font_24pt, *ast_font_32pt;
static GameAsset *ast_buttons, *ast_blocks, *ast_frame;
static GameAsset *ast_dragged, *ast_marked;

static GameSettings *settings;

static Level level;

static Block *adjacents[MAX_ADJACENTS_COUNT];
static Block *selected_block;

static Matches matches;

static bool gui_menu_overlay_visible, gui_settings_window_box_visible;

static double start_time, end_time;

static char *current_level = NULL;

static int progress[NORMAL_BLOCK_COUNT], scores[MAX_SCORES_COUNT];
static int result, state;

/* | `game` 모듈 함수... | */

/* 레벨 위치 `indexes`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair indexes, BlockType type);

/* 블록 `block`이 마우스로 이동 가능한지 확인한다. */
static bool CanBeDragged(Block *block);

/* 게임 플레이 화면에 블록을 그린다. */
static void DrawBlock(Block *block);

/* 블록 `block`의 화면 기준 경계 범위를 반환한다. */
static Rectangle GetBlockBounds(Block *block);

/* 블록 `block`이 일반 블록인지 확인한다. */
static bool IsNormalBlock(Block *block);

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block);

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetLevelCoordinates(Vector2 v);

/* 레벨 위치 `indexes`를 게임 화면의 위치로 변환한다. */
static Vector2 GetWorldCoordinates(CPair indexes);

/* 블록 `block`의 X 좌표를 기준으로 마우스가 어느 방향에 있는지 확인한다. */
static int GetMouseDirection(Block *block);

/* 현재 레벨의 클리어 여부를 확인한다. */
static bool IsLevelCompleted(void);

/* 사용자의 키보드 입력을 처리한다. */
static void HandleKeyEvents(void);

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void);

/* 게임 플레이 화면에 사이드바 구성 요소를 그린다. */
static void DrawSidebar(void);

/* 레벨 문자열 `str`을 통해 레벨을 불러온다. */
void LoadLevel(const char *str) {
    static char buffer[MAX_LVSTR_LENGTH], *token;

    strncpy(buffer, str, MAX_LVSTR_LENGTH);

    token = strtok(buffer, ",");

    // 현재 레벨의 블록 배열을 초기화한다.
    for (int y = 0; y < LEVEL_HEIGHT_IN_BLOCKS; y++)
        for (int x = 0; x < LEVEL_WIDTH_IN_BLOCKS; x++)
            level.blocks[y][x] = EMPTY_BLOCK;

    // 현재 레벨의 클리어 목표를 초기화한다.
    for (int i = 0; i < NORMAL_BLOCK_COUNT; i++)
        level.goals[i] = 0;

    // 블록의 종류를 하나씩 읽는다.
    for (int i = 0; token != NULL; i++) {
        const int x = i % LEVEL_WIDTH_IN_BLOCKS;
        const int y = i / LEVEL_WIDTH_IN_BLOCKS;

        BlockType type = atoi(token);

        level.blocks[y][x].type = type;
        level.blocks[y][x].position = GetWorldCoordinates((CPair) { x, y });

        if (IsNormalBlock(&level.blocks[y][x])) level.goals[type - 1]++;

        token = strtok(NULL, ",");
    }

    // 게임 시작 시간을 설정한다.
    start_time = GetTime();
    
    // 게임의 현재 레벨을 설정한다.
    current_level = (char *) str;

    // 게임의 진행 상황을 초기화한다.
    for (int i = 0; i < NORMAL_BLOCK_COUNT; i++)
        progress[i] = 0;

    // 현재 점수를 초기화한다.
    scores[0] = 0;
}

/* 게임 플레이 화면을 초기화한다. */
void InitGameScreen(void) {
    ast_font_16pt = GetGameAsset(0);
    ast_font_24pt = GetGameAsset(1);
    ast_font_32pt = GetGameAsset(2);

    ast_buttons = GetGameAsset(3);
    ast_blocks = GetGameAsset(4);
    ast_frame = GetGameAsset(5);

    ast_dragged = GetGameAsset(7);
    ast_marked = GetGameAsset(8);

    settings = GetGameSettings();

    GuiSetFont(ast_font_16pt->data.font);

    SetGameState(GST_NORMAL);

    LoadLevel(LEVEL_00);
}

/* 게임 플레이 화면을 업데이트한다. */
void UpdateGameScreen(void) {
    HandleKeyEvents();

    ClearBackground(BLACK);

    DrawTextureV(
        ast_frame->data.texture,
        (Vector2) { 0.0f, 0.0f },
        WHITE
    );

    DrawLevel();
    DrawSidebar();

    if (settings->show_fps) DrawFPS(8, 8);
}

/* 게임 플레이 화면을 종료한다. */
int FinishGameScreen(void) {
    return result;
}

/* 레벨 위치 `indexes`에 종류가 `type`인 블록을 추가한다. */
static void AddBlock(CPair indexes, BlockType type) {
    if (type == BLT_EMPTY || indexes.x > LEVEL_WIDTH_IN_BLOCKS - 1 
        || indexes.y > LEVEL_HEIGHT_IN_BLOCKS - 1) return;

    level.blocks[indexes.y][indexes.x] = (Block) {
        .type = type,
        .state = BLS_NORMAL,
        .position = GetWorldCoordinates(indexes)
    };
}

/* 블록 `block`이 마우스로 이동 가능한지 확인한다. */
static bool CanBeDragged(Block *block) {
    if (selected_block != NULL) return false;

    return (IsNormalBlock(block) && block->state == BLS_NORMAL
        && CheckCollisionPointRec(GetMousePosition(), GetBlockBounds(block)));
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

    if (GetGameState() != GST_NORMAL) return;

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

/* 블록 `block`의 화면 기준 경계 범위를 반환한다. */
static Rectangle GetBlockBounds(Block *block) {
    return (Rectangle) {
        .x = block->position.x,
        .y = block->position.y,
        BLOCK_SIZE,
        BLOCK_SIZE
    };
}

/* 블록 `block`이 일반 블록인지 확인한다. */
static bool IsNormalBlock(Block *block) {
    return (block != NULL && block->type >= BLT_COLOR_01 && block->type <= BLT_COLOR_07);
}

/* 블록 `block`의 위치를 업데이트한다. */
static void UpdateBlock(Block *block) {
    if (!IsNormalBlock(block)) return;

    CPair indexes = GetLevelCoordinates(block->position);

    switch (block->state) {
        case BLS_NORMAL:
            if (indexes.y < LEVEL_HEIGHT_IN_BLOCKS - 1) {
                Block *bottom = &level.blocks[indexes.y + 1][indexes.x];

                // 바로 아래에 위치한 블록이 아예 없거나, 떨어지고 있다면...
                if (bottom->type == BLT_EMPTY || bottom->state == BLS_FALLING) {
                    block->state = BLS_FALLING;

                    break;
                }
            }

            // 블록을 왼쪽이나 오른쪽으로 이동할 수 있는지 확인한다.
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CanBeDragged(block)) {
                PlaySound(ast_dragged->data.sound);

                block->state = BLS_DRAGGED;
                selected_block = block;
            }

            break;
        
        case BLS_MARKED:
            if (block->timer >= FADE_DURATION) {
                if (selected_block == block) selected_block = NULL;

                level.blocks[indexes.y][indexes.x] = EMPTY_BLOCK;

                break;
            } else {
                if (!IsSoundPlaying(ast_marked->data.sound))
                    PlaySound(ast_marked->data.sound);
                
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
            // 마우스 왼쪽 버튼을 떼면 블록 이동을 멈춘다.
            if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
                block->state = BLS_NORMAL;
                selected_block = NULL;

                break;
            }

            Block *left = (indexes.x >= 1)
                ? &level.blocks[indexes.y][indexes.x - 1]
                : NULL;

            Block *right = (indexes.x < LEVEL_WIDTH_IN_BLOCKS - 1)
                ? &level.blocks[indexes.y][indexes.x + 1]
                : NULL;

            Block *bottom = (indexes.y < LEVEL_HEIGHT_IN_BLOCKS - 1)
                ? &level.blocks[indexes.y + 1][indexes.x]
                : NULL;

            // 바로 아래에 위치한 블록이 없으면 이동을 제한한다.
            if (bottom != NULL && bottom->type == BLT_EMPTY) break;

            int direction = GetMouseDirection(block);

            if (direction < 0 && left != NULL && left->type == BLT_EMPTY) {
                block->position = GetWorldCoordinates((CPair) { indexes.x - 1, indexes.y });

                level.blocks[indexes.y][indexes.x - 1] = level.blocks[indexes.y][indexes.x];
                level.blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
            } else if (direction > 0 && right != NULL && right->type == BLT_EMPTY) {
                block->position = GetWorldCoordinates((CPair) { indexes.x + 1, indexes.y });

                level.blocks[indexes.y][indexes.x + 1] = level.blocks[indexes.y][indexes.x];
                level.blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
            }

            break;

        case BLS_FALLING:
            if (indexes.y >= LEVEL_HEIGHT_IN_BLOCKS - 1) {
                block->state = BLS_NORMAL;

                block->velocity.y = 0.0f;
                block->position = GetWorldCoordinates(indexes);
            } else {
                Block *bottom = &level.blocks[indexes.y + 1][indexes.x];

                // 바로 아래에 위치한 블록이 존재하면, 블록이 더 이상 떨어지지 않게 한다.
                if (bottom->type != BLT_EMPTY && bottom->state != BLS_FALLING) {
                    block->state = BLS_NORMAL;

                    block->velocity.y = 0.0f;
                    block->position = GetWorldCoordinates(indexes);

                    break;
                }

                const float dt = GetFrameTime();

                block->velocity.y += GRAVITY_CONSTANT * dt;
                block->position.y += block->velocity.y * dt;

                CPair new_indexes = GetLevelCoordinates(block->position);

                // 현재 레벨의 블록 배열을 업데이트한다.
                if (indexes.y != new_indexes.y) {
                    level.blocks[new_indexes.y][new_indexes.x] = level.blocks[indexes.y][indexes.x];
                    level.blocks[indexes.y][indexes.x] = EMPTY_BLOCK;
                }
            }

            break;

        default:
            break;
    }

    if (block->state == BLS_NORMAL) {
        adjacents[0] = (indexes.y >= 1) 
            ? &level.blocks[indexes.y - 1][indexes.x] 
            : NULL;

        adjacents[1] = (indexes.x >= 1) 
            ? &level.blocks[indexes.y][indexes.x - 1] 
            : NULL;

        adjacents[2] = (indexes.y < LEVEL_HEIGHT_IN_BLOCKS - 1)
            ? &level.blocks[indexes.y + 1][indexes.x] 
            : NULL;

        adjacents[3] = (indexes.x < LEVEL_WIDTH_IN_BLOCKS - 1) 
            ? &level.blocks[indexes.y][indexes.x + 1] 
            : NULL;

        // 블록 주변에 이 블록과 같은 종류의 블록이 있는지 확인한다.
        for (int i = 0; i < MAX_ADJACENTS_COUNT; i++) {
            if (IsNormalBlock(adjacents[i]) && adjacents[i]->type == block->type 
                && adjacents[i]->state == BLS_NORMAL) {
                block->state = adjacents[i]->state = BLS_MARKED;
                
                matches.type = block->type;
                matches.count++;
            }
        }
    }
}

/* 게임 화면의 위치 `v`를 레벨 위치로 변환한다. */
static CPair GetLevelCoordinates(Vector2 v) {
    return (CPair) {
        .x = (v.x - LEVEL_BOUNDS.x) * INVERSE_BLOCK_SIZE,
        .y = (v.y - LEVEL_BOUNDS.y) * INVERSE_BLOCK_SIZE
    };
}

/* 레벨 위치 `indexes`를 게임 화면의 위치로 변환한다. */
static Vector2 GetWorldCoordinates(CPair indexes) {
    return (Vector2) {
        LEVEL_BOUNDS.x + (indexes.x * BLOCK_SIZE),
        LEVEL_BOUNDS.y + (indexes.y * BLOCK_SIZE)
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

/* 현재 레벨의 클리어 여부를 확인한다. */
static bool IsLevelCompleted(void) {
    for (int i = 0; i < NORMAL_BLOCK_COUNT; i++)
        if (progress[i] > 0) return false;

    return true;
}

/* 사용자의 키보드 입력을 처리한다. */
static void HandleKeyEvents(void) {
    // 현재 레벨을 초기화한다.
    if (IsKeyPressed(KEY_R)) LoadLevel(current_level);

    // 게임 메뉴 창과 환경 설정 창을 닫는다.
    if (IsKeyPressed(KEY_ESCAPE)) {
        SetGameState(GST_NORMAL);

        gui_menu_overlay_visible = false;
        gui_settings_window_box_visible = false;
    }
}

/* 게임 플레이 화면에 현재 레벨을 그린다. */
static void DrawLevel(void) {
    for (int y = 0; y < LEVEL_HEIGHT_IN_BLOCKS; y++) {
        for (int x = 0; x < LEVEL_WIDTH_IN_BLOCKS; x++) {
            if (GetGameState() == GST_NORMAL) 
                UpdateBlock(&level.blocks[y][x]);

            if (level.blocks[y][x].state != BLS_MARKED) 
                DrawBlock(&level.blocks[y][x]);
        }
    }

    // 짝이 맞는 블록이 있을 경우, 점수와 진행 상황을 업데이트한다.
    if (matches.count > 0) {
        progress[matches.type - 1] += (matches.count + 1);
        scores[0] += (matches.count + 1) * 100;

        if (scores[1] < scores[0]) scores[1] = scores[0];

        matches.type = BLT_EMPTY;
        matches.count = 0;
    }

    end_time = GetTime();
}

/* 게임 플레이 화면에 사이드바 구성 요소를 그린다. */
static void DrawSidebar(void) {
    {
        DrawTextEx(
            ast_font_32pt->data.font,
            TextFormat(
                SIDEBAR_STATS_01_TEXT,
                (int) ((end_time - start_time) * INVERSE_SIXTY) % 60,
                (int) (end_time - start_time) % 60
            ),
            SIDEBAR_STATS_TEXT_POSITIONS[0],
            ast_font_32pt->data.font.baseSize,
            1.0f,
            BLACK
        );

        DrawTextEx(
            ast_font_32pt->data.font,
            TextFormat(SIDEBAR_STATS_02_TEXT, scores[0]),
            SIDEBAR_STATS_TEXT_POSITIONS[1],
            ast_font_32pt->data.font.baseSize,
            1.0f,
            BLACK
        );

        DrawTextEx(
            ast_font_32pt->data.font,
            TextFormat(SIDEBAR_STATS_03_TEXT, scores[1]),
            SIDEBAR_STATS_TEXT_POSITIONS[2],
            ast_font_32pt->data.font.baseSize,
            1.0f,
            BLACK
        );
    }

    {
        for (int i = 0; i < NORMAL_BLOCK_COUNT; i++) {
            DrawTexturePro(
                ast_blocks->data.texture,
                (Rectangle) {
                    (i + 1) * BLOCK_SIZE,
                    0.0f,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                },
                SIDEBAR_PROG_BLOCK_BOUNDS[i],
                (Vector2) { 0.0f, 0.0f },
                0.0f,
                WHITE
            );

            DrawTextEx(
                ast_font_24pt->data.font,
                TextFormat(
                    SIDEBAR_PROGRESS_TEXT, 
                    level.goals[i] - progress[i], 
                    level.goals[i]
                ),
                SIDEBAR_PROGRESS_TEXT_POSITIONS[i],
                ast_font_24pt->data.font.baseSize,
                1.0f,
                BLACK
            );
        }
    }

    {
        int button_state = DrawImageButton(
            (ImageButton) {
                ast_buttons,
                (Rectangle) {
                    .width = SIDEBAR_MENU_BUTTON_DEST.width,
                    .height = SIDEBAR_MENU_BUTTON_DEST.height
                },
                SIDEBAR_MENU_BUTTON_DEST
            }
        );

        DrawTextEx(
            ast_font_24pt->data.font,
            SIDEBAR_MENU_BUTTON_TEXT,
            SIDEBAR_MENU_BUTTON_TEXT_OFFSET,
            ast_font_24pt->data.font.baseSize,
            2.0f,
            WHITE
        );

        // '메뉴' 버튼을 클릭했을 때에 동작을 지정한다.
        if (GetGameState() == GST_NORMAL && button_state == 2) {
            SetGameState(GST_PAUSED);

            gui_menu_overlay_visible = true;
        }
    }

    if (gui_menu_overlay_visible) {
        DrawRectangleRec(
            (Rectangle) { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT },
            Fade(BLACK, 0.75f)
        );

        int button_01_state = DrawImageButton(
            (ImageButton) {
                ast_buttons,
                GAME_MENU_BUTTON_SOURCE,
                GAME_MENU_BUTTON_01_DEST
            }
        );

        DrawTextEx(
            ast_font_32pt->data.font,
            GAME_MENU_BUTTON_01_TEXT,
            GAME_MENU_BUTTON_01_TEXT_OFFSET,
            ast_font_32pt->data.font.baseSize,
            2.0f,
            WHITE
        );

        int button_02_state = DrawImageButton(
            (ImageButton) {
                ast_buttons,
                GAME_MENU_BUTTON_SOURCE,
                GAME_MENU_BUTTON_02_DEST
            }
        );

        DrawTextEx(
            ast_font_32pt->data.font,
            GAME_MENU_BUTTON_02_TEXT,
            GAME_MENU_BUTTON_02_TEXT_OFFSET,
            ast_font_32pt->data.font.baseSize,
            2.0f,
            WHITE
        );

        int button_03_state = DrawImageButton(
            (ImageButton) {
                ast_buttons,
                GAME_MENU_BUTTON_SOURCE,
                GAME_MENU_BUTTON_03_DEST
            }
        );

        DrawTextEx(
            ast_font_32pt->data.font,
            GAME_MENU_BUTTON_03_TEXT,
            GAME_MENU_BUTTON_03_TEXT_OFFSET,
            ast_font_32pt->data.font.baseSize,
            2.0f,
            WHITE
        );

        if (button_01_state == 2) {
            SetGameState(GST_NORMAL);

            gui_menu_overlay_visible = false;
        } else if (button_02_state == 2) {
            result = 1;
        } else if (button_03_state == 2) {
            gui_menu_overlay_visible = false;
            gui_settings_window_box_visible = true;
        }
    }

    if (gui_settings_window_box_visible) {
        // 'X' 버튼을 클릭했다면, 현재 창을 닫는다.
        if (DrawSettingsWindow()) {
            SetGameState(GST_NORMAL);

            gui_settings_window_box_visible = false;
        }
    }
}