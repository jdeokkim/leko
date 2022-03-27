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

/* | `select` 모듈 변수... | */

static int result = 0;

/* | `select` 모듈 함수... | */

/* 레벨 선택 화면을 초기화한다. */
void InitSelectScreen(void) {
    /* TODO: ... */
}

/* 레벨 선택 화면을 업데이트한다. */
void UpdateSelectScreen(void) {
    // TODO: ...
    ClearBackground(VIOLET);
}

/* 레벨 선택 화면을 종료한다. */
int FinishSelectScreen(void) {
    return result;
}