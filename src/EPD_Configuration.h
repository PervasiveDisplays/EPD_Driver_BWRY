///
/// @file EPD_Configuration.h
/// @brief Configuration of the options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// 1- List of supported Pervasive Displays screens
/// 2- List of pre-configured boards
/// 3- Register initializations
///
/// @author Pervasive Displays, Inc.
/// @date 20 September 2023
///
/// @copyright (c) Pervasive Displays, Inc., 2010-2021
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for personal usage
/// @n Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// * Advanced edition: for professionals or organisations, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
#include "stdint.h"

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE
\
///
/// @name 1- List of supported Pervasive Displays screens
/// @see https://www.pervasivedisplays.com/products/
/// @{
///
#define eScreen_EPD_t uint32_t ///< screen type
///
/// * Monochrome screens and default colour screens
#define eScreen_EPD_154 (uint32_t)0x1509 ///< reference xE2154CSxxx
#define eScreen_EPD_213 (uint32_t)0x2100 ///< reference xE2213CSxxx
#define eScreen_EPD_266 (uint32_t)0x2600 ///< reference xE2266CSxxx

/// @}

///
/// @name Frame Frame-buffer sizes
/// @details Frame-buffer size = width * height / 8 * depth, uint32_t
/// @note Only one frame buffer is required.
/// @n Depth = 2 for black-white-red screens and monochrome screens
///

#define frameSize_EPD_EXT3_154 (uint32_t)(2888)
#define frameSize_EPD_EXT3_213 (uint32_t)(2756)
#define frameSize_EPD_EXT3_266 (uint32_t)(5624)

/// @name 2- List of pre-configured boards
/// @{

///
/// @brief Not connected pin
///
#define NOT_CONNECTED (uint8_t)0xff

///
/// @brief Board configuration structure
///

struct pins_t
{
    // uint8_t panelSCL;
    ///< EXT3 pin 1 Black -> +3.3V
    ///< EXT3 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3 pin 3 Red
    uint8_t panelDC; ///< EXT3 pin 4 Orange
    uint8_t panelReset; ///< EXT3 pin 5 Yellow
    ///< EXT3 pin 6 Green -> SPI MISO
    ///< EXT3 pin 7 Blue -> SPI MOSI
    // uint8_t panelSDA;
    uint8_t panelCS;
    uint8_t panelON_EXT2;
    uint8_t panelSPI43_EXT2; ///< BS
    uint8_t flashCS;
};

///
/// @brief MSP430 and MSP432 LaunchPad configuration, tested
///
const pins_t boardLaunchPad_EXT3 =
{
    .panelBusy = 11, ///< EXT3 pin 3 Red
    .panelDC = 12, ///< EXT3 pin 4 Orange
    .panelReset = 13, ///< EXT3 pin 5 Yellow
    .panelCS = 19,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = NOT_CONNECTED
};

///
/// @brief Raspberry Pi Pico with default RP2040 configuration, tested
///
const pins_t boardRaspberryPiPico_RP2040_EXT3 =
{
    .panelBusy = 13, ///< EXT3 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 pin 5 Yellow -> GP11
    .panelCS = 17,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = 10
};

///
/// @brief Arduino M0Pro configuration, tested
///
const pins_t boardArduinoM0Pro_EXT3 =
{
    .panelBusy = 4, ///< EXT3 pin 3 Red
    .panelDC = 5, ///< EXT3 pin 4 Orange
    .panelReset = 6, ///< EXT3 pin 5 Yellow
    .panelCS = 8,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = NOT_CONNECTED
};

///
/// @brief Espressif ESP32-DevKitC
/// @note Numbers refer to GPIOs not pins
///
const pins_t boardESP32DevKitC_EXT3 =
{
    .panelBusy = 27, ///< EXT3 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 pin 5 Yellow -> GPIO25
    .panelCS = 32, ///< EXT3 pin 9 Grey -> GPIO32
	.panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED, ///< BS
    .flashCS = 33 ///< EXT3 pin 8 Violet -> GPIO33
};

/// @}

///
/// @name 3- Register initializations
/// @{
///

const uint8_t reg_154[] = {
	0x07, 
	0x0f, 0x29, 
	0x10, 0x54, 0x44,
	0x0f, 0x00, 0x3f, 0x0a, 0x25, 0x0a, 0x20,
	0x37,
	0x02, 0x02,
	0x00, 0x98, 0x00, 0x98,
	0x1c,
	0x22,
	0x78,
	0xd0,
	0x03,
	0x01,
	0x08};
const uint8_t reg_213[] = {
	0x07, 
	0x0f, 0x29, 
	0x10, 0x54, 0x44,
	0x05, 0x00, 0x3f, 0x0a, 0x25, 0x0d, 0x16,
	0x37,
	0x02, 0x02,
	0x00, 0x68, 0x00, 0xd4,
	0x1c,
	0x22,
	0x78,
	0xd0,
	0x03,
	0x01,
	0x08};
const uint8_t reg_266[] = {
	0x07, 
	0x0f, 0x29, 
	0x10, 0x54, 0x44,
	0x05, 0x00, 0x3f, 0x0a, 0x25, 0x12, 0x1a,
	0x37,
	0x02, 0x02,
	0x00, 0x98, 0x01, 0x28,
	0x1c,
	0x22,
	0x78,
	0xd0,
	0x00,
	0x01,
	0x08};	

/// @}

#endif // hV_CONFIGURATION_RELEASE
