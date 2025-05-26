#include <Arduino.h>
#include <LiquidCrystal.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "utils.h"
#include "lcd_text.h"

// GLOBAL INITIALIZATIONS:

// lcd
LiquidCrystal lcd(lcd_RS, lcd_E, lcd_D4, lcd_D5, lcd_D6, lcd_D7);

// state
GameState state = INTRO;

// FUNCTIONS:

void addPointToPlayer() {
  if (player == 1) {
    player1Score += 1;
  } else if (player == 2) {
    player2Score += 1;
  } else if (player == 3) {
    player3Score += 1;
  } else if (player == 4) {
    player4Score += 1;
  }
}

void playTicTac() {
  if (tictacflag) {
    if (tictacoff == 0) tone(buzzerPin, 1000);
    else if (tictacoff == 1) noTone(buzzerPin);
    else if (tictacoff == 2) tone(buzzerPin, 1500);
    tictacflag = false;
  }
}

void checkPlayerAnswer() {
  QA temp;
  memcpy_P(&temp, &questions[round_indices[current_index]], sizeof(QA));

  if (player_answer == temp.correct) {
    // give him a point
    addPointToPlayer();
    // animation
    PORTC |= (1 << PC7); // ledGreen HIGH
    tone(buzzerPin, 1200);
    _delay_ms(1000);
    noTone(buzzerPin);
    PORTC &= ~(1 << PC7); // ledGreen LOW
  } else {
    // animation
    PORTC |= (1 << PC6); // ledRed HIGH
    tone(buzzerPin, 400);
    _delay_ms(1000);
    noTone(buzzerPin);
    PORTC &= ~(1 << PC6); // ledRed LOW
  }
}

void blinkGreenAndRed() {
  PORTC |= (1 << PC7); // ledGreen HIGH
  PORTC |= (1 << PC6); // ledRed HIGH
  _delay_ms(500);
  PORTC &= ~(1 << PC7); // ledGreen LOW
  PORTC &= ~(1 << PC6); // ledRed LOW
  _delay_ms(500);
  PORTC |= (1 << PC7); // ledGreen HIGH
  PORTC |= (1 << PC6); // ledRed HIGH
  _delay_ms(500);
  PORTC &= ~(1 << PC7); // ledGreen LOW
  PORTC &= ~(1 << PC6); // ledRed LOW
}

void putPlayerLedOnLow() {
  if (player == 1) {
    PORTC &= ~(1 << PC4); // ledPlayer1 LOW
  } else if (player == 2) {
    PORTC &= ~(1 << PC5); // ledPlayer2 LOW
  } else if (player == 3) {
    PORTC &= ~(1 << PC3); // ledPlayer3 LOW
  } else if (player == 4) {
    PORTC &= ~(1 << PC2); // ledPlayer4 LOW
  }
}

