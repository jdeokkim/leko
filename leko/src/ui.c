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

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

/* | `ui` 모듈 매크로 정의... | */

#define GUI_SETTINGS_WINDOW_BOX_WIDTH   480.0f
#define GUI_SETTINGS_WINDOW_BOX_HEIGHT  360.0f

/* | `ui` 모듈 상수... | */

const Rectangle GUI_WINDOW_BOX_BOUNDS = {
    0.5f * (SCREEN_WIDTH - GUI_SETTINGS_WINDOW_BOX_WIDTH), 
    0.5f * (SCREEN_HEIGHT - GUI_SETTINGS_WINDOW_BOX_HEIGHT), 
    GUI_SETTINGS_WINDOW_BOX_WIDTH,
    GUI_SETTINGS_WINDOW_BOX_HEIGHT
};

const Rectangle GUI_SETTINGS_CHECK_BOX_01_BOUNDS = {
    /* TODO: ... */
};

const Rectangle GUI_SETTINGS_CHECK_BOX_02_BOUNDS = {
    /* TODO: ... */
};

const Rectangle GUI_SETTINGS_SLIDER_01_BOUNDS = {
    /* TODO: ... */
};

const Rectangle GUI_SETTINGS_SLIDER_02_BOUNDS = {
    /* TODO: ... */
};

const Rectangle GUI_SETTINGS_BUTTON_BOUNDS = {
    /* TODO: ... */
};

/* | `ui` 모듈 함수... | */

/* 그림 버튼을 화면에 그린다. */
int DrawImageButton(ImageButton button) {
    unsigned char state = 0;

    if (!GuiIsLocked() && CheckCollisionPointRec(GetMousePosition(), button.dest)) {
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

/* 게임 설정 창을 화면에 그린다. */
bool DrawSettingsWindow(void) {
    bool result = GuiWindowBox(
        GUI_WINDOW_BOX_BOUNDS,
        "\xED\x99\x98\xEA\xB2\xBD\x20\xEC\x84\xA4\xEC\xA0\x95"
    );
    
    // TODO: ...

    return result;
}