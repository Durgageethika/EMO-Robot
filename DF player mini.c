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
    player.volume(5); // Set volume to a comfortable level (0 to 30)
    Serial.println("Send '1' to play track 001 or '2' to play track 002.");
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  // Check if data is available in the serial input
  if (Serial.available()) {
    char input = Serial.read();

    // Check if the input is '1' or '2' and play the corresponding track
    if (input == '1') {
      player.play(1); // Play 001.mp3
      Serial.println("Playing track: 001");
    } else if (input == '2') {
      player.play(2); // Play 002.mp3
      Serial.println("Playing track: 002");
    } else {
      Serial.println("Invalid input. Send '1' or '2'.");
    }
  }

  // Check if the current track has finished playing and handle as needed
  if (player.available()) {
    if (player.readType() == DFPlayerPlayFinished) {
      Serial.println("Track finished playing.");
    }
  }
}
