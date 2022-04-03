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

/* | `ui` 모듈 함수... | */

/* 그림 버튼을 화면에 그린다. */
int DrawImageButton(ImageButton button) {
    unsigned char state = 0;

    if (CheckCollisionPointRec(GetMousePosition(), button.dest)) {
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) state = 1;
        else state = 2;
    }

    // 그림 버튼의 상태에 따라 모양을 변경한다.
    button.source.x = state * button.source.width;

    DrawTexturePro(
        button.asset->data.texture,
        button.source,
        button.dest,
        (Vector2) { 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    return state;
}