#include "mastermind.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX_ATTEMPTS 10
#define LED_COUNT 4
#define CODE_LENGTH 4

LiquidCrystal_I2C lcd(0x27, 16, 2); 


void animate_leds(int duration_ms = 3000, int blink_delay_ms = 500) {
    const int led_red[4] = {LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4};
    const int led_blue[4] = {LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4};
    const int total_cycles = duration_ms / (blink_delay_ms * 2); 

    for (int cycle = 0; cycle < total_cycles; cycle++) {

        turn_off_leds();
        for (int i = 0; i <= 4; i += 2) {
            digitalWrite(led_red[i], HIGH);
        }
        for (int i = 1; i <= 4; i += 2) {
            digitalWrite(led_blue[i], HIGH);
        }
        delay(blink_delay_ms);


        turn_off_leds();
        for (int i = 1; i <= 4; i += 2) {
            digitalWrite(led_red[i], HIGH);
        }
        for (int i = 0; i <= 4; i += 2) {
            digitalWrite(led_blue[i], HIGH);
        }
        delay(blink_delay_ms);
    }

    turn_off_leds(); 
    
}

void show_welcome_message() {
    lcd.clear();
    lcd.print("Welcome to");
    lcd.setCursor(0, 1);
    lcd.print("Mastermind!");
    delay(3000);
}

void show_victory_message() {
    lcd.clear();
    lcd.print("You won!");
    delay(3000);
}

void show_game_over_message(char* secret) {
    lcd.clear();
    lcd.print("Game over!");
    lcd.setCursor(0, 1);
    lcd.print("Code: ");
    lcd.print(secret);
    delay(3000);
}

void history_view(char* secret, char** history, const int entry) {
    if (!secret || !history || entry < 0) return;

    int i = entry; 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("His: ");
    lcd.print("Enter-Exit");
    lcd.setCursor(0, 1);
    lcd.print("<-BTN_3 ");
    lcd.print(" BTN_4->");
    render_history(secret, history, i);
    while (true) {
        render_history(secret, history, i); 

        while (true) {
            btn3.update();
            btn4.update();
            btnEnter.update();
            
            if (btn3.fell() && i > 0) { 
                i--;
                break;
            }
            if (btn4.fell() && i < entry) {  
                i++;
                break;
            }
            if (btnEnter.fell()) {  
                return;
            }
        }
    }
}



char* get_user_input(char* secret, char** history, const int entry) {
    static char input[5] = {'0', '0', '0', '0', '\0'};
    bool confirmed = false;

    strcpy(input, "0000");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input:");
    lcd.setCursor(0, 1);
    lcd.print(input);
    
    while (btnEnter.read() == LOW) {
        btnEnter.update();
    }
    
    while (!confirmed) {
        btn1.update();
        btn2.update();
        btn3.update();
        btn4.update();
        btnEnter.update();

        if (btnEnter.read() == LOW) {
            if(btn1.read() == HIGH){
                history_view(secret, history, entry);
                turn_off_leds();
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Input:");
                lcd.setCursor(0, 1);
                lcd.print(input);
                
                while (btn1.read() == HIGH || btnEnter.read() == LOW) {
                    btn1.update();
                    btnEnter.update();
                }
            }
        }

        if (btn1.fell()) {
            input[0] = ((input[0] - '0' + 1) % 10) + '0';
            lcd.setCursor(0, 1);
            lcd.print(input);
        }
        if (btn2.fell()) {
            input[1] = ((input[1] - '0' + 1) % 10) + '0';
            lcd.setCursor(0, 1);
            lcd.print(input);
        }
        if (btn3.fell()) {
            input[2] = ((input[2] - '0' + 1) % 10) + '0';
            lcd.setCursor(0, 1);
            lcd.print(input);
        }
        if (btn4.fell()) {
            input[3] = ((input[3] - '0' + 1) % 10) + '0';
            lcd.setCursor(0, 1);
            lcd.print(input);
        }
        if (btnEnter.fell()) {
            confirmed = true;
        }
    }

    return input;
}


