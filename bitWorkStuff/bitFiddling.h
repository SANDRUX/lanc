#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAXSYMBOLS 8

unsigned int hex_to_uint(char *, size_t );
int hex_to_int(char *, size_t );
float hex_to_float(char *, size_t );
static char hex_to_num(char );