void adc_init() {
  // 5V
  ADMUX = 0;
  ADMUX = (1 << REFS0);

  // activate + prescaler 128 (16 MHz / 128 = 125 kHz)
  ADCSRA = 0;
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t analogReadBareMetal(uint8_t channel) {
  // keep REFS.. and select analogic pin
  ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

  // start conversion
  ADCSRA |= (1 << ADSC);

  // wait
  while (ADCSRA & (1 << ADSC));

  // return
  return ADC;
}

// function that chooses DIM_ROUND random questions
void generate_indices() {
  // choose seed depending on noise
  randomSeed(analogReadBareMetal(0));

  int i = 0;
  while (i < DIM_ROUND) {
    int r = random(0, NUMBER_OF_QUESTIONS);
    bool exists = false;
    for (int j = 0; j < i; j++) {
      if (round_indices[j] == r) {
        exists = true;
        break;
      }
    }
    if (!exists) {
      round_indices[i] = r;
      i++;
    }
  }

  current_index = 0;
}

void startGame() {
  // generate questions
  generate_indices();
  // variables
  stage_intro = false;
  stage_question = false;
  stage_restart = false;
  // set scores
  player1Score = 0;
  player2Score = 0;
  player3Score = 0;
  player4Score = 0;
}

void printScore() {
  lcd.clear();

  // player 1
  strcpy_P(buffer, player1Prompt);
  lcd.setCursor(0, 0);
  lcd.print(buffer);
  lcd.print(player1Score);

  // player 2
  strcpy_P(buffer, player2Prompt);
  lcd.setCursor(0, 1);
  lcd.print(buffer);
  lcd.print(player2Score);

  // player 3
  strcpy_P(buffer, player3Prompt);
  lcd.setCursor(0, 2);
  lcd.print(buffer);
  lcd.print(player3Score);

  // player 4
  strcpy_P(buffer, player4Prompt);
  lcd.setCursor(0, 3);
  lcd.print(buffer);
  lcd.print(player4Score);
}

void printStringFromProgmem (const char str[], int row, int column) {
  strcpy_P(buffer, str);
  lcd.clear();
  lcd.setCursor(column, row);
  lcd.print(buffer);
}

void printQuestion(int index) {
  QA temp;
  memcpy_P(&temp, &questions[index], sizeof(QA));

  strcpy_P(buffer, temp.question);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buffer);

  strcpy_P(buffer, temp.a);

  lcd.setCursor(0, 1);
  lcd.print(buffer);

  strcpy_P(buffer, temp.b);

  lcd.setCursor(0, 2);
  lcd.print(buffer);

  strcpy_P(buffer, temp.c);
  
  lcd.setCursor(0, 3);
  lcd.print(buffer);
}

void activateInterruptions() {
  cli();

  EIMSK |= (1 << INT2) | (1 << INT3) | (1 << INT4) | (1 << INT5);

  // falling edge for all
  // INT2
  EICRA |= (1 << ISC21);
  EICRA &= ~(1 << ISC20);

  // INT3
  EICRA |= (1 << ISC31);
  EICRA &= ~(1 << ISC30);

  // INT4
  EICRB |= (1 << ISC41);
  EICRB &= ~(1 << ISC40);

  // INT5
  EICRB |= (1 << ISC51);
  EICRB &= ~(1 << ISC50);

  sei();
}

void initializeTimerPrimitives() {
  intr_count = 0;
  pause_duration = MAX_PAUSE_DURATION;
  question_seconds = 0;

  tictacoff = 1;
  tictacflag = false;
}

void initTimer1() {
  cli();

  TCCR1A = 0;
  TCCR1B = 0;

  // 16MHz / 64 = 250kHz
  OCR1A = 250;

  // CTC mode
  TCCR1B |= (1 << WGM12);
  // 64 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // activate
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

// INTERRUPTS:

ISR(INT2_vect) {
  if (stage_restart) stage_restart = false;
  else if (stage_intro) stage_intro = false;
  else if (stage_question) {
    stage_question = false;
    player = 1;
    PORTC |= (1 << PC4); // ledPlayer1 HIGH
  }
}

ISR(INT3_vect) {
  if (stage_restart) stage_restart = false;
  else if (stage_intro) stage_intro = false;
  else if (stage_question) {
    stage_question = false;
    player = 2;
    PORTC |= (1 << PC5); // ledPlayer2 HIGH
  }
}

ISR(INT4_vect) {
  if (stage_restart) stage_restart = false;
  else if (stage_intro) stage_intro = false;
  else if (stage_question) {
    stage_question = false;
    player = 3;
    PORTC |= (1 << PC3); // ledPlayer3 HIGH
  }
}

ISR(INT5_vect) {
  if (stage_restart) stage_restart = false;
  else if (stage_intro) stage_intro = false;
  else if (stage_question) {
    stage_question = false;
    player = 4;
    PORTC |= (1 << PC2); // ledPlayer4 HIGH
  }
}

// TIMER:
ISR(TIMER1_COMPA_vect) {
  intr_count++;

  if (intr_count == pause_duration) {
    tictacoff = (tictacoff + 1) % 3;
    tictacflag = true;

    intr_count = 0;
    pause_duration -= STEP_PAUSE_DURATION;
  }

  question_seconds++;
  if (question_seconds == TIME_ROUND) {
    still_time = false;

    intr_count = 0;
    question_seconds = 0;
    pause_duration = 500;
  }
}

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
        _delay_ms(2000);
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