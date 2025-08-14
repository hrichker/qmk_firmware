/*
Copyright 2025 Harleyrichker

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB descriptor
 * Moved to info.json: vendor ID, product ID, device version, manufacturer, and keyboard name.
 */

/* Matrix size: 6 rows × 18 "duplex" columns (2 per physical column) */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* Row & column pins (KB2040 uses GPxx names) */
#define MATRIX_ROW_PINS { GP26, GP27, GP28, GP29, GP1,  GP20 }
#define MATRIX_COL_PINS { \
    GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP19, \
    GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP19 \
}

/* Diode directions alternate by row (Japanese duplex) */
#define R2C false
#define C2R true
#define ROW_DIODES { R2C, C2R, R2C, C2R, R2C, C2R }

#define MATRIX_IO_DELAY 5
#define DEBOUNCE        5
