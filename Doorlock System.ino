#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SERVO_PIN D10

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {D6, D7, D8, D9};
byte colPins[COLS] = {D3, D4, D5, D0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";
String input_password;

void setup() {
  servo.attach(SERVO_PIN);
  servo.write(0);  // Locked position

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input_password == password) {
        lcd.clear();
        lcd.print("Access Granted");
        servo.write(90);  // Unlock servo position
        delay(3000);
        servo.write(0);   // Lock again
        lcd.clear();
        lcd.print("Enter Password:");
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        delay(2000);
        lcd.clear();
        lcd.print("Enter Password:");
      }
      input_password = "";
    } else if (key == '*') {
      input_password = "";
      lcd.clear();
      lcd.print("Input Cleared");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Password:");
    } else {
      input_password += key;
      lcd.setCursor(input_password.length()-1, 1);
      lcd.print("*");
    }
  }
}
