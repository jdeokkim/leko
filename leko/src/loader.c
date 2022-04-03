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

#include <stdlib.h>

#include "preload.h"
#include "leko.h"

/* | `loader` 모듈 매크로 정의... | */

#define LOADER_WAIT_TIME         1.0f

#define PRELOAD_FONT_FIRST_CHAR  0x20
#define PRELOAD_FONT_SIZE        32

#define PROGRESS_BAR_COLOR_01    ((Color) { 52, 36, 244, 255 })
#define PROGRESS_BAR_COLOR_02    ((Color) { 58, 64, 216, 255 })
#define PROGRESS_BAR_COLOR_03    ((Color) { 64, 96, 187, 255 })
#define PROGRESS_BAR_COLOR_04    ((Color) { 61, 83, 200, 255 })

#define PROGRESS_BAR_LINE_THICK  2.5f

/* | `loader` 모듈 변수... | */

static GameAsset assets[] = {
    { .type = GAT_FONT,    .path = "res/fonts/nanum/nanumsquareround-16pt.fnt" },
    { .type = GAT_FONT,    .path = "res/fonts/nanum/nanumsquareround-24pt.fnt" },
    { .type = GAT_FONT,    .path = "res/fonts/nanum/nanumsquareround-32pt.fnt" },
    { .type = GAT_TEXTURE, .path = "res/images/buttons.png"                    },
    { .type = GAT_TEXTURE, .path = "res/images/blocks.png"                     },
    { .type = GAT_TEXTURE, .path = "res/images/frame.png"                      },
    { .type = GAT_SOUND,   .path = "res/sounds/dragged.wav"                    },
    { .type = GAT_SOUND,   .path = "res/sounds/marked.wav"                     }
};

static Rectangle progress_bar_inner_bounds = { .width = 764.0f, .height = 48.0f };
static Rectangle progress_bar_outer_bounds = { .width = 778.0f, .height = 62.0f };

static Font fnt_neodgm_min_32pt;
static Texture2D tx_copyright_message, tx_error_message, tx_loading_message;
static Vector2 v_copyright_message, v_error_message, v_loading_message;

static bool loading_failed = false;
static size_t asset_index = 0, max_asset_count;

static int result = 0;

/* | `loader` 모듈 함수... | */

/* 리소스 파일 관련 오류 화면을 업데이트한다. */
static void UpdateErrorScreen(void);

/* 리소스 파일 로딩 바를 업데이트한다. */
static void UpdateProgressBar(void);

/* 로딩 화면을 초기화한다. */
void InitLoadingScreen(void) {
    Image img_copyright_message = LoadImageFromMemory(
        ".png", 
        _preload_01_png, 
        PRELOAD_01_LENGTH
    );

    Image img_error_message = LoadImageFromMemory(
        ".png", 
        _preload_02_png, 
        PRELOAD_02_LENGTH
    );

    Image img_loading_message = LoadImageFromMemory(
        ".png", 
        _preload_03_png, 
        PRELOAD_03_LENGTH
    );

    Image img_neodgm_min_32pt = LoadImageFromMemory(
        ".png", 
        _preload_04_png, 
        PRELOAD_04_LENGTH
    );

    tx_copyright_message = LoadTextureFromImage(img_copyright_message);
    tx_error_message = LoadTextureFromImage(img_error_message);
    tx_loading_message = LoadTextureFromImage(img_loading_message);

    fnt_neodgm_min_32pt = LoadFontFromImage(
        img_neodgm_min_32pt, 
        MAGENTA, 
        PRELOAD_FONT_FIRST_CHAR
    );

    UnloadImage(img_copyright_message);
    UnloadImage(img_error_message);
    UnloadImage(img_loading_message);

    progress_bar_outer_bounds.x = 0.5f * (SCREEN_WIDTH - progress_bar_outer_bounds.width);
    progress_bar_outer_bounds.y = 0.65f * (SCREEN_HEIGHT - tx_loading_message.height);

    progress_bar_inner_bounds.x = 0.5f * (SCREEN_WIDTH - progress_bar_inner_bounds.width);
    progress_bar_inner_bounds.y = progress_bar_outer_bounds.y 
        + 0.5f * (progress_bar_outer_bounds.height - progress_bar_inner_bounds.height);

    v_error_message = (Vector2) {
        0.5f * (SCREEN_WIDTH - tx_error_message.width),
        0.5f * (SCREEN_HEIGHT - tx_error_message.height)
    };

    v_loading_message = (Vector2) {
        0.5f * (SCREEN_WIDTH - tx_loading_message.width),
        0.35f * (SCREEN_HEIGHT - tx_loading_message.height)
    };

    v_copyright_message = (Vector2) {
        SCREEN_WIDTH - (tx_copyright_message.width + 16.0f),
        SCREEN_HEIGHT - (tx_copyright_message.height + 16.0f)
    };

    max_asset_count = sizeof(assets) / sizeof(assets[0]);
}

