/*
	demoImageData.h
  DEMO set of Image Data
*/

// Load Global Update Images
#if (SCREEN==154)   //1.54"
#include "image_data\154E5SE_testimage.c"
#define BW_monoBuffer        (uint8_t *) & testImage
#elif(SCREEN==213)   //2.13"
#include "image_data\213E5SE_testimage.c"
#define BW_monoBuffer        (uint8_t *) & testImage
#elif(SCREEN==266)   //2.66"
#include "image_data\266E5SE_testimage.c"
#define BW_monoBuffer        (uint8_t *) & testImage
#endif