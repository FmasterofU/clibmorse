#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NULL_TERMINATOR '\0'
#define MORSE_SIGNAL_ON '1'
#define MORSE_SIGNAL_OFF '0'
#define MORSE_DOT '.'
#define MORSE_DASH '-'
#define ASCII_ZERO 48 // '0'
#define ASCII_A 65  // 'A'
#define ASCII_SPACE 32 // ' '
#define ASCII_FSTOP_PERIOD '.'
#define ASCII_COLON ':'
#define ASCII_APOSTROPHE '\''
#define ASCII_COMMA ','
#define ASCII_EXCLAMATION_MARK '!'
#define ASCII_QUESTION_MARK '?'
#define ASCII_QUOTATION_MARKS '\"'
#define ASCII_SLASH '/'
#define ASCII_HYPHEN '-'
#define ASCII_PLUS_SIGN '+'
#define ASCII_EQUALS_SIGN '='
#define ASCII_BRACKET_OPEN '('
#define ASCII_BRACKET_CLOSED ')'
#define ASCII_AT_SIGN '@'
#define ASCII_AMPERSAND '&'

static const char numbers[10][6] = {
    {"-----\0"}, //0
    {".----\0"}, //1
    {"..---\0"}, //2
    {"...--\0"}, //3
    {"....-\0"}, //4
    {".....\0"}, //5
    {"-....\0"}, //6
    {"--...\0"}, //7
    {"---..\0"}, //8
    {"----.\0"}  //9
};

static const char letters[26][5] = {
    {".-\0"},    //A
    {"-...\0"},  //B
    {"-.-.\0"},  //C
    {"-..\0"},   //D
    {".\0"},     //E
    {"..-.\0"},  //F
    {"--.\0"},   //G
    {"....\0"},  //H
    {"..\0"},    //I
    {".---\0"},  //J
    {"-.-\0"},   //K
    {".-..\0"},  //L
    {"--\0"},    //M
    {"-.\0"},    //N
    {"---\0"},   //O
    {".--.\0"},  //P
    {"--.-\0"},  //Q
    {".-.\0"},   //R
    {"...\0"},   //S
    {"-\0"},     //T
    {"..-\0"},   //U
    {"...-\0"},  //V
    {".--\0"},   //W
    {"-..-\0"},  //X
    {"-.--\0"},  //Y
    {"--..\0"}   //Z
};

static const char fullStopPeriod[7] = ".-.-.-\0";
static const char colon[7] = "---...\0";
static const char apostrophe[7] = ".----.\0";
static const char comma[7] = "--..--\0";
static const char exclamationMark[7] = "-.-.--\0";
static const char questionMark[7] = "..--..\0";
static const char quotationMarks[7] = ".-..-.\0";
static const char slash[6] = "-..-.\0";
static const char hyphen[7] = "-....-\0";
static const char plusSign[6] = ".-.-.\0";
static const char equalsSign[6] = "-...-\0";
static const char bracketOpen[6] = "-.--.\0";
static const char bracketClosed[7] = "-.--.-\0";
static const char atSign[7] = ".--.-.\0";
static const char ampersand[6] = ".-...\0";

static unsigned char dotUnitLen = 1;
static unsigned char dashUnitLen = 3;
static unsigned char letterSpaceUnitLen = 3;
static unsigned char letterPartSpaceUnitLen = 1;
static unsigned char wordSpaceUnitLen = 7;

void encodeCharacter(char * ret, const char * morseKey, int * retiter){
    for(; *morseKey != NULL_TERMINATOR; morseKey++){
        if(*morseKey==MORSE_DOT)
            for(int j = 0; j<dotUnitLen; j++)
                ret[(*retiter)++]=MORSE_SIGNAL_ON;
        else if(*morseKey==MORSE_DASH)
            for(int j = 0; j<dashUnitLen; j++)
                ret[(*retiter)++]=MORSE_SIGNAL_ON;
        for(int k = 0; k<letterPartSpaceUnitLen && *(morseKey+1) != NULL_TERMINATOR; k++)
            ret[(*retiter)++]=MORSE_SIGNAL_OFF;
    }
}

