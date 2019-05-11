#define FOREGROUND CRGB::Green
#define BACKGROUND CRGB::DarkBlue


// First player's figure
uint8_t player = 0;

uint8_t game_map[3][3];

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

void game_loop(WiFiClient client)
{
//	WiFiClient client;

	while (1)
	{
		/* client = server.available(); */
		if (client) {
			Serial.println("Client is here, ftw");
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
						// Should be a win screen here
						return;
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
		}
	}
}

void game_init(WiFiClient client)
{
	uint8_t x, y;

  for (y = 0; y < 3; y++)
  {
    for (x = 0; x < 3; x++)
    {
      // Filling it w/ value that does not represent any player
      game_map[y][x] = 2;
    }
  }

	game_loop(client);
}
