#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MORSE_SIGNAL_ON '1'
#define MORSE_SIGNAL_OFF '0'
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

static const char fullStopPeriod[6] = ".-.-.-\0";
static const char colon[6] = "---...\0";
static const char apostrophe[6] = ".----.\0";
static const char comma[6] = "--..--\0";
static const char exclamationMark[6] = "-.-.--\0";
static const char questionMark[6] = "..--..\0";
static const char quotationMarks[6] = ".-..-.\0";
static const char slash[6] = "-..-.\0";
static const char hyphen[6] = "-....-\0";
static const char plusSign[6] = ".-.-.\0";
static const char equalsSign[6] = "-...-\0";

static unsigned char dotUnitLen = 1;
static unsigned char dashUnitLen = 3;
static unsigned char letterSpaceUnitLen = 3;
static unsigned char letterPartSpaceUnitLen = 1;
static unsigned char wordSpaceUnitLen = 7;

char* encode(char* text){
    char *ret = (char*) malloc(4096);
    int i, retiter = 0;
    for(i = 0; i<strlen(text); i++){
        char tempChar = (char) toupper(text[i]);
        if(tempChar == ASCII_SPACE)
            for(int k = 0; k<wordSpaceUnitLen; k++)
                ret[retiter++]=MORSE_SIGNAL_OFF;
        else{
            const char * tempMorseNotation = (tempChar-ASCII_ZERO<=9) ? numbers[tempChar-ASCII_ZERO] : letters[tempChar-ASCII_A];
            for(; *tempMorseNotation != '\0'; tempMorseNotation++){
                if(*tempMorseNotation=='.')
                    for(int j = 0; j<dotUnitLen; j++)
                        ret[retiter++]=MORSE_SIGNAL_ON;
                else if(*tempMorseNotation=='-')
                    for(int j = 0; j<dashUnitLen; j++)
                        ret[retiter++]=MORSE_SIGNAL_ON;
                for(int k = 0; k<letterPartSpaceUnitLen && *(tempMorseNotation+1) != '\0'; k++)
                    ret[retiter++]=MORSE_SIGNAL_OFF;
            }
            for(int k = 0; k<letterSpaceUnitLen && *(text+i+1) != ASCII_SPACE && *(text+i+1) != '\0'; k++)
                ret[retiter++]=MORSE_SIGNAL_OFF;
        }
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
