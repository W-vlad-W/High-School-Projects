#include "mastermind.h"
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

Bounce btn1;
Bounce btn2;
Bounce btn3;
Bounce btn4;
Bounce btnEnter;

void setup() {
    btn1.attach(BTN_1_PIN, INPUT_PULLUP);
    btn2.attach(BTN_2_PIN, INPUT_PULLUP);
    btn3.attach(BTN_3_PIN, INPUT_PULLUP);
    btn4.attach(BTN_4_PIN, INPUT_PULLUP);
    btnEnter.attach(BTN_ENTER_PIN, INPUT_PULLUP);
    
    btn1.interval(25);
    btn2.interval(25);
    btn3.interval(25);
    btn4.interval(25);
    btnEnter.interval(25);

    pinMode(LED_BLUE_1, OUTPUT);
    pinMode(LED_BLUE_2, OUTPUT);
    pinMode(LED_BLUE_3, OUTPUT);
    pinMode(LED_BLUE_4, OUTPUT);
    pinMode(LED_RED_1, OUTPUT);
    pinMode(LED_RED_2, OUTPUT);
    pinMode(LED_RED_3, OUTPUT);
    pinMode(LED_RED_4, OUTPUT);

    char* secret = generate_code(false, 4);  
    if (secret) {
        turn_off_leds();
        play_game(secret);
        free(secret);
    }
}

void loop() {

}