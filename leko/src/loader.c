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

#include "leko.h"

/* | `loader` 모듈 매크로 정의... | */

#define MUSIC_LIST_LENGTH    1
#define SOUND_LIST_LENGTH    1
#define TEXTURE_LIST_LENGTH  1

/* | `loader` 모듈 상수... | */

const char *music_paths[MUSIC_LIST_LENGTH] = {
    /* TODO: ... */
};

const char *sound_paths[SOUND_LIST_LENGTH] = {
    /* TODO: ... */
};

const char *texture_paths[TEXTURE_LIST_LENGTH] = {
    "res/images/background.png"
};

/* | `loader` 모듈 변수... | */

static Music music_list[MUSIC_LIST_LENGTH];
static Sound sound_list[SOUND_LIST_LENGTH];
static Texture2D texture_list[TEXTURE_LIST_LENGTH];

static bool initialized = false;

static int result = 0;

/* | `loader` 모듈 함수... | */

/* ID가 `id`인 `Music` 리소스를 반환한다. */
Music *GetMusicResource(int id) {
    if (!initialized) return NULL;

    return (id >= 0 && id <= MUSIC_LIST_LENGTH - 1) ? &music_list[id] : NULL;
}

/* ID가 `id`인 `Sound` 리소스를 반환한다. */
Sound *GetSoundResource(int id) {
    if (!initialized) return NULL;

    return (id >= 0 && id <= SOUND_LIST_LENGTH - 1) ? &sound_list[id] : NULL;
}

/* ID가 `id`인 `Texture2D` 리소스를 반환한다. */
Texture2D *GetTextureResource(int id) {
    if (!initialized) return NULL;
    
    return (id >= 0 && id <= TEXTURE_LIST_LENGTH - 1) ? &texture_list[id] : NULL;
}

/* 로딩 화면을 초기화한다. */
void InitLoadingScreen(void) {
    /* TODO: ... */
}

/* 로딩 화면을 업데이트한다. */
void UpdateLoadingScreen(void) {
    // TODO: ...
    ClearBackground(GREEN);
}

/* 로딩 화면을 종료한다. */
int FinishLoadingScreen(void) {
    return result;
}