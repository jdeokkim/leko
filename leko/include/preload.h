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

#ifndef PRELOAD_H
#define PRELOAD_H

/* 매크로 정의... */

#define PRELOAD_01_LENGTH  1567

/* 전역 상수 정의... */

// 리소스 파일 로드 오류 메시지 (흰색)
const unsigned char _preload_01_png[PRELOAD_01_LENGTH] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x02, 0xbe, 0x00, 0x00, 0x00, 0x5f,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x0e, 0x00, 0xc4, 0x7b, 0x00, 0x00, 0x00,
  0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x2e, 0x23, 0x00, 0x00, 0x2e,
  0x23, 0x01, 0x78, 0xa5, 0x3f, 0x76, 0x00, 0x00, 0x05, 0xd1, 0x49, 0x44,
  0x41, 0x54, 0x78, 0xda, 0xed, 0xdd, 0x51, 0x72, 0xe3, 0x36, 0x0c, 0x00,
  0x50, 0xab, 0x93, 0x03, 0xb6, 0xe7, 0xd8, 0xcd, 0x69, 0x76, 0x7b, 0x8f,
  0xde, 0x50, 0xfd, 0xc8, 0x74, 0xaa, 0x8f, 0x68, 0x57, 0x0a, 0x49, 0x11,
  0x04, 0xde, 0xfb, 0xf2, 0x4c, 0x1c, 0x99, 0xa6, 0x20, 0x98, 0x43, 0x50,
  0xe2, 0xeb, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xdb, 0x22, 0x37, 0x6e, 0xdf, 0xf7, 0xfd,
  0xd3, 0x46, 0x6f, 0xdb, 0xe6, 0xd4, 0x91, 0x31, 0x26, 0xcf, 0x8e, 0x7f,
  0x7a, 0x01, 0x37, 0x7c, 0xee, 0xea, 0xd7, 0x57, 0x85, 0xfc, 0xb0, 0xef,
  0xfb, 0xcf, 0xd7, 0xeb, 0xf5, 0xed, 0x93, 0x3f, 0xbd, 0x6f, 0xdb, 0xf6,
  0x33, 0x5b, 0xff, 0x67, 0x3a, 0xa7, 0x4f, 0xf6, 0x4f, 0xd6, 0xfc, 0x50,
  0x79, 0x0c, 0xb0, 0xe2, 0x77, 0x5f, 0xa5, 0xcd, 0x7f, 0x18, 0xca, 0x00,
  0x00, 0x50, 0x81, 0x81, 0x2f, 0x00, 0x00, 0x25, 0xbc, 0x9d, 0xfd, 0xe1,
  0x6e, 0x49, 0xe5, 0x0a, 0xe5, 0x2a, 0xed, 0x1f, 0xfd, 0xbd, 0x56, 0x8c,
  0xcf, 0xbb, 0xe7, 0xe8, 0xf8, 0xfe, 0xe3, 0xeb, 0x08, 0xe7, 0xf4, 0xc9,
  0x52, 0x2c, 0x3c, 0x99, 0x1f, 0x66, 0xc5, 0x6d, 0xa6, 0xfc, 0xe0, 0x77,
  0xdf, 0xef, 0x63, 0x04, 0x66, 0x7c, 0x01, 0x00, 0x28, 0xc1, 0xc0, 0x17,
  0x00, 0x80, 0x12, 0x86, 0x4c, 0x5d, 0xf7, 0x2a, 0x13, 0xb8, 0xab, 0x54,
  0xfb, 0x7b, 0x7d, 0xc7, 0x68, 0x31, 0x19, 0xe1, 0x38, 0xb3, 0xda, 0x90,
  0x29, 0x3f, 0x3c, 0x19, 0xcf, 0xbf, 0x30, 0xe5, 0x09, 0x0f, 0x91, 0x9f,
  0xea, 0xb0, 0xfa, 0x6f, 0xc7, 0xe8, 0x7e, 0xb8, 0x12, 0x33, 0xb3, 0xfa,
  0x30, 0xc2, 0x72, 0x29, 0xf1, 0x93, 0x7b, 0xbc, 0x61, 0xc6, 0x17, 0x00,
  0x80, 0x12, 0x0c, 0x7c, 0x01, 0x00, 0x28, 0xc1, 0x52, 0x87, 0x05, 0xda,
  0x50, 0xb9, 0xfd, 0xbd, 0xbe, 0xa3, 0xa5, 0x0e, 0x71, 0xfe, 0x37, 0x5a,
  0x1b, 0x22, 0xc7, 0xf0, 0xeb, 0xa4, 0x24, 0x9d, 0x35, 0x37, 0xb6, 0xdc,
  0x8d, 0x3e, 0xe2, 0x7a, 0x9f, 0xd5, 0x3f, 0x0f, 0x2c, 0x75, 0x78, 0xf5,
  0xe8, 0xe7, 0x59, 0x7d, 0x35, 0x6b, 0x23, 0x21, 0x4b, 0x1d, 0x72, 0xe4,
  0x64, 0x33, 0xbe, 0x00, 0x00, 0x94, 0x60, 0xe0, 0x0b, 0x00, 0x80, 0x81,
  0x6f, 0x55, 0xfb, 0x41, 0xcb, 0x7b, 0xb4, 0x1f, 0xd8, 0x2f, 0x38, 0xbe,
  0x7f, 0x3b, 0x78, 0xbd, 0x5e, 0x3f, 0x4e, 0xde, 0xff, 0x7e, 0x78, 0xcf,
  0xad, 0xcf, 0xda, 0xf7, 0xfd, 0xcf, 0xd5, 0x72, 0xcb, 0x76, 0x81, 0x48,
  0xbb, 0xe5, 0xfd, 0xa9, 0xfe, 0x6c, 0x8c, 0xff, 0xdf, 0xc6, 0x43, 0xcb,
  0x67, 0x61, 0xe0, 0x0b, 0x00, 0x00, 0x06, 0xbe, 0x00, 0x00, 0xb0, 0xb2,
  0xb7, 0xb3, 0x3f, 0x54, 0x2b, 0x09, 0xac, 0xbe, 0x1f, 0xba, 0xfd, 0xdc,
  0xd7, 0x72, 0x76, 0x07, 0xfa, 0x95, 0x73, 0x51, 0xe1, 0x49, 0x1d, 0x59,
  0xcf, 0xf5, 0x8a, 0xc7, 0x97, 0x5b, 0xe4, 0x87, 0xca, 0xf1, 0x4f, 0x3e,
  0x66, 0x7c, 0x01, 0x00, 0x30, 0xf0, 0x05, 0x00, 0x80, 0x2c, 0x4e, 0x4b,
  0x04, 0x99, 0x1e, 0x90, 0x3e, 0x7a, 0xef, 0x6f, 0xc7, 0x9f, 0x2b, 0xc2,
  0x06, 0x16, 0xbd, 0xfa, 0xed, 0xc9, 0x73, 0x61, 0x03, 0x8b, 0xe7, 0x63,
  0x32, 0xa0, 0xa1, 0x1b, 0x64, 0xcc, 0xda, 0x98, 0xc0, 0x06, 0x1f, 0x31,
  0xf3, 0x43, 0xb8, 0x01, 0x50, 0xe0, 0xe5, 0x22, 0x99, 0x36, 0xb0, 0x88,
  0x36, 0xae, 0x30, 0xe3, 0x0b, 0x00, 0x40, 0x09, 0x6f, 0xba, 0x00, 0x80,
  0x64, 0xfe, 0x3e, 0xbc, 0xfe, 0xf6, 0xdf, 0x8b, 0x7d, 0xdf, 0xbf, 0xf7,
  0x38, 0xf8, 0x67, 0xb3, 0xe4, 0xc0, 0x1a, 0x4a, 0x2c, 0x75, 0x20, 0xb7,
  0x08, 0x4b, 0x1d, 0xaa, 0xc5, 0xa4, 0xa5, 0x0e, 0xac, 0x1e, 0xab, 0x8d,
  0x03, 0x5f, 0xf1, 0x29, 0xbf, 0x85, 0x6d, 0x43, 0xb4, 0xa5, 0x0e, 0xd1,
  0x62, 0xde, 0x52, 0x07, 0x00, 0x00, 0x4a, 0x30, 0xf0, 0x05, 0x00, 0xa0,
  0x04, 0x6b, 0x7c, 0x7f, 0x43, 0xb9, 0x8a, 0x59, 0x31, 0x36, 0x8b, 0xd8,
  0x96, 0x43, 0x66, 0xc5, 0xed, 0x88, 0x3e, 0xc9, 0xba, 0x11, 0xcc, 0x93,
  0x4f, 0x8d, 0x88, 0x76, 0x4c, 0xbf, 0xdd, 0xb4, 0x30, 0xe3, 0x0b, 0x00,
  0x80, 0x81, 0x2f, 0x00, 0x00, 0x64, 0x61, 0xa9, 0x03, 0x4c, 0x36, 0xab,
  0xf4, 0xb6, 0xd0, 0x26, 0x0b, 0x4c, 0x74, 0x25, 0x4e, 0x7a, 0x95, 0xc2,
  0x95, 0xa7, 0x81, 0xbb, 0xb9, 0xe8, 0x6e, 0x7e, 0x30, 0xe3, 0x0b, 0x00,
  0x40, 0x09, 0x06, 0xbe, 0x00, 0x00, 0x94, 0x30, 0x64, 0xa9, 0x83, 0x72,
  0x15, 0xb4, 0x5f, 0x2f, 0x91, 0x9d, 0x6d, 0x0e, 0x72, 0x7c, 0x9d, 0xf5,
  0x6e, 0x7a, 0xfa, 0x9e, 0xaf, 0x2b, 0x1b, 0xcd, 0x20, 0xef, 0x65, 0xfa,
  0x8e, 0x91, 0x73, 0x5d, 0x85, 0xfc, 0x6c, 0xc6, 0x17, 0x00, 0x80, 0x12,
  0x0c, 0x7c, 0x01, 0x00, 0x28, 0xe1, 0x74, 0xa9, 0xc3, 0x95, 0x52, 0xe6,
  0x15, 0x59, 0xef, 0x58, 0xef, 0x75, 0xfc, 0xbb, 0xe5, 0xe0, 0x68, 0x22,
  0x9f, 0xdf, 0xbb, 0xef, 0x89, 0x56, 0xca, 0x59, 0xa5, 0xb4, 0xd4, 0x92,
  0x2b, 0x2c, 0x6f, 0x58, 0x57, 0xaf, 0x6b, 0x67, 0x44, 0xae, 0x6b, 0x39,
  0x66, 0xe4, 0xdc, 0x3b, 0x22, 0xa7, 0xcd, 0xca, 0x93, 0xb3, 0x36, 0xb0,
  0x18, 0x9d, 0xd3, 0x22, 0xe4, 0xba, 0xd5, 0xc7, 0x6f, 0xa3, 0xdb, 0x63,
  0xc6, 0x17, 0x00, 0x80, 0x12, 0x0c, 0x7c, 0x01, 0x00, 0x28, 0x21, 0x74,
  0x99, 0xd1, 0xdd, 0xdf, 0x54, 0x8b, 0xc9, 0x08, 0x65, 0xd6, 0x55, 0xae,
  0xaf, 0x4c, 0x77, 0x4c, 0x3f, 0xec, 0xaf, 0x6d, 0xdb, 0xfe, 0x89, 0xf8,
  0x5d, 0x32, 0xe5, 0xf6, 0x5e, 0xf1, 0x79, 0xf7, 0x38, 0x57, 0xde, 0x3f,
  0xe2, 0x98, 0x91, 0xe3, 0x7f, 0xc5, 0xb8, 0xf2, 0x44, 0x88, 0x71, 0xcc,
  0xf8, 0x02, 0x00, 0x50, 0x82, 0x81, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xdf, 0xa6,
  0x0b, 0xda, 0x8d, 0xd8, 0x1b, 0xfd, 0xee, 0x67, 0x9d, 0x9e, 0xe0, 0x86,
  0x3d, 0xb2, 0x47, 0xef, 0xbb, 0x3d, 0x7a, 0xdf, 0xf6, 0x15, 0xf7, 0x67,
  0x8f, 0x10, 0xab, 0xbe, 0x4b, 0x8e, 0xf6, 0x3b, 0xfe, 0x33, 0xc7, 0x7f,
  0x32, 0xff, 0xa3, 0xff, 0x69, 0x67, 0xcb, 0x62, 0x00, 0x00, 0x0c, 0x7c,
  0x01, 0x00, 0x20, 0x8b, 0xb7, 0xac, 0x5f, 0xac, 0x57, 0x19, 0x3d, 0x42,
  0x29, 0xe4, 0x6e, 0x99, 0xe6, 0xf8, 0xfe, 0xe3, 0xeb, 0x59, 0xdf, 0xe5,
  0xca, 0xb9, 0x18, 0x51, 0xbe, 0x8c, 0x5c, 0xde, 0x1a, 0xb1, 0xcc, 0x23,
  0x5a, 0xd9, 0x4e, 0x79, 0xb1, 0x66, 0xfe, 0x7c, 0xf2, 0x7a, 0xcf, 0xda,
  0xfe, 0xd1, 0xb9, 0x22, 0x42, 0x9e, 0xc9, 0xba, 0x54, 0x29, 0x72, 0x3e,
  0x97, 0x93, 0x3f, 0x98, 0xf1, 0x05, 0x00, 0xc0, 0xc0, 0x17, 0x00, 0x00,
  0xb2, 0x48, 0xbb, 0xd4, 0x61, 0xf4, 0xd3, 0x12, 0x46, 0x6b, 0x29, 0x49,
  0x9c, 0xdd, 0xcd, 0x1a, 0x61, 0xd9, 0x43, 0xcb, 0x39, 0xba, 0x7b, 0xcc,
  0x68, 0xe7, 0x74, 0x56, 0x9f, 0xc0, 0x88, 0x38, 0x8c, 0x5c, 0x36, 0xcd,
  0x74, 0x1d, 0x45, 0x7e, 0x32, 0x4f, 0x35, 0x4f, 0x3e, 0x69, 0x24, 0xda,
  0xef, 0x75, 0x26, 0x66, 0x7c, 0x01, 0x00, 0x30, 0xf0, 0x05, 0x00, 0x80,
  0x2c, 0xde, 0x74, 0x01, 0xb3, 0x8c, 0x28, 0xe5, 0xac, 0xb8, 0xbc, 0x01,
  0xc4, 0x79, 0xcc, 0x7e, 0x53, 0x62, 0xe6, 0xc9, 0xe5, 0x22, 0xab, 0x2c,
  0x53, 0x5c, 0x9d, 0x19, 0x5f, 0x00, 0x00, 0x0c, 0x7c, 0x01, 0x00, 0x20,
  0x0b, 0x4b, 0x1d, 0x18, 0xee, 0xee, 0x46, 0x1b, 0xa3, 0x3f, 0x17, 0x66,
  0xb9, 0x12, 0xe7, 0x57, 0xca, 0x9a, 0x2d, 0x4f, 0x5d, 0xd0, 0xe7, 0x5f,
  0xcb, 0x4b, 0x99, 0x36, 0x56, 0x50, 0x3a, 0xa7, 0x32, 0x33, 0xbe, 0x00,
  0x00, 0x18, 0xf8, 0x02, 0x00, 0x40, 0x16, 0x96, 0x3a, 0x04, 0xd5, 0x72,
  0x77, 0xe7, 0x2a, 0x0f, 0x2d, 0x57, 0x62, 0xa3, 0x82, 0x6a, 0xa5, 0xf6,
  0x15, 0xfb, 0xbc, 0x57, 0xee, 0x15, 0x63, 0x10, 0x9f, 0x19, 0x5f, 0x00,
  0x00, 0x0c, 0x7c, 0x01, 0x00, 0x20, 0x0b, 0x4b, 0x1d, 0x6e, 0x98, 0x75,
  0x97, 0xf4, 0x95, 0xd2, 0xdb, 0x95, 0xff, 0xad, 0xd0, 0x57, 0x2d, 0x7d,
  0x2b, 0xb6, 0xf5, 0xd5, 0xe8, 0xfe, 0xcc, 0x5a, 0x6a, 0x67, 0x5c, 0x0e,
  0x1c, 0xb1, 0xe9, 0x86, 0xdf, 0x94, 0xbe, 0xbf, 0xbf, 0xa3, 0x37, 0x60,
  0x72, 0xbd, 0xf7, 0x65, 0xc6, 0x17, 0x00, 0x80, 0x12, 0xcc, 0xf8, 0x02,
  0x00, 0x7c, 0xd1, 0xbe, 0xef, 0xdf, 0xf5, 0xc2, 0x3a, 0x4c, 0x9f, 0xff,
  0x1f, 0xb8, 0x5f, 0x2e, 0x31, 0x5c, 0xf9, 0x5f, 0x25, 0x0c, 0x7a, 0xc5,
  0xdb, 0x2a, 0x9f, 0x3b, 0xfa, 0xb3, 0x5c, 0x53, 0xb9, 0x63, 0x78, 0x74,
  0x4e, 0xee, 0xd5, 0x06, 0xf9, 0x7f, 0x6e, 0xfc, 0xcc, 0xea, 0xff, 0xd1,
  0x4b, 0x2f, 0x56, 0xcc, 0xc9, 0xab, 0xb0, 0xd4, 0x01, 0x00, 0x00, 0x03,
  0x5f, 0x00, 0x00, 0xc8, 0xc2, 0x1a, 0xdf, 0x05, 0x44, 0x7b, 0x42, 0x42,
  0xaf, 0x52, 0xd4, 0x2a, 0xed, 0x87, 0xca, 0xd7, 0x2f, 0x62, 0x46, 0x2c,
  0xe5, 0xf8, 0x7d, 0x74, 0xbe, 0x3e, 0x98, 0xf1, 0x05, 0x00, 0xc0, 0xc0,
  0x17, 0x00, 0x00, 0xb2, 0xb0, 0xd4, 0x61, 0x61, 0xb3, 0x9e, 0x00, 0x10,
  0xad, 0x9d, 0xa3, 0xdb, 0x4f, 0xdf, 0x3e, 0xaf, 0xb6, 0x11, 0x43, 0xa6,
  0xf8, 0x77, 0x7e, 0xd7, 0x8a, 0x99, 0x68, 0x77, 0xf1, 0x8b, 0x9f, 0x98,
  0xf9, 0xd9, 0x53, 0x1d, 0x00, 0x00, 0xc0, 0xc0, 0x17, 0x00, 0x00, 0xd6,
  0x54, 0x7a, 0xa9, 0x83, 0x69, 0xff, 0xb9, 0xfd, 0x4c, 0x8e, 0xb8, 0xbd,
  0xdb, 0x9e, 0xd1, 0xfb, 0xdd, 0x8b, 0x7f, 0xe7, 0xf7, 0x6c, 0xf3, 0x82,
  0x2b, 0xed, 0xf1, 0xbb, 0x20, 0x7e, 0xc8, 0xcd, 0x8c, 0x2f, 0x00, 0x00,
  0x06, 0xbe, 0x00, 0x00, 0x90, 0x45, 0x89, 0xa5, 0x0e, 0x57, 0x4a, 0x8d,
  0xca, 0x28, 0xcf, 0xab, 0xdc, 0xe7, 0x57, 0x4a, 0xb1, 0x91, 0xfb, 0xb0,
  0xa5, 0x1c, 0xdc, 0x52, 0x86, 0x16, 0xff, 0xce, 0xef, 0x93, 0xd7, 0x9a,
  0xdf, 0x85, 0x9a, 0xf1, 0xd3, 0xb2, 0x3c, 0xa9, 0xd7, 0xd2, 0xa6, 0x11,
  0xf1, 0x29, 0x9e, 0x3f, 0x98, 0xf1, 0x05, 0x00, 0xc0, 0xc0, 0x17, 0x00,
  0x00, 0xb2, 0x28, 0xb1, 0xd4, 0x61, 0xf5, 0xe9, 0xfd, 0x5e, 0x65, 0xf1,
  0x59, 0x7d, 0x18, 0xa1, 0xfd, 0x91, 0xe3, 0x61, 0xc5, 0xf8, 0xec, 0xd5,
  0xe6, 0x6a, 0x4b, 0x1a, 0x56, 0x89, 0xff, 0xac, 0xe7, 0x57, 0xa9, 0x57,
  0x7e, 0x10, 0x27, 0x98, 0xf1, 0x05, 0x00, 0xc0, 0xc0, 0x17, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xdc, 0xbf, 0xe2,
  0xba, 0x9b, 0x88, 0x87, 0x0e, 0xf6, 0x22, 0x00, 0x00, 0x00, 0x00, 0x49,
  0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

#endif