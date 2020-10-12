#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libmorse.h"

#define NULL_TERMINATOR '\0'
#define MORSE_SIGNAL_ON '1'
#define MORSE_SIGNAL_OFF '0'
#define MORSE_DOT '.'
#define MORSE_DASH '-'
#define ASCII_ZERO '0'
#define ASCII_A 'A'
#define ASCII_NINE '9'
#define ASCII_Z 'Z'
#define ASCII_SPACE ' '
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

static const unsigned char numbers[10][6] = {
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

static const unsigned char letters[26][5] = {
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

static const unsigned char fullStopPeriod[7] = ".-.-.-\0";
static const unsigned char colon[7] = "---...\0";
static const unsigned char apostrophe[7] = ".----.\0";
static const unsigned char comma[7] = "--..--\0";
static const unsigned char exclamationMark[7] = "-.-.--\0";
static const unsigned char questionMark[7] = "..--..\0";
static const unsigned char quotationMarks[7] = ".-..-.\0";
static const unsigned char slash[6] = "-..-.\0";
static const unsigned char hyphen[7] = "-....-\0";
static const unsigned char plusSign[6] = ".-.-.\0";
static const unsigned char equalsSign[6] = "-...-\0";
static const unsigned char bracketOpen[6] = "-.--.\0";
static const unsigned char bracketClosed[7] = "-.--.-\0";
static const unsigned char atSign[7] = ".--.-.\0";
static const unsigned char ampersand[6] = ".-...\0";

static const unsigned char dotUnitLen = 1;
static const unsigned char dashUnitLen = 3;
static const unsigned char letterSpaceUnitLen = 3;
static const unsigned char letterPartSpaceUnitLen = 1;
static const unsigned char wordSpaceUnitLen = 7;

void addCharacterToStream(unsigned char * ret, const unsigned char * morseKey, unsigned long * retiter, char returnType){
    if(returnType == RETURN_MORSE_SIGNAL_STREAM)
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
    else if(returnType == RETURN_MORSE_NOTATION)
        for(; *morseKey != NULL_TERMINATOR; morseKey++)
            ret[(*retiter)++]=*morseKey;
    else return;
}

unsigned char* encode(unsigned char * dest, unsigned char* src, unsigned long capacity, char returnType){
    if(returnType!=RETURN_MORSE_NOTATION && returnType!=RETURN_MORSE_SIGNAL_STREAM)
        return NULL;
    unsigned char *ret = dest;
    unsigned long i, retiter = 0;
    for(i = 0; i<strlen(src); i++){
        unsigned char tempChar = (unsigned char) toupper(src[i]);
        switch(tempChar){
        case ASCII_SPACE:
            if(returnType==RETURN_MORSE_SIGNAL_STREAM)
                for(int k = 0; k<wordSpaceUnitLen; k++)
                    ret[retiter++]=MORSE_SIGNAL_OFF;
            else ret[retiter++]=ASCII_SPACE;
            break;
        case ASCII_FSTOP_PERIOD:
            addCharacterToStream(ret, fullStopPeriod, &retiter, returnType);
            break;
        case ASCII_COLON:
            addCharacterToStream(ret, colon, &retiter, returnType);
            break;
        case ASCII_APOSTROPHE:
            addCharacterToStream(ret, apostrophe, &retiter, returnType);
            break;
        case ASCII_COMMA:
            addCharacterToStream(ret, comma, &retiter, returnType);
            break;
        case ASCII_EXCLAMATION_MARK:
            addCharacterToStream(ret, exclamationMark, &retiter, returnType);
            break;
        case ASCII_QUESTION_MARK:
            addCharacterToStream(ret, questionMark, &retiter, returnType);
            break;
        case ASCII_QUOTATION_MARKS:
            addCharacterToStream(ret, quotationMarks, &retiter, returnType);
            break;
        case ASCII_SLASH:
            addCharacterToStream(ret, slash, &retiter, returnType);
            break;
        case ASCII_HYPHEN:
            addCharacterToStream(ret, hyphen, &retiter, returnType);
            break;
        case ASCII_PLUS_SIGN:
            addCharacterToStream(ret, plusSign, &retiter, returnType);
            break;
        case ASCII_EQUALS_SIGN:
            addCharacterToStream(ret, equalsSign, &retiter, returnType);
            break;
        case ASCII_BRACKET_OPEN:
            addCharacterToStream(ret, bracketOpen, &retiter, returnType);
            break;
        case ASCII_BRACKET_CLOSED:
            addCharacterToStream(ret, bracketClosed, &retiter, returnType);
            break;
        case ASCII_AT_SIGN:
            addCharacterToStream(ret, atSign, &retiter, returnType);
            break;
        case ASCII_AMPERSAND:
            addCharacterToStream(ret, ampersand, &retiter, returnType);
            break;
        default:
            if((tempChar<ASCII_A || tempChar>ASCII_Z) && (tempChar<ASCII_ZERO || tempChar>ASCII_NINE)) continue;
            else addCharacterToStream(ret, (tempChar-ASCII_ZERO<=9) ? numbers[tempChar-ASCII_ZERO] : letters[tempChar-ASCII_A], &retiter, returnType);
        }
        if(returnType==RETURN_MORSE_SIGNAL_STREAM)
            for(int k = 0; k<letterSpaceUnitLen && *(src+i) != ASCII_SPACE && *(src+i+1) != ASCII_SPACE && *(src+i+1) != NULL_TERMINATOR; k++)
                ret[retiter++]=MORSE_SIGNAL_OFF;
    }
    return ret;
}

unsigned char * encodeMorseDynMemAlloc(unsigned char * src, char returnType){
    if(returnType == RETURN_MORSE_NOTATION){
        unsigned char * dest = (unsigned char *) calloc(strlen(src)*MAX_MORSE_TEXT_SIZE_PER_CHAR+1, sizeof(unsigned char));
        if(dest==NULL) return NULL;
        return encode(dest, src, 0, returnType);
    } else if(returnType == RETURN_MORSE_SIGNAL_STREAM){
        unsigned char * dest = (unsigned char *) calloc(strlen(src)*MAX_MORSE_SIGNAL_STREAM_SIZE_PER_CHAR+1, sizeof(unsigned char));
        if(dest==NULL) return NULL;
        return encode(dest, src, 0, returnType);
    } else return NULL;
}

unsigned char * encodeMorse(unsigned char * dest, unsigned char * src, unsigned long capacity, char returnType){
    if(returnType == RETURN_MORSE_NOTATION || returnType == RETURN_MORSE_SIGNAL_STREAM)
        return encode(dest, src, capacity, returnType);
    else return NULL;
}

void sendFrame(int consecutiveSignals, char signalType, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    if(consecutiveSignals!=0){
        if(signalType == MORSE_SIGNAL_ON) (*signal_func)(unitTime*consecutiveSignals);
        else (*sleep_func)(unitTime*consecutiveSignals);
    }
}

void sendMorse(unsigned char * dataStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    int consecutiveSignals = 0;
    unsigned char signalType = MORSE_SIGNAL_OFF;
    for(unsigned long i = 0; i<strlen(dataStream); i++){
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
