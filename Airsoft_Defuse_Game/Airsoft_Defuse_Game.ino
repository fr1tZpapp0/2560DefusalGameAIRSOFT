// ARDUINO MEGA 2560 BASED AIRSOFT DEFUSAL GAME
// MADE BY fr1tZ

// INCLUDED LIBRARIES
#include <Keypad.h>
#include <LiquidCrystal.h>

// ===== LCD SETUP =====
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // SET THE LCD PINS TO THE ARDUINO IO PINS
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // SET THE LCD TO THE DECLARED PINS

// ===== KEYPAD SETUP =====
const byte ROWS = 4; // 4 ROWS
const byte COLS = 4; // 4 COLUMNS
char keys[ROWS][COLS] = { // SETUP THE ROWS & COLUMNS AND LABEL EACH BUTTON IN THE KEYPAD
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; // WHICH PIN GOES TO WHAT IN THE ROWS
byte colPins[COLS] = {A0, A1, A2, A3}; // WHICH PIN GOES TO WHAT IN THE COLUMNS

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // SET THE KEYPAD TO THE ROWS, COLUMNS, AND MAKE A KEYMAP

// ===== INT DECLARATIONS =====
int redTeamBtn = A4; // ENABLE ARMED MODE BUTTON
int blueTeamBtn = A5; // ENABLE DISARM MODE BUTTON
int rLED = A6; // RED PIN (RGB LED)
int gLED = A7; // GREEN PIN (RGB LED)
int bLED = A8; // BLUE PIN (RGB LED)
int buzzer = 10; // BEEPER / BUZZER FOR COUNT-DOWN

// ===== TIME DECLARATIONS =====
int second = 1000; // ONE SECOND
int multiplex = 100; // TENTH OF A SECOND

int twentyMin = 1200000; // 1,200,000 MILLISECONDS
int fifteenMin = 900000; // 900,000 MILLISECONDS
int tenMin = 600000; // 600,000 MILLISECONDS
int fiveMin = 300000; // 300,000 MILLISECONDS
int oneMin = 60000; // 60,000 MILLISECONDS


// ===== COUNTDOWN DISPLAY =====
int a = 22; // SEGMENT A
int b = 23; // SEGMENT B
int c = 24; // SEGMENT C
int d = 25; // SEGMENT D
int e = 26; // SEGMENT E
int f = 27; // SEGMENT F
int g = 28; // SEGMENT G

int digit1 = 29; // FIRST DIGIT (4 DIGIT DISPLAY)
int digit2 = 30; // SECOND DIGIT (4 DIGIT DISPLAY)
int digit3 = 31; // THIRD DIGIT (4 DIGIT DISPLAY)
int digit4 = 32; // FOURTH DIGIT (4 DIGIT DISPLAY)

// ===== FUNCTIONS =====
void zero() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void three() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void six() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void firstDigit() {
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}

void secondDigit() {
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}

void thirdDigit() {
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, LOW);
}

void fourthDigit() {
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, HIGH);
}

void beep() {
  digitalWrite(buzzer, HIGH);
  delay(second);
  digitalWrite(buzzer, LOW);
  delay(second);
}

void begin10MinCountdown() { // INITIAL 10 MINUTE COUNTDOWN (DISPLAYS 10:00 FIRST!)
  firstDigit();
  zero();
  beep();
  delay(multiplex);
  secondDigit();
  zero();
  beep();
  delay(multiplex);
  thirdDigit();
  zero();
  beep();
  delay(multiplex);
  fourthDigit();
  one();
  beep();
  delay(multiplex);
}

void boom() {
  firstDigit();
  zero();
  beep();
  delay(multiplex);
  secondDigit();
  zero();
  beep();
  delay(multiplex);
  thirdDigit();
  zero();
  beep();
  delay(multiplex);
  fourthDigit();
  zero();
  beep();
  delay(multiplex);
}

// ===== LOOPS =====
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("ENGAGE DEVICE...");
  Serial.begin(9600);

  pinMode(redTeamBtn, INPUT_PULLUP); // INPUT PULLUPS = READ A GROUND SIGNAL / LOW SIGNAL
  pinMode(blueTeamBtn, INPUT_PULLUP); // EACH BUTTON IS SET TO READ A GROUND SIGNAL / LOW SIGNAL

  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
}

void loop() {
  char key = keypad.getKey(); // THE CHARACTER 'KEY' IS THE KEYPAD'S KEY CORRESPONDING TO THE PRESSED KEYPAD BUTTON
  
}
