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

typedef struct {
    unsigned char numbers[10][6];
    unsigned char letters[26][5];
    unsigned char fullStopPeriod[7];
    unsigned char colon[7];
    unsigned char apostrophe[7];
    unsigned char comma[7];
    unsigned char exclamationMark[7];
    unsigned char questionMark[7];
    unsigned char quotationMarks[7];
    unsigned char slash[6];
    unsigned char hyphen[7];
    unsigned char plusSign[6];
    unsigned char equalsSign[6];
    unsigned char bracketOpen[6];
    unsigned char bracketClosed[7];
    unsigned char atSign[7];
    unsigned char ampersand[6];
} Encoder;

typedef struct {
    unsigned char dotUnitLen, dashUnitLen, letterSpaceUnitLen, letterPartSpaceUnitLen, wordSpaceUnitLen;
} MorseParams;

static MorseParams * parameters = NULL;
static Encoder * encoder = NULL;

void initParams(){
    if(parameters==NULL){
        parameters = (MorseParams*) malloc(sizeof(MorseParams));
        if(parameters==NULL) return;
    }
    parameters->dotUnitLen = 1;
    parameters->dashUnitLen = 3;
    parameters->letterSpaceUnitLen = 3;
    parameters->letterPartSpaceUnitLen = 1;
    parameters->wordSpaceUnitLen = 7;
}

void initEncoderData(){
    if(encoder==NULL){
        encoder = (Encoder*) malloc(sizeof(Encoder));
        if(encoder==NULL) return;
    }
    strcpy(encoder->numbers[0], "-----\0");  //0
    strcpy(encoder->numbers[1], ".----\0");  //1
    strcpy(encoder->numbers[2], "..---\0");  //2
    strcpy(encoder->numbers[3], "...--\0");  //3
    strcpy(encoder->numbers[4], "....-\0");  //4
    strcpy(encoder->numbers[5], ".....\0");  //5
    strcpy(encoder->numbers[6], "-....\0");  //6
    strcpy(encoder->numbers[7], "--...\0");  //7
    strcpy(encoder->numbers[8], "---..\0");  //8
    strcpy(encoder->numbers[9], "----.\0");  //9
    strcpy(encoder->letters[0], ".-\0");     //A
    strcpy(encoder->letters[1], "-...\0");   //B
    strcpy(encoder->letters[2], "-.-.\0");   //C
    strcpy(encoder->letters[3], "-..\0");    //D
    strcpy(encoder->letters[4], ".\0");      //E
    strcpy(encoder->letters[5], "..-.\0");   //F
    strcpy(encoder->letters[6], "--.\0");    //G
    strcpy(encoder->letters[7], "....\0");   //H
    strcpy(encoder->letters[8], "..\0");     //I
    strcpy(encoder->letters[9], ".---\0");   //J
    strcpy(encoder->letters[10], "-.-\0");   //K
    strcpy(encoder->letters[11], ".-..\0");  //L
    strcpy(encoder->letters[12], "--\0");    //M
    strcpy(encoder->letters[13], "-.\0");    //N
    strcpy(encoder->letters[14], "---\0");   //O
    strcpy(encoder->letters[15], ".--.\0");  //P
    strcpy(encoder->letters[16], "--.-\0");  //Q
    strcpy(encoder->letters[17], ".-.\0");   //R
    strcpy(encoder->letters[18], "...\0");   //S
    strcpy(encoder->letters[19], "-\0");     //T
    strcpy(encoder->letters[20], "..-\0");   //U
    strcpy(encoder->letters[21], "...-\0");  //V
    strcpy(encoder->letters[22], ".--\0");   //W
    strcpy(encoder->letters[23], "-..-\0");  //X
    strcpy(encoder->letters[24], "-.--\0");  //Y
    strcpy(encoder->letters[25], "--..\0");  //Z
    strcpy(encoder->fullStopPeriod, ".-.-.-\0");
    strcpy(encoder->colon, "---...\0");
    strcpy(encoder->apostrophe, ".----.\0");
    strcpy(encoder->comma, "--..--\0");
    strcpy(encoder->exclamationMark, "-.-.--\0");
    strcpy(encoder->questionMark, "..--..\0");
    strcpy(encoder->quotationMarks, ".-..-.\0");
    strcpy(encoder->slash, "-..-.\0");
    strcpy(encoder->hyphen, "-....-\0");
    strcpy(encoder->plusSign, ".-.-.\0");
    strcpy(encoder->equalsSign, "-...-\0");
    strcpy(encoder->bracketOpen, "-.--.\0");
    strcpy(encoder->bracketClosed, "-.--.-\0");
    strcpy(encoder->atSign, ".--.-.\0");
    strcpy(encoder->ampersand, ".-...\0");
}

