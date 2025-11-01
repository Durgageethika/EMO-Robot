#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    player.volume(10); // Set volume to a comfortable level (0 to 30)
    Serial.println("Send '1' to '6' to play track 001 to 006.");
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}
void loop() {
  // Check if data is available in the serial input
  if (Serial.available()) {
    char input = Serial.read();

    // Ignore newline characters
    if (input == '\n' || input == '\r') {
      return; // Skip this iteration
    }

    // Check if the input is '1' to '6' and play the corresponding track
    if (input >= '1' && input <= '6') {
      int trackNumber = input - '0'; // Convert char to int (1 to 6)
      player.play(trackNumber); // Play track 001 to 006
      Serial.print("Playing track: 00");
      Serial.println(trackNumber);
    } else {
      Serial.println("Invalid input. Send '1' to '6'.");
    }
  }

  // Check if the current track has finished playing and handle as needed
  if (player.available()) {
    if (player.readType() == DFPlayerPlayFinished) {
      Serial.println("Track finished playing.");
    }
  }
}
