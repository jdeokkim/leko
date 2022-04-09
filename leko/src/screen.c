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
            /*
            UpdateLoadingScreen();

            if (FinishLoadingScreen())
                LoadScreen(GSC_TITLE);
            */

            UpdateLoadingScreen();

            if (FinishLoadingScreen())
                LoadScreen(GSC_GAME);

            break;

        case GSC_TITLE:
            UpdateTitleScreen();

            if (FinishTitleScreen())
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