void initEncoder(){
    initParams();
    if(parameters!=NULL) initEncoderData();
}

int isEncoderReady(){
    if(parameters==NULL || encoder==NULL) return 0;
    else return 1;
}


void addCharacterToStream(unsigned char * ret, const unsigned char * morseKey, unsigned long * retiter, char returnType){
    if(returnType == RETURN_MORSE_SIGNAL_STREAM)
        for(; *morseKey != NULL_TERMINATOR; morseKey++){
            if(*morseKey==MORSE_DOT)
                for(int j = 0; j<parameters->dotUnitLen; j++)
                    ret[(*retiter)++]=MORSE_SIGNAL_ON;
            else if(*morseKey==MORSE_DASH)
                for(int j = 0; j<parameters->dashUnitLen; j++)
                    ret[(*retiter)++]=MORSE_SIGNAL_ON;
            for(int k = 0; k<parameters->letterPartSpaceUnitLen && *(morseKey+1) != NULL_TERMINATOR; k++)
                ret[(*retiter)++]=MORSE_SIGNAL_OFF;
        }
    else if(returnType == RETURN_MORSE_NOTATION)
        for(; *morseKey != NULL_TERMINATOR; morseKey++)
            ret[(*retiter)++]=*morseKey;
    else return;
}

void encodeCharacter(unsigned char * ret, unsigned char currChar, const unsigned char * src, unsigned long * retiter, unsigned long srciter, char returnType){
    switch(currChar){
        case ASCII_SPACE:
            if(returnType==RETURN_MORSE_SIGNAL_STREAM)
                for(int k = 0; k<parameters->wordSpaceUnitLen; k++)
                    ret[(*retiter)++]=MORSE_SIGNAL_OFF;
            else{
                    ret[(*retiter)++]=ASCII_SPACE;
                    ret[(*retiter)++]=ASCII_SPACE;
                    ret[(*retiter)++]=ASCII_SPACE;
            }
            break;
        case ASCII_FSTOP_PERIOD:
            addCharacterToStream(ret, encoder->fullStopPeriod, retiter, returnType);
            break;
        case ASCII_COLON:
            addCharacterToStream(ret, encoder->colon, retiter, returnType);
            break;
        case ASCII_APOSTROPHE:
            addCharacterToStream(ret, encoder->apostrophe, retiter, returnType);
            break;
        case ASCII_COMMA:
            addCharacterToStream(ret, encoder->comma, retiter, returnType);
            break;
        case ASCII_EXCLAMATION_MARK:
            addCharacterToStream(ret, encoder->exclamationMark, retiter, returnType);
            break;
        case ASCII_QUESTION_MARK:
            addCharacterToStream(ret, encoder->questionMark, retiter, returnType);
            break;
        case ASCII_QUOTATION_MARKS:
            addCharacterToStream(ret, encoder->quotationMarks, retiter, returnType);
            break;
        case ASCII_SLASH:
            addCharacterToStream(ret, encoder->slash, retiter, returnType);
            break;
        case ASCII_HYPHEN:
            addCharacterToStream(ret, encoder->hyphen, retiter, returnType);
            break;
        case ASCII_PLUS_SIGN:
            addCharacterToStream(ret, encoder->plusSign, retiter, returnType);
            break;
        case ASCII_EQUALS_SIGN:
            addCharacterToStream(ret, encoder->equalsSign, retiter, returnType);
            break;
        case ASCII_BRACKET_OPEN:
            addCharacterToStream(ret, encoder->bracketOpen, retiter, returnType);
            break;
        case ASCII_BRACKET_CLOSED:
            addCharacterToStream(ret, encoder->bracketClosed, retiter, returnType);
            break;
        case ASCII_AT_SIGN:
            addCharacterToStream(ret, encoder->atSign, retiter, returnType);
            break;
        case ASCII_AMPERSAND:
            addCharacterToStream(ret, encoder->ampersand, retiter, returnType);
            break;
        default:
            if((currChar<ASCII_A || currChar>ASCII_Z) && (currChar<ASCII_ZERO || currChar>ASCII_NINE)) return;
            else addCharacterToStream(ret, (currChar-ASCII_ZERO<=9) ? encoder->numbers[currChar-ASCII_ZERO] : encoder->letters[currChar-ASCII_A], retiter, returnType);
        }
        if(returnType==RETURN_MORSE_SIGNAL_STREAM)
            for(int k = 0; k<parameters->letterSpaceUnitLen && *(src+srciter) != ASCII_SPACE && *(src+srciter+1) != ASCII_SPACE && *(src+srciter+1) != NULL_TERMINATOR; k++)
                ret[(*retiter)++]=MORSE_SIGNAL_OFF;
        else if(returnType==RETURN_MORSE_NOTATION && *(src+srciter) != ASCII_SPACE && *(src+srciter+1) != ASCII_SPACE && *(src+srciter+1) != NULL_TERMINATOR)
            ret[(*retiter)++]=ASCII_SPACE;
}

