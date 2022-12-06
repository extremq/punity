//
// Created by god on 03.11.2022.
//

/*
 * Copied defines from adafruit's libarry.
 * https://github.com/adafruit/Adafruit-ST7735-Library
 */
#ifndef ST7735_DEFINES_H
#define ST7735_DEFINES_H

#define X_START 2
#define Y_START 3

#define ST77XX_SWRESET 0x01
#define ST77XX_SLPOUT 0x11
#define ST77XX_NORON 0x13
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

// Some register settings
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#endif //ST7735_DEFINES_H
