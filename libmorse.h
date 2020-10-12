#pragma once

#ifndef LIBMORSE_H_INCLUDED
#define LIBMORSE_H_INCLUDED

#define RETURN_MORSE_NOTATION 0
#define RETURN_MORSE_SIGNAL_STREAM 1
#define MAX_MORSE_TEXT_SIZE_PER_CHAR 6
#define MAX_MORSE_SIGNAL_STREAM_SIZE_PER_CHAR 6*3+5+3

unsigned char * encodeMorseDynMemAlloc(unsigned char * src, char returnType);
unsigned char * encodeMorse(unsigned char * dest, unsigned char * src, unsigned long capacity, char returnType);
void sendMorse(unsigned char * signalStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time));

#endif // LIBMORSE_H_INCLUDED
