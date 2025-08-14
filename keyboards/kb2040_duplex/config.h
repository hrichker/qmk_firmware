#pragma once
#include "config_common.h"

/* USB descriptor */
#define VENDOR_ID    0x1209
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER You
#define PRODUCT      CustomKB

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
#define ROW_DIODES { R2C, C2R, R2C, C2R, R2C, C2R }

#define MATRIX_IO_DELAY 5
#define DEBOUNCE        5
