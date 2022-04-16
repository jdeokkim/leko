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

#define GUI_SETTINGS_WINDOW_BOX_TEXT    "\xED\x99\x98\xEA\xB2\xBD\x20\xEC\x84\xA4\xEC\xA0\x95"

#define GUI_SETTINGS_ELEMENT_01_TEXT    " \x46\x50\x53\x20\xED\x91\x9C\xEC\x8B\x9C\xED\x95\x98" \
                                        "\xEA\xB8\xB0"

#define GUI_SETTINGS_ELEMENT_02_TEXT   "\xEB\xA7\x88\xEC\x8A\xA4\xED\x84\xB0\x20\xEB\xB3\xBC\xEB" \
                                       "\xA5\xA8 "

#define GUI_SETTINGS_ELEMENT_03_TEXT   "\xEB\xB0\xB0\xEA\xB2\xBD\xEC\x9D\x8C\x20\xEB\xB3\xBC\xEB" \
                                       "\xA5\xA8 "

#define GUI_SETTINGS_ELEMENT_04_TEXT   "\xED\x9A\xA8\xEA\xB3\xBC\xEC\x9D\x8C\x20\xEB\xB3\xBC\xEB" \
                                       "\xA5\xA8 "

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
    DrawRectangleRec(
        (Rectangle) { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT },
        Fade(BLACK, 0.75f)
    );

    bool result = GuiWindowBox(
        GUI_WINDOW_BOX_BOUNDS,
        GUI_SETTINGS_WINDOW_BOX_TEXT
    );

    GameSettings *settings = GetGameSettings();

    settings->show_fps = GuiCheckBox(
        GUI_SETTINGS_CHECK_BOX_BOUNDS,
        GUI_SETTINGS_ELEMENT_01_TEXT,
        settings->show_fps
    );

    settings->volume.master = GuiSlider(
        GUI_SETTINGS_SLIDER_01_BOUNDS,
        GUI_SETTINGS_ELEMENT_02_TEXT,
        NULL,
        settings->volume.master,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    settings->volume.music = GuiSlider(
        GUI_SETTINGS_SLIDER_02_BOUNDS,
        GUI_SETTINGS_ELEMENT_03_TEXT,
        NULL,
        settings->volume.music,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    settings->volume.sound = GuiSlider(
        GUI_SETTINGS_SLIDER_03_BOUNDS,
        GUI_SETTINGS_ELEMENT_04_TEXT,
        NULL,
        settings->volume.sound,
        GUI_SETTINGS_SLIDER_MIN_VALUE,
        GUI_SETTINGS_SLIDER_MAX_VALUE
    );

    UpdateGameSettings();

    return result;
}