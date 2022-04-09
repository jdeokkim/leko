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
#include "raygui.h"

/* | 매크로 정의... | */

#define LEKO_NAME               "c-krit/leko"
#define LEKO_VERSION            "0.1.0"

#define TARGET_FPS              60

#define SCREEN_WIDTH            1024
#define SCREEN_HEIGHT           768

#define BLOCK_SIZE              48

#define NORMAL_BLOCK_COUNT      (BLT_COLOR_07 - BLT_EMPTY)

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

/* 게임의 현재 상태를 나타내는 열거형. */
typedef enum GameState {
    GST_NORMAL,
    GST_PAUSED
} GameState;

/* 게임의 리소스를 나타내는 구조체. */
typedef struct GameAsset {
    bool loaded;            // 게임 리소스의 로딩 여부
    GameAssetType type;     // 게임 리소스의 종류
    const char *path;       // 게임 리소스의 경로
    union {
        Font font;
        Music music;
        Sound sound;
        Texture2D texture;
    } data;                 // 게임 리소스의 데이터
} GameAsset;

/* 게임의 환경 설정을 나타내는 구조체. */
typedef struct GameSettings {
    bool show_fps;     // 게임 화면에 FPS 표시 여부
    struct {
        float master;
        float music;
        float sound;
    } volume;          // 게임의 볼륨 설정
} GameSettings;

/* 그림 버튼을 나타내는 구조체. */
typedef struct ImageButton {
    GameAsset *asset;  // 그림 버튼 렌더링에 필요한 게임 리소스
    Rectangle source;  // 텍스처 파일을 기준으로 한 렌더링 영역
    Rectangle dest;    // 게임 화면을 기준으로 한 렌더링 영역
} ImageButton;

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
typedef struct Block Block;

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

/* 게임의 현재 상태를 반환한다. */
GameState GetGameState(void);

/* 게임의 환경 설정을 반환한다. */
GameSettings *GetGameSettings(void);

/* 게임의 현재 상태를 `state`로 변경한다. */
void SetGameState(GameState state);

/* | `ui` 모듈 함수... | */

/* 그림 버튼을 화면에 그린다. */
int DrawImageButton(ImageButton button);

/* 게임 설정 창을 화면에 그린다. */
bool DrawSettingsWindow(void);

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