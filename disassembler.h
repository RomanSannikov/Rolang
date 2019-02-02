#ifndef rolang_disassembler_h
#define rolang_disassembler_h

#include <stdio.h>

#include "bucket.h"

static int disassembleInstruction(Bucket*, uint8_t, int);
void disassemble(Bucket*);

#endif