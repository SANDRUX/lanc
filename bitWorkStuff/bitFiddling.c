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

    return 1;
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

    int whole_bits;
    int fraction_bits;

    switch (bytes) 
    {
        case 1:
            whole_bits = 4;
            fraction_bits = 4;
            break;

        case 2:
            whole_bits = 10;
            fraction_bits = 6;
            break;

        case 3:
            whole_bits = 16;
            fraction_bits = 8;
            break;

        case 4:
            whole_bits = 22;
            fraction_bits = 10;
    }

    int s = binary[0];
    int whole = 0;
    int fraction = 0;

    for (int i = 0; i < whole_bits; i++)
    {
        whole += binary[wholebits - i] * pow(2, i);
    }
        
    for (int i = 0; i < fraction_bits; i++)
    {
        fraction += binary[bits - 1 - i] * pow(2, i);
    }

    float exponent = whole - (pow(2, whole_bits - 1) - 1);
    float mantissa = 1;

    for(int i = 0; i < fraction_bits; i++)
    {
        mantissa += binary[whole_bits + 1 + i] / pow(2, i + 1);
    }

    float result = sign * pow(2, exponent) * mantissa;

    return result;
}
