#pragma once

#ifndef LIBMORSE_H_INCLUDED
#define LIBMORSE_H_INCLUDED

char* encode(char*);
void send(char * dataStream, long unitTime, void (*signal_func) (long time), void (*sleep_func)(long time));

#endif // LIBMORSE_H_INCLUDED
