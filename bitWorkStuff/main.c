#include "bitFiddling.h"

extern unsigned int hex_to_uint(char * hex, size_t size);
extern int hex_to_int(char * hex, size_t size);
extern float hex_to_float(char * hex, size_t size);

int main()
{
    char array[8];
    char type;

    printf("enter hex value: ");
    scanf("%s", array);
    printf("\n");
    printf("enter type of converted data (S/U/F): ");
    scanf("%c", &type);
    printf("\n");

    if(strlen(array) > 8)
    {
        printf("too many characters!");
        exit(EXIT_FAILURE);
    }


    if ((strlen(array) % 2) == 1)
    {
        char * temp = "0";
        strcat(temp, array);
        strcpy(array, temp);
    }

    switch (type)
    {
        case 'U':
        printf("%ud", hex_to_uint(array, strlen(array)));

        break;

        case 'S':
        printf("%d", hex_to_int(array, strlen(array)));

        break;

        case 'F':
        printf("%f", hex_to_float(array, strlen(array)));

        break;

        default:
        printf("Invalid data type");

    }

    return 0;
}
