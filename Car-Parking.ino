#include <LiquidCrystal.h> // Include the LiquidCrystal library
#include <Servo.h>         // Include the Servo library

// Initialize the LCD with the corresponding interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

Servo myservo1; // Create a Servo object

int ir_s1 = 2; // IR sensor 1 (entry)
int ir_s2 = 4; // IR sensor 2 (exit)

int Total = 5; // Total parking spaces
int Space;     // Available parking spaces

int flag1 = 0;
int flag2 = 0;

void setup() {
    pinMode(ir_s1, INPUT);
    pinMode(ir_s2, INPUT);

    myservo1.attach(3);
    myservo1.write(100); // Initial servo position

    lcd.begin(16, 2); // Initialize the LCD (16x2)
    lcd.setCursor(0, 0);
    lcd.print(" Car Parking ");
    lcd.setCursor(0, 1);
    lcd.print(" System ");
    delay(2000);
    lcd.clear();

    Space = Total; // Initialize available spaces
}

void loop() {
    if (digitalRead(ir_s1) == LOW && flag1 == 0) {
        if (Space > 0) {
            flag1 = 1;
            if (flag2 == 0) {
                myservo1.write(0);
                Space = Space - 1;
            }
        } else {
            lcd.setCursor(0, 0);
            lcd.print(" Sorry No Space ");
            lcd.setCursor(0, 1);
            lcd.print(" Available ");
            delay(1000);
            lcd.clear();
        }
    }

    if (digitalRead(ir_s2) == LOW && flag2 == 0) {
        flag2 = 1;
        if (flag1 == 0) {
            myservo1.write(0);
            Space = Space + 1;
        }
    }

    if (flag1 == 1 && flag2 == 1) {
        delay(1000);
        myservo1.write(100);
        flag1 = 0;
        flag2 = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("Total Space: ");
    lcd.print(Total);

    lcd.setCursor(0, 1);
    lcd.print("Available: ");
    lcd.print(Space);
}
