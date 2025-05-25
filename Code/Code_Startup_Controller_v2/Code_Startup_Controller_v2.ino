// GR Yaris Startup Controller
// Will Norman
// May 2025
// For use with PCB v2.0
// Code updates for ABRE

// Define all output pins that drive car button presses
#define SWITCH_MODE 10   // sport / track (slide switch determines which chassis signal wire is pulled low)
#define SWITCH_LDA  14   // lane departure alert
#define SWITCH_ASS  15   // auto stop start
#define SWITCH_IMT  16   // iMT
#define SWITCH_ESC  17   // ESC / traction

// Define all output pins of indicator LEDs (flash corresponding LED when button is pressed)
#define LED_SPORT   4   // sport mode led
#define LED_TRACK   3   // track mode led
#define LED_LDA     2   // lane departure led
#define LED_ASS     1   // auto stop/start led
#define LED_IMT     0   // imt led
#define LED_ESC     18  // esc led

// Define input pins (connected to slide switches)
#define INPUT_ESC   5   // Input to determine ESC switch state - expert mode or esc fully off
#define INPUT_MODE  6   // Input to determine track/sport switch state

void setup() {

    // Configure pins as outputs for button 'pressers'
    pinMode(SWITCH_MODE, OUTPUT);
    pinMode(SWITCH_LDA, OUTPUT);
    pinMode(SWITCH_ASS, OUTPUT);
    pinMode(SWITCH_IMT, OUTPUT);
    pinMode(SWITCH_ESC, OUTPUT);
    
    // Configure pins as outputs for indicator LEDs
    pinMode(LED_TRACK, OUTPUT);
    pinMode(LED_SPORT, OUTPUT);
    pinMode(LED_LDA, OUTPUT);
    pinMode(LED_ASS, OUTPUT);
    pinMode(LED_IMT, OUTPUT);
    pinMode(LED_ESC, OUTPUT); 

    // Ensure all output pins are driven low
    digitalWrite(SWITCH_MODE, LOW);
    digitalWrite(SWITCH_LDA, LOW);
    digitalWrite(SWITCH_ASS, LOW);
    digitalWrite(SWITCH_IMT, LOW);
    digitalWrite(SWITCH_ESC, LOW);

    digitalWrite(LED_TRACK, LOW);
    digitalWrite(LED_SPORT, LOW);
    digitalWrite(LED_LDA, LOW);
    digitalWrite(LED_ASS, LOW);
    digitalWrite(LED_IMT, LOW);
    digitalWrite(LED_ESC, LOW);

    // Configure input pins (slide switch inputs)
    pinMode(INPUT_ESC, INPUT);
    pinMode(INPUT_MODE, INPUT);

    // Delay 10s to allow car to startup
    delay(10000); // increased from 3s
    
    // Read states of inputs
    bool STATE_ESC = digitalRead(INPUT_ESC);    // HIGH for expert (short press), LOW for ESC fully off (long press)
    bool STATE_MODE = digitalRead(INPUT_MODE);  // HIGH for track, LOW for sport

    // Press buttons sequentially (turn corresponding LED on with button press)

    // LDA on
    digitalWrite(SWITCH_LDA, HIGH);
    digitalWrite(LED_LDA, HIGH);
    delay(3500);
    // LDA off
    digitalWrite(SWITCH_LDA, LOW);
    digitalWrite(LED_LDA, LOW);
    delay(500);

    // Auto stop/start on
    digitalWrite(SWITCH_ASS, HIGH);
    digitalWrite(LED_ASS, HIGH);
    delay(500);
    // Auto stop/start off
    digitalWrite(SWITCH_ASS, LOW);
    digitalWrite(LED_ASS, LOW);
    delay(500);

    // Mode select
    // Turn appropriate LED on
    if(STATE_MODE){
        digitalWrite(LED_TRACK, HIGH);
    }else{
        digitalWrite(LED_SPORT, HIGH);
    }
    // Mash mode button 4 times to guarantee button registration
    for(int i=0;i<4;i++){
      digitalWrite(SWITCH_MODE, HIGH);
      delay(500);
      digitalWrite(SWITCH_MODE, LOW);
      delay(500);
    }
    // Switch mode LEDs off
    digitalWrite(LED_TRACK, LOW);
    digitalWrite(LED_SPORT, LOW);
    delay(500);

    // ESC on (must happen after sport/track mode has been selected)
    digitalWrite(SWITCH_ESC, HIGH);
    digitalWrite(LED_ESC, HIGH);
    delay(500);
    // ESC off, check input state to determine if short or long press required
    if(STATE_ESC){
        // If true, short press for expert mode
        digitalWrite(SWITCH_ESC, LOW);
        digitalWrite(LED_ESC, LOW);
    }else{
        // Else long press for ESC fully off (4s total)
        delay(3500);
        digitalWrite(SWITCH_ESC, LOW);
        digitalWrite(LED_ESC, LOW);
    }
    delay(500);

    // iMT on (now last in queue)
    digitalWrite(SWITCH_IMT, HIGH);
    digitalWrite(LED_IMT, HIGH);
    delay(500);
    // iMT off
    digitalWrite(SWITCH_IMT, LOW);
    digitalWrite(LED_IMT, LOW);
}

void loop() {
    // Nothing to do in loop
}