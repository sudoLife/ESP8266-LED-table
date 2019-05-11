void greet()
{
  uint8_t x, y;

	for (x = 1; x < 3; x++) {
		for (y = 2; y < 10; y++) { 
			leds[ XYsafe(x,y) ] = FOREGROUND;
		}
	}

	for (x = 3; x < 5; x++) {
		for (y = 5; y < 7; y++) {
			leds[ XYsafe(x, y) ] = FOREGROUND;
		}
	}

	for (x = 5; x < 7; x++) {
		for (y = 2; y < 10; y++) {
			leds[ XYsafe(x,y) ] = FOREGROUND;
		}
	}

	for (x = 9; x < 11; x++) {
		for (y = 2; y < 10; y++) {
			leds[ XYsafe(x,y) ] = FOREGROUND;
		}
	}

  FastLED.show();
	delay(5000);
}
