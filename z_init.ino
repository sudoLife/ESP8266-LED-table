void setup() {
	// Let's set up diodes
	init_serial();
	init_wifi();
	init_leds();

  delay(2000);

  // WE need a greeting function
  clear_board();

  // Networking
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\r');
				Serial.println(command);
				if (command == "play")
				{
					game_init(client);
					Serial.println("Time to play");
				}
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}
