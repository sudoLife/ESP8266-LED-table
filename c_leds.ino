#include <FastLED.h>

#define BRIGHTNESS  64
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define LED_PIN     5

// Params for width and height
const uint8_t kMatrixWidth = 12;
const uint8_t kMatrixHeight = 12;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);


void init_leds()
{
	FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
	FastLED.setBrightness( BRIGHTNESS );
	FastLED.setMaxPowerInMilliWatts(30000);
}


uint16_t XY( uint8_t x, uint8_t y)
{
	uint16_t i;

	if( kMatrixSerpentineLayout == false) {
		i = (y * kMatrixWidth) + x;
	}

	if( kMatrixSerpentineLayout == true) {
		if( y & 0x01) {
			// Odd rows run backwards
			uint8_t reverseX = (kMatrixWidth - 1) - x;
			i = (y * kMatrixWidth) + reverseX;
		} else {
			// Even rows run forwards
			i = (y * kMatrixWidth) + x;
		}
	}

	return i;
}

uint16_t XYsafe( uint8_t x, uint8_t y)
{
	if( x >= kMatrixWidth) return -1;
	if( y >= kMatrixHeight) return -1;
	return XY(x,y);
}