char* encode(char* text){
    char *ret = (char*) malloc(4096);
    int i, retiter = 0;
    for(i = 0; i<strlen(text); i++){
        char tempChar = (char) toupper(text[i]);
        switch(tempChar){
        case ASCII_SPACE:
            for(int k = 0; k<wordSpaceUnitLen; k++)
                ret[retiter++]=MORSE_SIGNAL_OFF;
            break;
        case ASCII_FSTOP_PERIOD:
            encodeCharacter(ret, fullStopPeriod, &retiter);
            break;
        case ASCII_COLON:
            encodeCharacter(ret, colon, &retiter);
            break;
        case ASCII_APOSTROPHE:
            encodeCharacter(ret, apostrophe, &retiter);
            break;
        case ASCII_COMMA:
            encodeCharacter(ret, comma, &retiter);
            break;
        case ASCII_EXCLAMATION_MARK:
            encodeCharacter(ret, exclamationMark, &retiter);
            break;
        case ASCII_QUESTION_MARK:
            encodeCharacter(ret, questionMark, &retiter);
            break;
        case ASCII_QUOTATION_MARKS:
            encodeCharacter(ret, quotationMarks, &retiter);
            break;
        case ASCII_SLASH:
            encodeCharacter(ret, slash, &retiter);
            break;
        case ASCII_HYPHEN:
            encodeCharacter(ret, hyphen, &retiter);
            break;
        case ASCII_PLUS_SIGN:
            encodeCharacter(ret, plusSign, &retiter);
            break;
        case ASCII_EQUALS_SIGN:
            encodeCharacter(ret, equalsSign, &retiter);
            break;
        case ASCII_BRACKET_OPEN:
            encodeCharacter(ret, bracketOpen, &retiter);
            break;
        case ASCII_BRACKET_CLOSED:
            encodeCharacter(ret, bracketClosed, &retiter);
            break;
        case ASCII_AT_SIGN:
            encodeCharacter(ret, atSign, &retiter);
            break;
        case ASCII_AMPERSAND:
            encodeCharacter(ret, ampersand, &retiter);
            break;
        default:
            ;const char * tempMorseNotation = (tempChar-ASCII_ZERO<=9) ? numbers[tempChar-ASCII_ZERO] : letters[tempChar-ASCII_A];  // about that ";", requirement per standard, after a label (default) only an statement can follow, and declaration is not a statement
            encodeCharacter(ret, tempMorseNotation, &retiter);
        }
        for(int k = 0; k<letterSpaceUnitLen && *(text+i) != ASCII_SPACE && *(text+i+1) != ASCII_SPACE && *(text+i+1) != '\0'; k++)
            ret[retiter++]=MORSE_SIGNAL_OFF;
    }
    return ret;
}

void sendFrame(int consecutiveSignals, char signalType, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    if(consecutiveSignals!=0){
        if(signalType == MORSE_SIGNAL_ON) (*signal_func)(unitTime*consecutiveSignals);
        else (*sleep_func)(unitTime*consecutiveSignals);
    }
}

void send(char * dataStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    int consecutiveSignals = 0;
    char signalType = MORSE_SIGNAL_OFF;
    for(long i = 0; i<strlen(dataStream); i++){
        if(dataStream[i]==signalType)
            consecutiveSignals++;
        else if(dataStream[i]!=signalType){
            sendFrame(consecutiveSignals, signalType, unitTime, signal_func, sleep_func);
            consecutiveSignals=1;
            signalType = signalType==MORSE_SIGNAL_OFF?MORSE_SIGNAL_ON:MORSE_SIGNAL_OFF;
        }
    }
    sendFrame(consecutiveSignals, signalType, unitTime, signal_func, sleep_func);
}
