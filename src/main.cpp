#include <Arduino.h>
#include <LiquidCrystal.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "utils.h"
#include "lcd_text.h"
#include "functions.h"

void setup() {
  // lcd
  lcd.begin(20, 4);
  // buzzer
  DDRH |= (1 << PH6); // buzzerPin
  // leds
  DDRC |= (1 << PC7); // ledGreen
  DDRC |= (1 << PC6); // ledRed
  DDRC |= (1 << PC4); // ledPlayer1
  DDRC |= (1 << PC5); // ledPlayer2
  DDRC |= (1 << PC3); // ledPlayer3
  DDRC |= (1 << PC2); // ledPlayer4
  // buttons
  // input
  DDRG &= ~(1 << PG1); // button_A
  // activate pull-up
  PORTG |= (1 << PG1);

  DDRG &= ~(1 << PG0); // button_B
  PORTG |= (1 << PG0);

  DDRL &= ~(1 << PL7); // button_C
  PORTL |= (1 << PL7);

  DDRD &= ~(1 << PD2); // buttonPlayer1
  PORTD |= (1 << PD2);

  DDRD &= ~(1 << PD3); // buttonPlayer2
  PORTD |= (1 << PD3);

  DDRE &= ~(1 << PE4); // buttonPlayer3
  PORTE |= (1 << PE4);

  DDRE &= ~(1 << PE5); // buttonPlayer4
  PORTE |= (1 << PE5);

  // adc
  adc_init();

  activateInterruptions();
  startGame();
  // timer
  initTimer1();
}

void loop() {
  switch (state) {
    case INTRO:
      // show intro
      printStringFromProgmem(intro, 2, 5);
      stage_intro = true;
      state = WAIT_INTRO_DONE;
      break;

    case WAIT_INTRO_DONE:
      // wait for confirmation
      if (!stage_intro) {
        state = QUESTION;
        _delay_ms(500);
      }
      break;

    case QUESTION:
      // print question
      printQuestion(round_indices[current_index]);
      // tell timer a question stars
      initializeTimerPrimitives();
      still_time = true;
      stage_question = true;
      state = WAIT_PLAYER_QUESTION;
      break;

    case WAIT_PLAYER_QUESTION:
      // wait for an answer
      if (!stage_question) {
        // stop buzzer
        noTone(buzzerPin);
        // show the lucky player
        _delay_ms(1000);
        putPlayerLedOnLow();
        state = ANSWER;
      } else if (!still_time) {
        // if no more time
        // stop buzzer
        noTone(buzzerPin);
        // sad sound =(
        _delay_ms(1500);
        tone(buzzerPin, 400);
        _delay_ms(1500);
        noTone(buzzerPin);
        state = AFTER_ANSWER;
      } else playTicTac();
      break;

    case ANSWER:
      // animation
      blinkGreenAndRed();
      state = WAIT_ANSWER;
      break;
      
    case WAIT_ANSWER:
      // wait for answer
      stateA = (PING & (1 << PG1)) ? 1 : 0;
      stateB = (PING & (1 << PG0)) ? 1 : 0;
      stateC = (PINL & (1 << PL7)) ? 1 : 0;
      if (stateA == LOW || stateB == LOW || stateC == LOW) {
        if (stateA == LOW) player_answer = 1;
        else if (stateB == LOW) player_answer = 2;
        else if (stateC == LOW) player_answer = 3;
        checkPlayerAnswer();
        state = AFTER_ANSWER;
      }
      break;

    case AFTER_ANSWER:

      current_index++;
      if (current_index == DIM_ROUND) {
        printScore();
        stage_restart = true;
        state = WAIT_FOR_RESTART;
      } else state = QUESTION;
    
      break;
    
    case WAIT_FOR_RESTART:

      if (!stage_restart) {
        startGame();
        state = INTRO;
      }

      break;
  }
}