# Introduction
 *  This library code implements the driving code of [Spectra 4 EPDs with iTC driver](https://www.pervasivedisplays.com/products/epd-product-selection/) made by [Pervasive Displays Inc (PDi)](https://www.pervasivedisplays.com/). This is compatible with [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/).
 *  It implements the global update mode (GU). However, the same code for fast and partial update are shared upon request. Contact [PDi](https://www.pervasivedisplays.com/technical-support/) for further details.
 *  The library supports the following EPD sizes: 1.54", 2.13", 2.66"
 *  This library was tested with Launchpad (Tiva-C) with TM4C123, MSP432P401R, Arduino M0 Pro, Raspberry Pi Pico, and ESP32DevKitC.


# Installation
  Download the ZIP file of this library and install as instructed in [Arduino](https://www.arduino.cc/en/guide/libraries) or Energia.

# Hardware Setup
 *  If using Launchpad (Tiva-C) with TM4C123 or MSP432P401R, the SPI pins are by default:
``` c++
// Using EXT3
    SCK = 7     // BROWN
    BUSY = 11   // RED
    D/C = 12    // ORANGE
    RST = 13    // YELLOW
    MOSI = 15   // BLUE
    ECSM = 19   // GRAY
    
 ```
 *  If using Arduino M0 Pro,
  ```
    SCK = 13 
    BUSY = 4  
    D/C = 5
    RST = 6
    MOSI = 12
    ECSM = 8
 ```
  *  If using Raspberry Pi Pico,
  ```
    SCK = 18 
    BUSY = 13  
    D/C = 12
    RST = 11
    MOSI = 19
    ECSM = 17
 ```
 
   *  If using ESP32DevKitC,
  ```
    SCK = 18 
    BUSY = 27  
    D/C = 26
    RST = 25
    MOSI = 23
    ECSM = 32
 ```
 
For further wiring guidance, check out the User Manual of [EXT3](https://www.pervasivedisplays.com/wp-content/uploads/2021/01/User-Manual-of-EXT3_Rev01_Jan-2021-1.pdf).

# EPD_Driver Demo
 *  The sample code implements a global update functionality for a [1.54" Spectra 4 EPD (E2154QS0F1)](https://www.pervasivedisplays.com/product/1-54-e-ink-displays/#ptab-5).  
 
 A BWRY(black, white, red and yellow) image is flashed.  
 
 *  The demo currently includes sample images for all the supported EPD sizes mentioned above. To implement global update demo on these other sizes, update the following lines
``` c++
//------------------------------------------------------------
// DEMO Image Set <Comment out when in User Mode>
// Screen Size: 154, 213, 266
#define SCREEN 154
#include "globalupdate_src/demoImageData.h"
```
 *  Then select the appropriate EPD size, development board and extension kit:
```
  // EPD_Driver epdtest(eScreen_EPD_154, boardLaunchPad_EXT3);
  EPD_Driver epdtest(eScreen_EPD_154, boardRaspberryPiPico_RP2040_EXT3);
```

#  Tech Support
 *  For more information, please visit [Pervasive Displays, Inc. (龍亭新技股份有限公司)](https://www.pervasivedisplays.com/)
 *  [PDI Wiki](https://docs.pervasivedisplays.com/)
 *  [PDi Product Line up](https://www.pervasivedisplays.com/products/)
 *  [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/)
 *  [24/7 Support Service](https://www.pervasivedisplays.com/technical-support/)

