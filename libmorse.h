#pragma once

#ifndef LIBMORSE_H_INCLUDED
#define LIBMORSE_H_INCLUDED

#define RETURN_MORSE_NOTATION 0
#define RETURN_MORSE_SIGNAL_STREAM 1
#define MAX_MORSE_TEXT_SIZE_PER_CHAR 6+1 // six for morse signs and one for spacing for the next char
#define MAX_MORSE_SIGNAL_STREAM_SIZE_PER_CHAR 6*3+5+3 // three per dash times six morse signs plus 5 for spacing between signs plus three for spacing between chars

void initEncoder();
unsigned char * encodeMorseDynMemAlloc(const unsigned char * src, char returnType);
unsigned char * encodeMorse(unsigned char * dest, const unsigned char * src, unsigned long capacity, char returnType);
void sendMorseStream(const unsigned char * signalStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time));
void sendMorse(const unsigned char * morse, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time));
void destroyMorseLibAlloc();

#endif // LIBMORSE_H_INCLUDED
