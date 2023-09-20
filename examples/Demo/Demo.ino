/*
  EPD_Driver_demo
  This is a demo sketch for the E5 series EPD from Pervasive Displays, Inc.
  The aim of this demo and the library used is to introduce CoG usage and global update functionality.
  
  Hardware Suggested:
  * Launchpad MSP432P401R or (Tiva-C) with TM4C123/Arduino M0 Pro/Raspberry Pi Pico
  * EPD Extension Kit (EXT3-1)
  * E5 EPD
  * 10-pin rainbow jumper cable
*/

#include <EPD_Driver.h>

// DEMO Image Set <Comment out when in User Mode>
// Screen Size: 154, 213, 266
#define SCREEN 154
#include "globalupdate_src/demoImageData.h"
//------------------------------------------------------------

void setup()
{
  EPD_Driver epdtest(eScreen_EPD_154, boardRaspberryPiPico_RP2040_EXT3);
  
  // Initialize CoG
  epdtest.COG_initial();

  // Global Update Call
  epdtest.globalUpdate(BW_monoBuffer);

  // Turn off CoG
  epdtest.COG_powerOff();
}

void loop()
{
  delay(1000);
}
