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

/* | `select` 모듈 변수... | */

static GameAsset *ast_select;

static int result = 0;

/* | `select` 모듈 함수... | */

/* 레벨 선택 화면을 초기화한다. */
void InitSelectScreen(void) {
    ast_select = GetGameAsset(6);
}

/* 레벨 선택 화면을 업데이트한다. */
void UpdateSelectScreen(void) {
    ClearBackground(BLACK);

    // TODO: ...
    DrawTextureV(
        ast_select->data.texture,
        (Vector2) { 0.0f, 0.0f },
        WHITE
    );
}

/* 레벨 선택 화면을 종료한다. */
int FinishSelectScreen(void) {
    return result;
}