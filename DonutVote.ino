
/**
 * Six button Arduino keyboard proxy
 * (Use pins 1-6)
 */

// Number of buttons.
const int buttons = 7;
const long debounceDelay = 50;

// Current reading from the input pin.
int buttonState[buttons] = {LOW};
// Previous reading from the input pin.
int lastButtonState[buttons] = {LOW};

// Last time the output pin was toggled.
long lastDebounceTime[buttons] = {0};


// Main setup.
void setup() {
  // Set inputs.
  for (int i = 1; i <= buttons; i++) {
    pinMode(i, INPUT);
  }
  // Initialize keyboard control.
  Keyboard.begin();
  // Debug.
  //Serial.begin(9600);
}


// Main loop.
void loop() {

  // Check all buttons.
  int reading[buttons];
  for (int i = 1; i <= buttons; i++) {

    // Read button press.
    reading[i] = digitalRead(i);

    // If the switch changed, due to noise or pressing.
    if (reading[i] != lastButtonState[i]) {
      // Reset the debouncing timer.
      lastDebounceTime[i] = millis();
    } 

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
  
      // If the button state has changed.
      if (reading[i] != buttonState[i]) {
        buttonState[i] = reading[i];
  
        // Press key if the new button state is HIGH.
        if (buttonState[i] == HIGH) {
          // Type conversion. (Obviously, got lazy and annoyed.)
          char pressChar;
          switch (i) {
            case 1:
              pressChar = '1';
              break;
            case 2:
              pressChar = '2';
              break;
            case 3:
              pressChar = '3';
              break;
            case 4:
              pressChar = '4';
              break;
            case 5:
              pressChar = '5';
              break;
            case 6:
              pressChar = '6';
              break;
          }
          // Debug.
          // Serial.println(pressChar);

          // Press that key!
          Keyboard.press(pressChar);
          Keyboard.release(pressChar);
        }
      }
    }

    // Save the reading. Next time it'll be the lastButtonState.
    lastButtonState[i] = reading[i];

  } // End buttons loop.

}

