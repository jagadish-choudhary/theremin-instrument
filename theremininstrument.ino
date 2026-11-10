// --- PIN DEFINITIONS ---
const int trig_pin = 7;
const int echo_pin = 6;
const int speakerPin = 8; 
const int buttonPin = 2; // Our new Mute Pedal

// --- SYSTEM STATES ---
bool isPlaying = true;      // Start with the music ON
int lastButtonState = HIGH; // Keeps track of the button

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(speakerPin, OUTPUT);
  
  // Activate the Arduino's hidden internal resistor!
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("Theremin Active! Press the button to toggle Mute.");
}

void loop() {
  // ==========================================
  // 1. READ THE MUTE PEDAL
  // ==========================================
  int buttonState = digitalRead(buttonPin);

  // If the button is pressed down
  if (buttonState == LOW && lastButtonState == HIGH) {
    isPlaying = !isPlaying;  // Flip the state
    
    if(isPlaying) {
      Serial.println("\n--- Music ON ---");
    } else {
      Serial.println("\n--- Music MUTED ---");
    }
    
    delay(200); // A tiny pause to prevent double-triggering
  }
  
  lastButtonState = buttonState; // Save the state for the next loop

  // ==========================================
  // 2. PLAY THE THEREMIN (If not muted)
  // ==========================================
  if (isPlaying == true) {
    
    // Send the ultrasonic ping
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    
    // Calculate distance
    float timing = pulseIn(echo_pin, HIGH, 30000); 
    float distance = (timing * 0.034) / 2;

    // Play the notes
    if (distance > 5 && distance < 50) {
      int pitch = map(distance, 5, 50, 200, 3500);
      tone(speakerPin, pitch);
      
      // THE MISSING PRINT LINES ARE BACK!
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" cm | Pitch: ");
      Serial.println(pitch);
      
    } else {
      noTone(speakerPin);
    }
    
  } else {
    // If the system is MUTED, force the speaker to be completely quiet
    noTone(speakerPin);
  }
  
  delay(20); 
}