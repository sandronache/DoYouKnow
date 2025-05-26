#pragma once
#include <avr/pgmspace.h>

#define NUMBER_OF_QUESTIONS 30

const char intro[] PROGMEM = "Ready? <3";

const char player1Prompt[] PROGMEM = "1: ";
const char player2Prompt[] PROGMEM = "2: ";
const char player3Prompt[] PROGMEM = "3: ";
const char player4Prompt[] PROGMEM = "4: ";

struct QA {
  const char* question;
  const char* a;
  const char* b;
  const char* c;
  uint8_t correct; // 1 = A, 2 = B, 3 = C
};

const char q0[] PROGMEM = "Cel mai mare ocean?";
const char a0[] PROGMEM = "A - Atlantic";
const char b0[] PROGMEM = "B - Pacific";
const char c0[] PROGMEM = "C - Indian";

const char q1[] PROGMEM = "2,3,5,7,..?";
const char a1[] PROGMEM = "  A - 11";
const char b1[] PROGMEM = "  B - 9";
const char c1[] PROGMEM = "  C - 10";

const char q2[] PROGMEM = "Alfabetul are?";
const char a2[] PROGMEM = "A - 29 litere";
const char b2[] PROGMEM = "B - 30 litere";
const char c2[] PROGMEM = "C - 31 litere";

const char q3[] PROGMEM = "75-4*(456+9)*0+7*9?";
const char a3[] PROGMEM = "A - 138";
const char b3[] PROGMEM = "B - (-1722)";
const char c3[] PROGMEM = "C - 63";

const char q4[] PROGMEM = "1 octet = ?";
const char a4[] PROGMEM = "A - 1 biti";
const char b4[] PROGMEM = "B - 4 biti";
const char c4[] PROGMEM = "C - 8 biti";

const char q5[] PROGMEM = "Ce inseamna CPU?";
const char a5[] PROGMEM = "A - Memorie";
const char b5[] PROGMEM = "B - Procesor";
const char c5[] PROGMEM = "C - Stocare";

const char q6[] PROGMEM = "Ce inseamna WWW?";
const char a6[] PROGMEM = "A - Web";
const char b6[] PROGMEM = "B - World Wide Web";
const char c6[] PROGMEM = "C - Word Wide Web";

const char q7[] PROGMEM = "\"Romeo si Julieta\"?";
const char a7[] PROGMEM = "A - Shakespeare";
const char b7[] PROGMEM = "B - Tolstoi";
const char c7[] PROGMEM = "C - Dickens";

const char q8[] PROGMEM = "ROGV___?";
const char a8[] PROGMEM = "A - AVI";
const char b8[] PROGMEM = "B - AIV";
const char c8[] PROGMEM = "C - IVA";

const char q9[] PROGMEM = "Limba in Brazilia?";
const char a9[] PROGMEM = "A - Spaniola";
const char b9[] PROGMEM = "B - Portugheza";
const char c9[] PROGMEM = "C - Engleza";

const char q10[] PROGMEM = "Taj Mahal?";
const char a10[] PROGMEM = "A - India";
const char b10[] PROGMEM = "B - China";
const char c10[] PROGMEM = "C - Egipt";

const char q11[] PROGMEM = "Pisica are?";
const char a11[] PROGMEM = "A - 18 degete";
const char b11[] PROGMEM = "B - 16 degete";
const char c11[] PROGMEM = "C - 20 degete";

const char q12[] PROGMEM = "Care este conifer?";
const char a12[] PROGMEM = "A - Fag";
const char b12[] PROGMEM = "B - Molid";
const char c12[] PROGMEM = "C - Stejar";

const char q13[] PROGMEM = "Cizma...";
const char a13[] PROGMEM = "A - Italia";
const char b13[] PROGMEM = "B - Romania";
const char c13[] PROGMEM = "C - Chile";

const char q14[] PROGMEM = "Mov + Portocaliu?";
const char a14[] PROGMEM = "A - Maro";
const char b14[] PROGMEM = "B - Verde";
const char c14[] PROGMEM = "C - Gri";

const char q15[] PROGMEM = "Varful maxim..";
const char a15[] PROGMEM = "A - Omul";
const char b15[] PROGMEM = "B - Negoiu";
const char c15[] PROGMEM = "C - Moldoveanu";

const char q16[] PROGMEM = "Zeul soarelui?";
const char a16[] PROGMEM = "A - Ra";
const char b16[] PROGMEM = "B - Anubis";
const char c16[] PROGMEM = "C - Osiris";

