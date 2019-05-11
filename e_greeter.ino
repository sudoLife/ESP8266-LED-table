void greet()
{
  uint8_t x, y;

for (x=1; x<=2; x++){
  for (y=2; y<=9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

leds[XYsafe(3,5)] = FOREGROUND;
leds[XYsafe(4,5)] = FOREGROUND;
leds[XYsafe(6,3)] = FOREGROUND;
leds[XYsafe(6,4)] = FOREGROUND;


for (x=5; x<=6; x++){
  for (y=2; y<=9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

for (x=9; x<=10; x++){
  for (y=2; y<=9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

  FastLED.show();
}
