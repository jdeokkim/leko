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

#ifndef LEKO_H
#define LEKO_H

#include <stdbool.h>
#include <stdint.h>

#include "raylib.h"

/* | 매크로 정의... | */

#define LEKO_NAME               "c-krit/leko"
#define LEKO_VERSION            "0.1.0"

#define TARGET_FPS              60

#define SCREEN_WIDTH            1024
#define SCREEN_HEIGHT           768

#define BLOCK_SIZE              48

#define NORMAL_BLOCK_COUNT      7

#define LEVEL_WIDTH_IN_BLOCKS   15
#define LEVEL_HEIGHT_IN_BLOCKS  14

/* | 자료형 정의... | */

/* 게임 리소스의 종류를 나타내는 열거형. */
typedef enum GameAssetType {
    GAT_FONT,    // 비트맵 글꼴
    GAT_MUSIC,   // 배경 음악
    GAT_SOUND,   // 효과음
    GAT_TEXTURE  // 텍스처
} GameAssetType;

/* 게임의 현재 화면을 나타내는 열거형. */
typedef enum GameScreen {
    GSC_INIT,     // 초기 화면
    GSC_LOADING,  // 로딩 화면
    GSC_TITLE,    // 타이틀 화면
    GSC_SELECT,   // 레벨 선택 화면
    GSC_GAME      // 게임 플레이 화면
} GameScreen;

/* 게임의 리소스를 나타내는 구조체. */
typedef struct GameAsset {
    bool loaded;
    GameAssetType type;
    const char *path;
    union {
        Font font;
        Music music;
        Sound sound;
        Texture2D texture;
    } data;
} GameAsset;

/* 블록의 종류를 나타내는 열거형. */
typedef enum BlockType {
    BLT_EMPTY,     // 일반 블록, 빈 공간
    BLT_COLOR_01,  // 일반 블록, 첫 번째 색상
    BLT_COLOR_02,  // 일반 블록, 두 번째 색상
    BLT_COLOR_03,  // 일반 블록, 세 번째 색상
    BLT_COLOR_04,  // 일반 블록, 네 번째 색상
    BLT_COLOR_05,  // 일반 블록, 다섯 번째 색상
    BLT_COLOR_06,  // 일반 블록, 여섯 번째 색상
    BLT_COLOR_07,  // 일반 블록, 일곱 번째 색상
    BLT_WALL       // 특수 블록, 벽
} BlockType;

/* 블록의 상태를 나타내는 열거형. */
typedef enum BlockState {
    BLS_NORMAL,   // 기본 상태
    BLS_MARKED,   // 하나 이상의 블록과 매치
    BLS_DRAGGED,  // 마우스로 드래그 중
    BLS_FALLING   // 아래로 떨어지는 중
} BlockState;

/* 블록을 나타내는 구조체. */
typedef struct Block {
    BlockType type;    // 블록의 종류
    BlockState state;  // 블록의 상태
    Vector2 position;  // 블록의 화면 기준 위치
    Vector2 velocity;  // 블록의 화면 기준 속도
    float timer;       // 시간 측정용 변수
} Block;

/* 게임의 레벨을 나타내는 구조체. */
typedef struct GameLevel {
    Block blocks[LEVEL_HEIGHT_IN_BLOCKS][LEVEL_WIDTH_IN_BLOCKS];  // 블록 배열
    int goals[NORMAL_BLOCK_COUNT];                                // 레벨 클리어 목표
} GameLevel;

/* | `screen` 모듈 함수... | */

/* 게임의 현재 화면을 `screen`에 대응하는 화면으로 변경한다. */
void LoadScreen(GameScreen screen);

/* 게임의 현재 화면을 업데이트한다. */
void UpdateScreen(void);

/* | `loader` 모듈 함수... | */

/* 로딩 화면을 초기화한다. */
void InitLoadingScreen(void);

/* 로딩 화면을 업데이트한다. */
void UpdateLoadingScreen(void);

/* 로딩 화면을 종료한다. */
int FinishLoadingScreen(void);

/* `index + 1`번째 게임 리소스의 데이터를 메모리로 불러온다.*/
bool LoadGameAsset(int index);

/* `index + 1`번째 게임 리소스의 데이터에 할당된 메모리를 해제한다.*/
bool UnloadGameAsset(int index);

/* `index + 1`번째 게임 리소스 데이터를 반환한다. */
GameAsset *GetGameAsset(int index);

/* | `title` 모듈 함수... | */

/* 타이틀 화면을 초기화한다. */
void InitTitleScreen(void);

/* 타이틀 화면을 업데이트한다. */
void UpdateTitleScreen(void);

/* 타이틀 화면을 종료한다. */
int FinishTitleScreen(void);

/* | `select` 모듈 함수... | */

/* 레벨 선택 화면을 초기화한다. */
void InitSelectScreen(void);

/* 레벨 선택 화면을 업데이트한다. */
void UpdateSelectScreen(void);

/* 레벨 선택 화면을 종료한다. */
int FinishSelectScreen(void);

/* | `game` 모듈 함수... | */

/* 레벨 문자열 `str`을 통해 레벨을 불러온다. */
void LoadLevel(const char *str);

/* 게임 플레이 화면을 초기화한다. */
void InitGameScreen(void);

/* 게임 플레이 화면을 업데이트한다. */
void UpdateGameScreen(void);

/* 게임 플레이 화면을 종료한다. */
int FinishGameScreen(void);

#endif