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

#include "quantum.h"

/* Row diode orientation: false = row→col, true = col→row */
static const bool row_col_reversed[MATRIX_ROWS] =
    ROW_DIODES;  // expands to {false,true,false,true,false,true}

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS/2] = { GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP19 };

static matrix_row_t matrix_state[MATRIX_ROWS];

static void matrix_init_custom(void) {
    /* Set rows to high‑impedance */
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        setPinInputHigh(row_pins[r]);
    }
    /* Columns as inputs with pull‑ups */
    for (uint8_t c = 0; c < MATRIX_COLS/2; c++) {
        setPinInputHigh(col_pins[c]);
    }
}

static bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        bool reversed = row_col_reversed[row];

        if (!reversed) {                  // row→col
            setPinOutput(row_pins[row]);
            writePinLow(row_pins[row]);
        }

        for (uint8_t col = 0; col < MATRIX_COLS/2; col++) {
            pin_t pin = col_pins[col];
            bool pressed;

            if (reversed) {               // col→row
                setPinOutput(pin);
                writePinLow(pin);
                pressed = !readPin(row_pins[row]);
                setPinInputHigh(pin);
            } else {
                pressed = !readPin(pin);
            }

            uint8_t matrix_col = col*2 + (reversed ? 1 : 0);
            if (pressed) {
                current_matrix[row] |=  (1 << matrix_col);
            } else {
                current_matrix[row] &= ~(1 << matrix_col);
            }
        }

        if (!reversed) {
            setPinInputHigh(row_pins[row]);
        }
    }
    return 1;
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix_state[i] = 0;
    }
    matrix_init_custom();
}

uint8_t matrix_scan(void) {
    return matrix_scan_custom(matrix_state);
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix_state[row];
}

void matrix_print(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        uprintf("%02u: %08lx\n", row, (long)matrix_state[row]);
    }
}
