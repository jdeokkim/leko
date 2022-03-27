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

/* | `loader` 모듈 상수... | */

const GameAsset assets[] = {
    { .type = GAT_TEXTURE, .path = "res/images/background.png" }
};

/* | `loader` 모듈 변수... | */

static Texture2D tx_error_message;

static int result = 0;

/* | `loader` 모듈 함수... | */

/* 로딩 화면을 초기화한다. */
void InitLoadingScreen(void) {
    Image img_error_message = LoadImageFromMemory(
        ".png", 
        _preload_01_png, 
        PRELOAD_01_LENGTH
    );

    tx_error_message = LoadTextureFromImage(img_error_message);

    UnloadImage(img_error_message);
}

/* 로딩 화면을 업데이트한다. */
void UpdateLoadingScreen(void) {
    const Vector2 error_message_position = {
        0.5f * (SCREEN_WIDTH - tx_error_message.width),
        0.5f * (SCREEN_HEIGHT - tx_error_message.height)
    };
    
    ClearBackground(BLACK);

    // TODO: ...
    DrawTextureEx(
        tx_error_message,
        error_message_position,
        0.0f,
        1.0f,
        WHITE
    );
}

/* 로딩 화면을 종료한다. */
int FinishLoadingScreen(void) {
    return result;
}