char* generate_code(bool repeat, int length) {
    if (length < 1 || (!repeat && length > 10)) return NULL;

    char* code = (char*) malloc(length + 1);
    if (!code) return NULL;

    char used[10] = {0};  
    srand(analogRead(A3));

    for (int i = 0; i < length; ++i) {
        int digit;
        do {
            digit = rand() % 10; 
        } while (!repeat && used[digit]);

        code[i] = '0' + digit;
        if (!repeat) {
            used[digit] = 1;
        }
    }

    code[length] = '\0';
    return code;
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b) {
    if (!secret || !guess || !peg_a || !peg_b) return;

    int len_secret = strlen(secret);
    int len_guess = strlen(guess);
    int len = (len_secret < len_guess) ? len_secret : len_guess;

    int used_secret[4] = {0};
    int used_guess[4] = {0};

    *peg_a = 0;
    *peg_b = 0;

    for (int i = 0; i < len; ++i) {
        if (secret[i] == guess[i]) {
            (*peg_a)++;
            used_secret[i] = 1;
            used_guess[i] = 1;
        }
    }

    for (int i = 0; i < len; ++i) {
        if (used_guess[i]) continue;
        for (int j = 0; j < len; ++j) {
            if (!used_secret[j] && guess[i] == secret[j]) {
                (*peg_b)++;
                used_secret[j] = 1;
                break;
            }
        }
    }
}


void turn_off_leds() {
    int ledA[4] = {LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4};
    int ledB[4] = {LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4};
    for (int i = 0; i < 4; ++i) {
        digitalWrite(ledA[i], LOW);
        digitalWrite(ledB[i], LOW);
    }
}

void render_leds(int peg_a, int peg_b) {
    turn_off_leds();  

    int led_red[4] = {LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4};
    int led_blue[4] = {LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4};

    int total_leds = peg_a + peg_b;
    if (total_leds > 4) {
        peg_b = 4 - peg_a;  
    }

    for (int i = 0; i < peg_a && i < 4; ++i) {
        digitalWrite(led_red[i], HIGH);
    }

    for (int i = 0; i < peg_b && i < 4; ++i) {
        digitalWrite(led_blue[i], HIGH);
    }
}


void render_history(char* secret, char** history, const int entry) {
    if (!secret || !history || entry < 0) return;
    
    if (!history[entry]) return;

    int peg_a = 0, peg_b = 0;
    get_score(secret, history[entry], &peg_a, &peg_b);
    render_leds(peg_a, peg_b);
    lcd.clear();
    
    lcd.print(history[entry]);
    
    const int buf_size = 32;  
    char buf[buf_size];
    snprintf(buf, buf_size, "C: %d, W pos: %d", peg_a, peg_b);
    
    lcd.setCursor(0, 1); 
    lcd.print(buf);
}

void play_game(char* secret) {
    lcd.init();      
    lcd.backlight();

    if (!secret) {
        lcd.print("Invalid secret!");
        return;
    }
    
    show_welcome_message();  
    animate_leds();
    char* history[MAX_ATTEMPTS] = {0};
    int attempts = 0;
    bool game_won = false;
    while (attempts < MAX_ATTEMPTS && !game_won) {
        turn_off_leds();
        lcd.clear();
        lcd.print("Attempt ");
        lcd.print(String(attempts + 1).c_str());
        lcd.print("/");
        lcd.print(String(MAX_ATTEMPTS).c_str());

        delay(1000); 
        char* guess = get_user_input(secret, history, attempts);

        int peg_a = 0, peg_b = 0;
        get_score(secret, guess, &peg_a, &peg_b);
        render_leds(peg_a, peg_b);

        history[attempts] = strdup(guess);
        if (!history[attempts]) {
            lcd.print("Memory error!");
            delay(2000);
            break;
        }

        if (peg_a == CODE_LENGTH) {
            game_won = true;
            show_victory_message();
            break;
        }

        render_history(secret, history, attempts);
        delay(3000); 

        attempts++;
    }

    if (!game_won) {
        show_game_over_message(secret);
    }

    for (int i = 0; i < MAX_ATTEMPTS; ++i) {
        if (history[i]) {
            free(history[i]);
        }
    }
    free(secret);  
}


