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

#define GUI_SETTINGS_WINDOW_BOX_WIDTH   360.0f
#define GUI_SETTINGS_WINDOW_BOX_HEIGHT  200.0f

#define GUI_SETTINGS_CHECK_BOX_WIDTH    20.0f
#define GUI_SETTINGS_CHECK_BOX_HEIGHT   20.0f

#define GUI_SETTINGS_SLIDER_WIDTH       242.0f
#define GUI_SETTINGS_SLIDER_HEIGHT      20.0f

#define GUI_SETTINGS_SLIDER_MIN_VALUE   0.0f
#define GUI_SETTINGS_SLIDER_MAX_VALUE   1.0f

#define GUI_SETTINGS_WINDOW_BOX_X       (0.5f * (SCREEN_WIDTH - GUI_SETTINGS_WINDOW_BOX_WIDTH))
#define GUI_SETTINGS_WINDOW_BOX_Y       (0.5f * (SCREEN_HEIGHT - GUI_SETTINGS_WINDOW_BOX_HEIGHT))

#define GUI_SETTINGS_ELEMENT_01_X       (GUI_SETTINGS_WINDOW_BOX_X + 16.0f)
#define GUI_SETTINGS_ELEMENT_01_Y       (GUI_SETTINGS_WINDOW_BOX_Y + 40.0f)

#define GUI_SETTINGS_ELEMENT_02_X       (GUI_SETTINGS_WINDOW_BOX_X + 100.0f)
#define GUI_SETTINGS_ELEMENT_02_Y       (GUI_SETTINGS_WINDOW_BOX_Y + 80.0f)

#define GUI_SETTINGS_ELEMENT_03_X       (GUI_SETTINGS_WINDOW_BOX_X + 100.0f)
#define GUI_SETTINGS_ELEMENT_03_Y       (GUI_SETTINGS_WINDOW_BOX_Y + 120.0f)

#define GUI_SETTINGS_ELEMENT_04_X       (GUI_SETTINGS_WINDOW_BOX_X + 100.0f)
#define GUI_SETTINGS_ELEMENT_04_Y       (GUI_SETTINGS_WINDOW_BOX_Y + 160.0f)

/* | `ui` 모듈 상수... | */

const Rectangle GUI_WINDOW_BOX_BOUNDS = {
    GUI_SETTINGS_WINDOW_BOX_X,
    GUI_SETTINGS_WINDOW_BOX_Y, 
    GUI_SETTINGS_WINDOW_BOX_WIDTH,
    GUI_SETTINGS_WINDOW_BOX_HEIGHT
};

const Rectangle GUI_SETTINGS_CHECK_BOX_BOUNDS = {
    GUI_SETTINGS_ELEMENT_01_X, 
    GUI_SETTINGS_ELEMENT_01_Y, 
    GUI_SETTINGS_CHECK_BOX_WIDTH,
    GUI_SETTINGS_CHECK_BOX_HEIGHT
};

const Rectangle GUI_SETTINGS_SLIDER_01_BOUNDS = {
    GUI_SETTINGS_ELEMENT_02_X, 
    GUI_SETTINGS_ELEMENT_02_Y, 
    GUI_SETTINGS_SLIDER_WIDTH,
    GUI_SETTINGS_SLIDER_HEIGHT
};

const Rectangle GUI_SETTINGS_SLIDER_02_BOUNDS = {
    GUI_SETTINGS_ELEMENT_03_X, 
    GUI_SETTINGS_ELEMENT_03_Y, 
    GUI_SETTINGS_SLIDER_WIDTH,
    GUI_SETTINGS_SLIDER_HEIGHT
};

const Rectangle GUI_SETTINGS_SLIDER_03_BOUNDS = {
    GUI_SETTINGS_ELEMENT_04_X, 
    GUI_SETTINGS_ELEMENT_04_Y, 
    GUI_SETTINGS_SLIDER_WIDTH,
    GUI_SETTINGS_SLIDER_HEIGHT
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

    if (GetGameState() != GST_NORMAL) state = 0;

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
    DrawRectangleRec(
        (Rectangle) { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT },
        Fade(BLACK, 0.25f)
    );

    bool result = GuiWindowBox(
        GUI_WINDOW_BOX_BOUNDS,
        "\xED\x99\x98\xEA\xB2\xBD\x20\xEC\x84\xA4\xEC\xA0\x95"
    );

    GameSettings *settings = GetGameSettings();

    settings->show_fps = GuiCheckBox(
        GUI_SETTINGS_CHECK_BOX_BOUNDS,
        " \x46\x50\x53\x20\xED\x91\x9C\xEC\x8B\x9C\xED\x95\x98\xEA\xB8\xB0",
        settings->show_fps
    );

    settings->volume.master = GuiSlider(
        GUI_SETTINGS_SLIDER_01_BOUNDS,
        "\xEB\xA7\x88\xEC\x8A\xA4\xED\x84\xB0\x20\xEB\xB3\xBC\xEB\xA5\xA8 ",
        NULL,
        settings->volume.master,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    settings->volume.music = GuiSlider(
        GUI_SETTINGS_SLIDER_02_BOUNDS,
        "\xEB\xB0\xB0\xEA\xB2\xBD\xEC\x9D\x8C\x20\xEB\xB3\xBC\xEB\xA5\xA8 ",
        NULL,
        settings->volume.music,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    settings->volume.sound = GuiSlider(
        GUI_SETTINGS_SLIDER_03_BOUNDS,
        "\xED\x9A\xA8\xEA\xB3\xBC\xEC\x9D\x8C\x20\xEB\xB3\xBC\xEB\xA5\xA8 ",
        NULL,
        settings->volume.sound,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    SetGameState(result ? GST_NORMAL : GST_PAUSED);

    UpdateGameSettings();

    return result;
}