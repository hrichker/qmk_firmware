#include "quantum.h"

/* Row diode orientation: false = row→col, true = col→row */
static const bool row_col_reversed[MATRIX_ROWS] =
    ROW_DIODES;  // expands to {false,true,false,true,false,true}

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS/2] = { GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP19 };

void matrix_init_custom(void) {
    /* Set rows to high‑impedance */
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        setPinInputHigh(row_pins[r]);
    }
    /* Columns as inputs with pull‑ups */
    for (uint8_t c = 0; c < MATRIX_COLS/2; c++) {
        setPinInputHigh(col_pins[c]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
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
