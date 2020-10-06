#pragma once

#ifndef LIBMORSE_H_INCLUDED
#define LIBMORSE_H_INCLUDED

void resetMorseParams();
void setMorseParams(unsigned char dotUnit, unsigned char dashUnit,
                    unsigned char letterSpaceUnit,
                    unsigned char letterPartSpaceUnit,
                    unsigned char wordSpaceUnit);


#endif // LIBMORSE_H_INCLUDED
