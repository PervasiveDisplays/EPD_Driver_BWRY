/*
	EPD_Driver.cpp
	
	--COPYRIGHT--
  * Brief The drivers and functions of development board
  * Copyright (c) 2012-2023 Pervasive Displays Inc. All rights reserved.
  *  Authors: Pervasive Displays Inc.
  *  Redistribution and use in source and binary forms, with or without
  *  modification, are permitted provided that the following conditions
  *  are met:
  *  1. Redistributions of source code must retain the above copyright
  *     notice, this list of conditions and the following disclaimer.
  *  2. Redistributions in binary form must reproduce the above copyright
  *     notice, this list of conditions and the following disclaimer in
  *     the documentation and/or other materials provided with the
  *     distribution.
  *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined(ENERGIA)
#include "Energia.h"
#else
#include "Arduino.h"
#endif

#include "EPD_Driver.h"

// ---------- PUBLIC FUNCTIONS -----------

EPD_Driver::EPD_Driver(eScreen_EPD_t eScreen_EPD, pins_t board)
{
	spi_basic = board;
	
	// Type
	pdi_size = (uint16_t) (eScreen_EPD >> 8);

	uint16_t _screenSizeV = 0;
	uint16_t _screenSizeH = 0;
	uint16_t _screenDiagonal = 0;
	uint16_t _refreshTime = 0;
	
    switch (pdi_size)
    {
        case 0x15: // 1.54"

            _screenSizeV = 152; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 154;
            _refreshTime = 16;
			
			// Config registers according to screen size
			memcpy(register_data, reg_154, sizeof(reg_154));
            break;

        case 0x21: // 2.13"

            _screenSizeV = 212; // vertical = wide size
            _screenSizeH = 104; // horizontal = small size
            _screenDiagonal = 213;
            _refreshTime = 15;
			
			memcpy(register_data, reg_213, sizeof(reg_213));
            break;

        case 0x26: // 2.66"

            _screenSizeV = 296; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 266;
            _refreshTime = 15;
			
			memcpy(register_data, reg_266, sizeof(reg_266));
            break;

        default:

            break;
    }

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    image_data_size = (uint32_t) _screenSizeV * 2 * (uint32_t) (_screenSizeH / 8);
}

// CoG initialization function
//		Implements Tcon (COG) power-on and temperature input to COG
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::COG_initial()
{	
	pinMode( spi_basic.panelBusy, INPUT );     //All Pins 0
	
	pinMode( spi_basic.panelDC, OUTPUT );
	digitalWrite(spi_basic.panelDC, HIGH);
	pinMode( spi_basic.panelReset, OUTPUT );
	digitalWrite(spi_basic.panelReset, HIGH);
	pinMode( spi_basic.panelCS, OUTPUT );
	digitalWrite(spi_basic.panelCS, HIGH);

	SPISettings _settingScreen;
	_settingScreen = {8000000, MSBFIRST, SPI_MODE0};
	SPI.begin();
	SPI.beginTransaction(_settingScreen);

	// Power On COG driver sequence
	_reset(40, 20, 40, 10);
	
/* 	// This section is on reading the OTP (section 1.6 and 3 of the app note)
	// Not used here as OTP constants were used
	uint8_t idx_A4[]={0x15,0x00,0x01};
	_sendIndexData(0xA4,&idx_A4[0],3);
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
	
	// Read OTP function
	
	// Reset COG again
	digitalWrite(spi_basic.panelReset, LOW);
	delay(40);
	digitalWrite(spi_basic.panelReset, HIGH);
	delay(10);
	while( digitalRead( spi_basic.panelBusy ) != HIGH ); */
	
	// COG initial commands
	_sendIndexData(0x01,&register_data[0],1);// PWR
	_sendIndexData(0x00,&register_data[1],2);// PSR
	_sendIndexData(0x03,&register_data[3],3);// PFS
	_sendIndexData(0x06,&register_data[6],7);// BTST_P
	_sendIndexData(0x50,&register_data[13],1);// CDI
	_sendIndexData(0x60,&register_data[14],2);// TCON
	_sendIndexData(0x61,&register_data[16],4);// TRES
	_sendIndexData(0xe7,&register_data[20],1); 
	_sendIndexData(0xe3,&register_data[21],1);// PWS
	_sendIndexData(0x4d,&register_data[22],1);
	_sendIndexData(0xb4,&register_data[23],1);
	_sendIndexData(0xb5,&register_data[24],1);
	_sendIndexData(0xe9,&register_data[25],1);
	_sendIndexData(0x30,&register_data[26],1);// PLL
}

// CoG shutdown function
//		Shuts down the CoG and DC/DC circuit after all update functions
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::COG_powerOff()
{
	uint8_t  idx_02[]={0x00};//POFF
	_sendIndexData(0x02,&idx_02[0],1);
	while( digitalRead( spi_basic.panelBusy ) != HIGH );

	digitalWrite( spi_basic.panelDC, LOW );
	digitalWrite( spi_basic.panelCS, LOW );
	digitalWrite( spi_basic.panelBusy, LOW );
	delay( 120 );
	digitalWrite( spi_basic.panelReset, LOW );
}

// Global Update function
//		Implements global update functionality on either small/mid EPD
//		- INPUT:
//			- two image data (either BW and 0x00 or BW and BWR types)
void EPD_Driver::globalUpdate(const uint8_t * data1s)
{
	// Send image data
	_sendIndexData(0x10, data1s, image_data_size);

	uint8_t  idx_04[]={};//PON
	_sendIndexData(0x04,&idx_04[0],0);
	while( digitalRead( spi_basic.panelBusy ) != HIGH );

	uint8_t  idx_12[]={0x00};//DFR
	_sendIndexData(0x12,&idx_12[0],1);
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
}

// ---------- PROTECTED FUNCTIONS -----------

// SPI transfer function
//		Implements SPI transfer of index and data (consult user manual for EPD SPI process)
//		- INPUT:
//			- register address
//			- pointer to data char array
//			- length/size of data
void EPD_Driver::_sendIndexData( uint8_t index, const uint8_t *data, uint32_t len )
{	
	digitalWrite( spi_basic.panelDC, LOW );      //DC Low
	digitalWrite( spi_basic.panelCS, LOW );      //CS Low
	SPI.transfer(index);
	digitalWrite( spi_basic.panelCS, HIGH );     //CS High
	digitalWrite( spi_basic.panelDC, HIGH );     //DC High
	digitalWrite( spi_basic.panelCS, LOW );      //CS Low
	for ( uint32_t i = 0; i < len; i++ )
	{
		SPI.transfer(data[ i ]);
	}
	digitalWrite( spi_basic.panelCS, HIGH );     //CS High
}

// CoG driver power-on hard reset
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4)
{
	// note: group delays into one array
	delay(ms1);
    digitalWrite(spi_basic.panelReset, HIGH); // RES# = 1
    delay(ms2);
    digitalWrite(spi_basic.panelReset, LOW);
    delay(ms3);
    digitalWrite(spi_basic.panelReset, HIGH);
    delay(ms4);
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
}