/* 로딩 화면을 업데이트한다. */
void UpdateLoadingScreen(void) {
    static double timer = 0;

    if (loading_failed) {
        UpdateErrorScreen();
    } else {
        ClearBackground(BLACK);
        
        DrawTextureEx(
            tx_loading_message,
            v_loading_message,
            0.0f,
            1.0f,
            WHITE
        );

        if (asset_index <= max_asset_count - 1) {
            bool check = LoadGameAsset(asset_index);

            if (!check) {
                loading_failed = true;

                return;
            }
            
            const char *path_text = TextFormat(
                "-> %s (%d / %d)", 
                assets[asset_index].path,
                asset_index + 1,
                max_asset_count
            );

            const Vector2 font_dimensions = MeasureTextEx(
                fnt_neodgm_min_32pt,
                path_text,
                PRELOAD_FONT_SIZE,
                2.0f
            );

            DrawTextEx(
                fnt_neodgm_min_32pt,
                path_text,
                (Vector2) {
                    0.5f * (SCREEN_WIDTH - font_dimensions.x),
                    v_loading_message.y + 80.0f
                },
                PRELOAD_FONT_SIZE,
                2.0f,
                WHITE
            );
            
            asset_index++;
        } else {
            if (timer >= LOADER_WAIT_TIME) {
                timer = 0.0f;
                result = 1;

                return;
            }

            timer += GetFrameTime();
        }

        UpdateProgressBar();

        DrawTextureEx(
            tx_copyright_message,
            v_copyright_message,
            0.0f,
            1.0f,
            WHITE
        );
    }
}

/* 로딩 화면을 종료한다. */
int FinishLoadingScreen(void) {
    if (result == 1) {
        UnloadTexture(tx_copyright_message);
        UnloadTexture(tx_error_message);
        UnloadTexture(tx_loading_message);

        UnloadFont(fnt_neodgm_min_32pt);
    }

    return result;
}

/* `index + 1`번째 게임 리소스의 데이터를 메모리로 불러온다.*/
bool LoadGameAsset(int index) {
    if (index < 0 || index > max_asset_count - 1) return false;

    switch (assets[index].type) {
        case GAT_FONT:
            assets[index].data.font = LoadFont(assets[index].path);

            break;

        case GAT_MUSIC:
            assets[index].data.music = LoadMusicStream(assets[index].path);

            if (assets[index].data.music.ctxData == NULL) 
                return false;

            break;

        case GAT_SOUND:
            assets[index].data.sound = LoadSound(assets[index].path);

            if (assets[index].data.sound.frameCount == 0) 
                return false;

            break;

        case GAT_TEXTURE:
            assets[index].data.texture = LoadTexture(assets[index].path);

            if (assets[index].data.texture.id == 0) 
                return false;

            break;

        default:
            break;
    }

    return (assets[index].loaded = true);
}

/* `index + 1`번째 게임 리소스의 데이터에 할당된 메모리를 해제한다.*/
bool UnloadGameAsset(int index) {
    if (index < 0 || index > max_asset_count - 1) return false;

    switch (assets[index].type) {
        case GAT_FONT:
            UnloadFont(assets[index].data.font);

            break;

        case GAT_MUSIC:
            UnloadMusicStream(assets[index].data.music);

            break;

        case GAT_SOUND:
            UnloadSound(assets[index].data.sound);

            break;

        case GAT_TEXTURE:
            UnloadTexture(assets[index].data.texture);

            break;

        default:
            break;
    }

    return true;
}

/* `index + 1`번째 게임 리소스 데이터를 반환한다. */
GameAsset *GetGameAsset(int index) {
    return (index >= 0 && index <= max_asset_count - 1)
        ? (GameAsset *) &assets[index] 
        : NULL;
}

/* 리소스 파일 관련 오류 화면을 업데이트한다. */
static void UpdateErrorScreen(void) {
    ClearBackground(BLACK);

    DrawTextureEx(
        tx_error_message,
        v_error_message,
        0.0f,
        1.0f,
        WHITE
    );

    DrawTextureEx(
        tx_copyright_message,
        v_copyright_message,
        0.0f,
        1.0f,
        WHITE
    );
}

/* 리소스 파일 로딩 바를 업데이트한다. */
static void UpdateProgressBar(void) {
    const Rectangle progress_bar_bounds = {
        .x = progress_bar_inner_bounds.x,
        .y = progress_bar_inner_bounds.y,
        .width = (asset_index / (float) max_asset_count) 
            * progress_bar_inner_bounds.width,
        .height = progress_bar_inner_bounds.height
    };

    DrawRectangleLinesEx(
        progress_bar_outer_bounds,
        PROGRESS_BAR_LINE_THICK,
        WHITE
    );

    DrawRectangleGradientEx(
        progress_bar_bounds,
        PROGRESS_BAR_COLOR_01,
        PROGRESS_BAR_COLOR_02,
        PROGRESS_BAR_COLOR_03,
        PROGRESS_BAR_COLOR_04
    );
}