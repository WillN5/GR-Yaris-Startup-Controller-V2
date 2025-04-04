// Will Norman
// April 2025
// GR Yaris Startup Controller
// For use with PCB v2.0

// Define all output pins that drive car button presses
#define SWITCH_MODE 10   // sport / track
#define SWITCH_LDA  14   // lane departure alert
#define SWITCH_ASS  15   // auto stop start
#define SWITCH_IMT  16   // iMT
#define SWITCH_ESC  17   // ESC / traction

// Define all output pins of indicator LEDs
#define LED_SPORT   4
#define LED_TRACK   3
#define LED_LDA     2
#define LED_ASS     1
#define LED_IMT     0
#define LED_ESC     18

// Define input pins
#define INPUT_ESC   5   // Input to determine ESC switch state - short (expert), long (all off)
#define INPUT_MODE  6   // Input to determine track/sport switch state

void setup() {

    // Configure output pins for button 'pressers'
    pinMode(SWITCH_MODE, OUTPUT);
    pinMode(SWITCH_LDA, OUTPUT);
    pinMode(SWITCH_ASS, OUTPUT);
    pinMode(SWITCH_IMT, OUTPUT);
    pinMode(SWITCH_ESC, OUTPUT);
    
    // Configure output pins for indicator LEDs
    pinMode(LED_TRACK, OUTPUT);
    pinMode(LED_SPORT, OUTPUT);
    pinMode(LED_LDA, OUTPUT);
    pinMode(LED_ASS, OUTPUT);
    pinMode(LED_IMT, OUTPUT);
    pinMode(LED_ESC, OUTPUT); 

    // Ensure all pins are driven low
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

    // Configure input pins
    pinMode(INPUT_ESC, INPUT);
    pinMode(INPUT_MODE, INPUT);

    // Delay to allow car screens to load fully (large delay not necessary for function)
    delay(3000);

    // Read states of inputs
    bool STATE_ESC = digitalRead(INPUT_ESC);    // HIGH for expert (short), LOW for ESC fully off (long)
    bool STATE_MODE = digitalRead(INPUT_MODE);  // HIGH for track, LOW for sport

    // Turn buttons on sequentially
    // LDA
    digitalWrite(SWITCH_LDA, HIGH);
    digitalWrite(LED_LDA, HIGH);
    delay(4000);
    digitalWrite(SWITCH_LDA, LOW);
    digitalWrite(LED_LDA, LOW);
    delay(500);

    // iMT
    digitalWrite(SWITCH_IMT, HIGH);
    digitalWrite(LED_IMT, HIGH);
    delay(500);
    digitalWrite(SWITCH_IMT, LOW);
    digitalWrite(LED_IMT, LOW);
    delay(1000);

    // Auto Stop/Start
    digitalWrite(SWITCH_ASS, HIGH);
    digitalWrite(LED_ASS, HIGH);
    delay(500);
    digitalWrite(SWITCH_ASS, LOW);
    digitalWrite(LED_ASS, LOW);
    delay(1000);

    // Mode Select
    digitalWrite(SWITCH_MODE, HIGH);
    if(STATE_MODE){
        digitalWrite(LED_TRACK, HIGH);
    }else{
        digitalWrite(LED_SPORT, HIGH);
    }
    delay(500);
    digitalWrite(SWITCH_MODE, LOW);
    digitalWrite(LED_TRACK, LOW);
    digitalWrite(LED_SPORT, LOW);
    delay(1000);

    // ESC
    digitalWrite(SWITCH_ESC, HIGH);
    digitalWrite(LED_ESC, HIGH);
    delay(500);
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
}

void loop() {
    // Nothing to do in loop
}