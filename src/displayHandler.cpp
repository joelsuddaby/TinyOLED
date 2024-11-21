#include "displayHandler.h"
#include <U8g2lib.h>
#include <Wire.h>
// Define and initialize the u8g2 object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 0x3C, 6, 5);  // Address 0x3C, Pins SDA=GPIO6, SCL=GPIO5
int width = 72;
int height = 40;
int xOffset = 30; // Center horizontally
int yOffset = 12; // Center vertically

void OLEDInit() {
    u8g2.begin();  // Initialize the OLED display
    u8g2.setContrast(255);  // Set maximum contrast
    u8g2.setBusClock(400000);  // Set I2C bus speed to 400 kHz
    u8g2.setFont(u8g2_font_ncenB10_tr);  // Set the font
}

bool OLEDUpdate() {
    u8g2.clearBuffer();
    // Draw the border
    u8g2.drawFrame(xOffset, yOffset, width, height);
    // Display the resolution in the middle of the screen
    u8g2.setCursor(xOffset + 15, yOffset + 25);
    u8g2.printf("Hello");
    u8g2.sendBuffer();
    return false;
}