const char q17[] PROGMEM = "Soare -> ..";
const char a17[] PROGMEM = "A - Venus";
const char b17[] PROGMEM = "B - Mercur";
const char c17[] PROGMEM = "C - Marte";

const char q18[] PROGMEM = "Mina creionului..";
const char a18[] PROGMEM = "A - Grafit";
const char b18[] PROGMEM = "B - Creta";
const char c18[] PROGMEM = "C - Carbune";

const char q19[] PROGMEM = "7 luni au fix:";
const char a19[] PROGMEM = "A - 30 de zile";
const char b19[] PROGMEM = "B - 31 de zile";
const char c19[] PROGMEM = "C - 29 de zile";

const char q20[] PROGMEM = "4 luni au fix:";
const char a20[] PROGMEM = "A - 30 de zile";
const char b20[] PROGMEM = "B - 31 de zile";
const char c20[] PROGMEM = "C - 29 de zile";

const char q21[] PROGMEM = "An bisect..";
const char a21[] PROGMEM = "A - 364";
const char b21[] PROGMEM = "B - 366";
const char c21[] PROGMEM = "C - 365";

const char q22[] PROGMEM = "Conductor:";
const char a22[] PROGMEM = "A - lemn";
const char b22[] PROGMEM = "B - metal";
const char c22[] PROGMEM = "C - bumbac";

const char q23[] PROGMEM = "Avem diftong?";
const char a23[] PROGMEM = "A - geam";
const char b23[] PROGMEM = "B - marsupiu";
const char c23[] PROGMEM = "C - trigon";

const char q24[] PROGMEM = "Turn inclinat:";
const char a24[] PROGMEM = "A - Turnul din Pisa";
const char b24[] PROGMEM = "B - Turnul Eiffel";
const char c24[] PROGMEM = "C - Turnul Big Ben";

const char q25[] PROGMEM = "Cea mai mare insula:";
const char a25[] PROGMEM = "A - Madagascar";
const char b25[] PROGMEM = "B - Noua Guinee";
const char c25[] PROGMEM = "C - Groenlanda";

const char q26[] PROGMEM = "Planeta Rosie:";
const char a26[] PROGMEM = "A - Marte";
const char b26[] PROGMEM = "B - Venus";
const char c26[] PROGMEM = "C - Saturn";

const char q27[] PROGMEM = "CMMDC 54 si 72:";
const char a27[] PROGMEM = "A - 6";
const char b27[] PROGMEM = "B - 18";
const char c27[] PROGMEM = "C - 9";

const char q28[] PROGMEM = "Animal nocturn...";
const char a28[] PROGMEM = "A - vultur";
const char b28[] PROGMEM = "B - liliac";
const char c28[] PROGMEM = "C - porumbel";

const char q29[] PROGMEM = "Kilometrii Ecuator!";
const char a29[] PROGMEM = "A - 20.075 km";
const char b29[] PROGMEM = "B - 10.075 km";
const char c29[] PROGMEM = "C - 40.075 km";

const QA questions[NUMBER_OF_QUESTIONS] PROGMEM = {
  {q0, a0, b0, c0, 2},
  {q1, a1, b1, c1, 1},
  {q2, a2, b2, c2, 3},
  {q3, a3, b3, c3, 1},
  {q4, a4, b4, c4, 3},
  {q5, a5, b5, c5, 2},
  {q6, a6, b6, c6, 2},
  {q7, a7, b7, c7, 1},
  {q8, a8, b8, c8, 2},
  {q9, a9, b9, c9, 2},
  {q10, a10, b10, c10, 1},
  {q11, a11, b11, c11, 1},
  {q12, a12, b12, c12, 2},
  {q13, a13, b13, c13, 1},
  {q14, a14, b14, c14, 1},
  {q15, a15, b15, c15, 3},
  {q16, a16, b16, c16, 1},
  {q17, a17, b17, c17, 2},
  {q18, a18, b18, c18, 1},
  {q19, a19, b19, c19, 2},
  {q20, a20, b20, c20, 1},
  {q21, a21, b21, c21, 2},
  {q22, a22, b22, c22, 2},
  {q23, a23, b23, c23, 2},
  {q24, a24, b24, c24, 1},
  {q25, a25, b25, c25, 3},
  {q26, a26, b26, c26, 1},
  {q27, a27, b27, c27, 2},
  {q28, a28, b28, c28, 2},
  {q29, a29, b29, c29, 3}
};
