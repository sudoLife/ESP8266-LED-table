#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

const char *ssid = "bless_gun_of_witch";

// This shit must be at least 8 characters!!!
const char *password = "toribbbb";

WiFiServer server(80);


#define LED_PIN 5
#define BRIGHTNESS 64
#define FOREGROUND CRGB::Green
#define BACKGROUND CRGB::DarkBlue

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

// Params for width and height
const uint8_t kMatrixWidth = 12;
const uint8_t kMatrixHeight = 12;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

// First player's figure
int player = 0;

char game_map[3][3];
// [ MATRIX FUNCTIONS ] ------------------------
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

// [ MATRIX FUNCTIONS END ] -------------------------



// [ TIC TAC TOE FUNCTIONS ] --------------------

char draw(uint8_t x, uint8_t y)
{
  if (x > 2 || y > 2 || game_map[y][x] != 2) {
    return 1;
  }
  game_map[y][x] = player;
  x *= 4;
  y *= 4;
  
  unsigned int counter;
  // First player
  if (!player) {
    for (counter = 0; counter < 4; counter++) {
      leds[ XYsafe(x + counter, y + counter) ] = FOREGROUND;
    }
  }
  // Second player
  else {
    x++;
    y++;
    leds[ XYsafe(x, y) ] = FOREGROUND;
    leds[ XYsafe(x + 1, y) ] = FOREGROUND;
    leds[ XYsafe(x, y + 1) ] = FOREGROUND;
    leds[ XYsafe(x + 1, y + 1) ] = FOREGROUND;
  }

  FastLED.show();
  delay(1);

  return 0;
}
char is_winner()
{
  int x, y;
  char won;
  //check vertically
  for (x = 0; x < 3; x++)
  {
    won = 1;
    for (y = 0; y < 3; y++)
    {
      if (game_map[y][x] != player)
      {
        won = 0;
        break;
      }
    }
    if (won) {
      return won;
    }
  }

  if (won) {
    return won;
  }

  // check horizontally
  for (y = 0; y < 3; y++)
  {
    won = 1;
    for (x = 0; x < 3; x++)
    {
      if (game_map[y][x] != player)
      {
        won = 0;
        break;
      }
    }
    if (won) {
      return won;
    }
  }

  if (won) {
    return won;
  }
  else {
    won = 1;
  }
  
  // check diagonally
  
  for (x = 0, y = 0; x < 3 && y < 3; x++, y++)
  {
    if (game_map[y][x] != player) {
      won = 0;
      break;
    }
  }

  if (won) {
    return won;
  }
  else {
    won = 1;
  }

  
  for (x = 2, y = 0; x >= 0 && y < 3; x--, y++)
  {
    if (game_map[y][x] != player) {
      won = 0;
      break;
    }
  }

  return won;
}

char is_deadlock()
{
  unsigned int x, y;

  for (y = 0; y < 3; y++)
  {
    for (x = 0; x < 3; x++)
    {
      if (game_map[y][x] == 2) {
        return 0;
      }
    }
  }
  return 1;
}

void clear_board()
{
  uint16_t counter;

  for (counter = 0; counter < kMatrixWidth * kMatrixHeight; counter++)
  {
    leds[counter] = BACKGROUND;
  }

  FastLED.show();
  delay(1);
}

// [ TIC TAC TOE FUNCTIONS END ] ---------------------

// [ GREET THE PLAYER ]

void greet(){

for (int x=1; x=<2; x++){
  for (int y=2; y=<9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

leds[XYsafe(3,5)] = FOREGROUND;
leds[XYsafe(4,5)] = FOREGROUND;
leds[XYsafe(6,3)] = FOREGROUND;
leds[XYsafe(6,4)] = FOREGROUND;


for (int x=5; x=<6; x++){
  for (int y=2; y=<9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

for (int x=9; x=<10; x++){
  for (int y=2; y=<9; y++){
    leds[XYsafe(x,y)] = FOREGROUND;
  }
}

}

// [END GREETING, TELL PLAYERS TO FUCK OFF AND PLAY ALREADY]

void setup() {

  int x, y;

  for (y = 0; y < 3; y++)
  {
    for (x = 0; x < 3; x++)
    {
      // Filling it w/ value that does not represent any player
      game_map[y][x] = 2;
    }
  }

  greet();

  delay(2000);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );

  // WE need a greeting function
  clear_board();

  // Networking
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\r');
        if(command.length() != 3) {
          continue;
        }
        Serial.print("Command: ");
        Serial.print(command);
        Serial.print("\n");
        if (draw(command[2] - '1', command[0] - '1'))
        {
          continue;
        }
        if (is_winner() || is_deadlock()) {
          while (1) {
            clear_board();
          }
        }
        Serial.print("player = ");
        Serial.print(player);
        Serial.print("\n");
        if (player)
        {
          player = 0;
        }
        else {
          Serial.print("Changing player to 1");
          player = 1;
        }
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}
