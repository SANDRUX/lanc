#include "bitFiddling.h"

unsigned int hex_to_uint(char * hex, size_t size)
{
    unsigned int buff = 0;
    char num;

    for (int i = 0; i < (int)size; i++)
    {
        num = hex_to_num(hex[(size - 1) - i]);
        buff += num * pow(16, i);
    }

    return buff;
}

static char hex_to_num(char hex)
{
    if (hex >= '0' && hex <= '9')
    {
        return (hex - '0');
    }
    else if(hex >= 'A' && hex <= 'F')
    {
        return (hex - 55);
    }
    else
    {
        printf("\n Invalid data");
        exit(EXIT_FAILURE);
    }
}

int hex_to_int(char * hex, size_t size)
{
    char bytes = size / 2;

    unsigned int num = hex_to_uint(hex, size);
    unsigned int power = pow(2, (8 * bytes) - 1);

    if ((num & power) == 0)
    {
        return num;
    }

    else
    {
        num -= power;
        num -= power;
        return num;
    }
}

float hex_to_float(char * hex, size_t size)
{
    char bits = (size / 2) * 8;
    char bytes = bits  / 8;
    bool binary[bits];

    unsigned int decimal = hex_to_uint(hex, size);

    for (int i = 0; i < bits; i++)
    {
        binary[i] = (decimal >> (bits - 1 - i)) & 1;
    }

    return (float)1;
}
