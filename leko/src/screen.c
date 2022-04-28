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

static GameScreen current_screen = GSC_INIT;

/* | `screen` 모듈 함수... | */

/* 게임의 현재 화면을 `screen`에 대응하는 화면으로 변경한다. */
void LoadScreen(GameScreen screen) {
    if (current_screen == screen) return;

    switch (screen) {
        case GSC_INIT:
            break;

        case GSC_LOADING:
            InitLoadingScreen();

            break;

        case GSC_TITLE:
            InitTitleScreen();
            
            break;

        case GSC_SELECT:
            InitSelectScreen();
            
            break;

        case GSC_GAME:
            InitGameScreen();
            
            break;
    }

    current_screen = screen;
}

/* 게임의 현재 화면을 업데이트한다. */
void UpdateScreen(void) {
    BeginDrawing();

    switch (current_screen) {
        case GSC_INIT:
            SetExitKey(KEY_NULL);

            LoadScreen(GSC_LOADING);

            break;

        case GSC_LOADING:
            UpdateLoadingScreen();

            if (FinishLoadingScreen())
                LoadScreen(GSC_TITLE);

            break;

        case GSC_TITLE:
            /*
            UpdateTitleScreen();

            if (FinishTitleScreen())
                LoadScreen(GSC_SELECT);
            */

            LoadScreen(GSC_SELECT);

            break;

        case GSC_SELECT:
            UpdateSelectScreen();

            if (FinishSelectScreen())
                LoadScreen(GSC_GAME);

            break;

        case GSC_GAME:
            UpdateGameScreen();

            if (FinishGameScreen())
                LoadScreen(GSC_SELECT);

            break;
    }

    EndDrawing();
}