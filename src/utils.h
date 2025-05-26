#pragma once
//  DEFINITIONS:

// -> lcd
#define lcd_RS 22
#define lcd_E 23
#define lcd_D4 24
#define lcd_D5 25
#define lcd_D6 26
#define lcd_D7 27

enum GameState {
    INTRO,
    WAIT_INTRO_DONE,
    QUESTION,
    WAIT_PLAYER_QUESTION,
    ANSWER,
    WAIT_ANSWER,
    AFTER_ANSWER,
    WAIT_FOR_RESTART
};

// -> buzzer
#define buzzerPin 9
#define MAX_PAUSE_DURATION 500
#define STEP_PAUSE_DURATION 3

// -> leds
#define ledGreen 30
#define ledRed 31
#define ledPlayer1 33
#define ledPlayer2 32
#define ledPlayer3 34
#define ledPlayer4 35

// -> buttons
#define button_A 40
#define button_B 41
#define button_C 42
#define buttonPlayer1 19
#define buttonPlayer2 18
#define buttonPlayer3 2
#define buttonPlayer4 3

// -> ROUND
#define DIM_ROUND 10
#define TIME_ROUND 30000 // ms

// ADDITIONAL VARIABLES:

// questions
char buffer[21];
int round_indices[DIM_ROUND];
int current_index;

// interruptions:

// -> buttons
volatile int player;
volatile bool stage_intro;
volatile bool stage_question;
volatile bool stage_restart;

// -> timer
volatile int intr_count;
volatile int pause_duration;
volatile int question_seconds;
volatile int still_time;
volatile int tictacoff; // 0 tic, 1 off, 2 tac
volatile bool tictacflag;

// buttons 
int stateA, stateB, stateC;

// players
int player_answer; // 1 - A, 2 - B, 3 - C
int player1Score;
int player2Score;
int player3Score;
int player4Score;