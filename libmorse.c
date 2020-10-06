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

void resetMorseParams(){
    dotUnitLen = 1;
    dashUnitLen = 3;
    letterSpaceUnitLen = 3;
    letterPartSpaceUnitLen = 1;
    wordSpaceUnitLen = 7;
}

void setMorseParams(unsigned char dotUnit, unsigned char dashUnit,
                    unsigned char letterSpaceUnit,
                    unsigned char letterPartSpaceUnit,
                    unsigned char wordSpaceUnit){
    dotUnitLen = dotUnit;
    dashUnitLen = dashUnit;
    letterSpaceUnitLen = letterSpaceUnit;
    letterPartSpaceUnitLen = letterPartSpaceUnit;
    wordSpaceUnitLen = wordSpaceUnit;
}