unsigned char* encode(unsigned char * dest, const unsigned char * src, unsigned long capacity, char returnType){
    if(returnType!=RETURN_MORSE_NOTATION && returnType!=RETURN_MORSE_SIGNAL_STREAM)
        return NULL;
    unsigned long i, destiter = 0;
    for(i = 0; i<strlen(src); i++){
        unsigned char tempChar = (unsigned char) toupper(src[i]);
        unsigned long retiter = 0;
        unsigned char ret[MAX_MORSE_SIGNAL_STREAM_SIZE_PER_CHAR+1] = {0};
        encodeCharacter(ret,tempChar, src, &retiter, i, returnType);
        if(capacity!=0 && destiter+retiter>capacity-1)
            return NULL;
        strcat(dest+destiter,ret);
        destiter+=retiter;
    }
    return dest;
}

unsigned char * encodeMorseDynMemAlloc(const unsigned char * src, char returnType){
    if(isEncoderReady()==0) return NULL;
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

unsigned char * encodeMorse(unsigned char * dest, const unsigned char * src, unsigned long capacity, char returnType){
    if(isEncoderReady()==0) return NULL;
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

void sendMorseStream(const unsigned char * dataStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    if(isEncoderReady()==0) return;
    int consecutiveSignals = 0;
    unsigned char signalType = MORSE_SIGNAL_OFF;
    unsigned long len = strlen(dataStream);
    for(unsigned long i = 0; i<len; i++){
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

void sendMorse(const unsigned char * morse, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time)){
    if(isEncoderReady()==0) return;
    unsigned long len = strlen(morse);
    for(unsigned long i = 0; i<len; i++){
        if(morse[i]==ASCII_SPACE && morse[i+1]!=ASCII_SPACE)
            sendFrame(parameters->letterSpaceUnitLen, MORSE_SIGNAL_OFF, unitTime, signal_func, sleep_func);
        else if(morse[i]==ASCII_SPACE && morse[i+1]==ASCII_SPACE && morse[i+2]!=NULL_TERMINATOR && morse[i+2]==ASCII_SPACE){
            sendFrame(parameters->wordSpaceUnitLen, MORSE_SIGNAL_OFF, unitTime, signal_func, sleep_func);
            i+=2;
        }else if(morse[i+1]==NULL_TERMINATOR || morse[i+1]==ASCII_SPACE){
            if(morse[i]==MORSE_DOT) sendFrame(parameters->dotUnitLen, MORSE_SIGNAL_ON, unitTime, signal_func, sleep_func);
            else if(morse[i]==MORSE_DASH) sendFrame(parameters->dashUnitLen, MORSE_SIGNAL_ON, unitTime, signal_func, sleep_func);
        }else{
            if(morse[i]==MORSE_DOT) sendFrame(parameters->dotUnitLen, MORSE_SIGNAL_ON, unitTime, signal_func, sleep_func);
            else if(morse[i]==MORSE_DASH) sendFrame(parameters->dashUnitLen, MORSE_SIGNAL_ON, unitTime, signal_func, sleep_func);
            if(morse[i]==MORSE_DOT || morse[i]==MORSE_DASH)sendFrame(parameters->letterPartSpaceUnitLen, MORSE_SIGNAL_OFF, unitTime, signal_func, sleep_func);
        }
    }
}

void destroyMorseLibAlloc(){
    free(parameters);
    parameters = NULL;
    free(encoder);
    encoder = NULL;
}
