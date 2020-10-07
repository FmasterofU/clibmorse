#include <string.h>
#include <ctype.h>


#define MORSE_SIGNAL_ON '1'
#define MORSE_SIGNAL_OFF '0'
#define ASCII_ZERO 48 // '0'
#define ASCII_A 65  // 'A'
#define ASCII_SPACE 32 // ' '

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

static unsigned char dotUnitLen = 1;
static unsigned char dashUnitLen = 3;
static unsigned char letterSpaceUnitLen = 3;
static unsigned char letterPartSpaceUnitLen = 1;
static unsigned char wordSpaceUnitLen = 7;

char* encode(char* text){
    char *ret = malloc(4096);
    int i, retiter = 0;
    for(i = 0; i<strlen(text); i++){
        char tempChar = (char) toupper(text[i]);
        if(tempChar == ASCII_SPACE)
            for(int k = 0; k<wordSpaceUnitLen; k++)
                ret[retiter++]=MORSE_SIGNAL_OFF;
        else {
            char * tempMorseNotation = (tempChar-ASCII_ZERO<=9) ? numbers[tempChar-ASCII_ZERO] : letters[tempChar-ASCII_A];
            for(;*tempMorseNotation != '\0';tempMorseNotation++){
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
