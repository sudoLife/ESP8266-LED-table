#define FIRST_PLAYER CRGB::Green
#define SECOND_PLAYER CRGB::Red
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
      leds[ XYsafe(x + counter, y + counter) ] = FIRST_PLAYER;
    }
  }
  // Second player
  else {
    x++;
    y++;
    leds[ XYsafe(x, y) ] = SECOND_PLAYER;
    leds[ XYsafe(x + 1, y) ] = SECOND_PLAYER;
    leds[ XYsafe(x, y + 1) ] = SECOND_PLAYER;
    leds[ XYsafe(x + 1, y + 1) ] = SECOND_PLAYER;
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

void print_winner()
{
	if (!player) {
		leds[ XYsafe(5, 1) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 1) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 2) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 3) ] = FIRST_PLAYER;
		leds[ XYsafe(5, 4) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 4) ] = FIRST_PLAYER;
		leds[ XYsafe(7, 4) ] = FIRST_PLAYER;
		leds[ XYsafe(0, 6) ] = FIRST_PLAYER;
		leds[ XYsafe(4, 6) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 6) ] = FIRST_PLAYER;
		leds[ XYsafe(8, 6) ] = FIRST_PLAYER;
		leds[ XYsafe(11, 6) ] = FIRST_PLAYER;
		leds[ XYsafe(0, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(4, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(8, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(9, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(11, 7) ] = FIRST_PLAYER;
		leds[ XYsafe(0, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(2, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(4, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(8, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(10, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(11, 8) ] = FIRST_PLAYER;
		leds[ XYsafe(1, 9) ] = FIRST_PLAYER;
		leds[ XYsafe(3, 9) ] = FIRST_PLAYER;
		leds[ XYsafe(6, 9) ] = FIRST_PLAYER;
		leds[ XYsafe(8, 9) ] = FIRST_PLAYER;
		leds[ XYsafe(11, 9) ] = FIRST_PLAYER;
	} else {
		leds[ XYsafe(5, 1) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 1) ] = SECOND_PLAYER;
		leds[ XYsafe(7, 2) ] = SECOND_PLAYER;
		leds[ XYsafe(5, 3) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 3) ] = SECOND_PLAYER;
		leds[ XYsafe(5, 4) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 4) ] = SECOND_PLAYER;
		leds[ XYsafe(7, 4) ] = SECOND_PLAYER;
		leds[ XYsafe(0, 6) ] = SECOND_PLAYER;
		leds[ XYsafe(4, 6) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 6) ] = SECOND_PLAYER;
		leds[ XYsafe(8, 6) ] = SECOND_PLAYER;
		leds[ XYsafe(11, 6) ] = SECOND_PLAYER;
		leds[ XYsafe(0, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(4, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(8, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(9, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(11, 7) ] = SECOND_PLAYER;
		leds[ XYsafe(0, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(2, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(4, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(8, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(10, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(11, 8) ] = SECOND_PLAYER;
		leds[ XYsafe(1, 9) ] = SECOND_PLAYER;
		leds[ XYsafe(3, 9) ] = SECOND_PLAYER;
		leds[ XYsafe(6, 9) ] = SECOND_PLAYER;
		leds[ XYsafe(8, 9) ] = SECOND_PLAYER;
		leds[ XYsafe(11, 9) ] = SECOND_PLAYER;
	}
	FastLED.show();
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
					if (draw(command[0] - '1', command[2] - '1'))
					{
						continue;
					}
					if (is_winner()) {
						// Should be a win screen here
						clear_board();
						print_winner();
						return;
					}

					if (is_deadlock()) {
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

	clear_board();
	game_loop(client);
}
