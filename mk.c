#include "mk_hdr.h"

void mk_cpy(void * dest, void * array, size_t size)
{

    uint8_t last_bytes = size % 8;
    size /= 8;
    
    if(dest == NULL)
    {
        dest = (int64_t *)malloc(size);
        if(dest == NULL)
        {
            fprintf(stdout, "\n {error with dynamic memory allocation!} \n");
        }

        for(size_t i = 0; i < size; i++)
        {
            (*(int64_t *)(dest + i)) = (*(int64_t *)(array + i));
        }
        if(last_bytes != 0)
        {
            for(size_t j = 0; j < last_bytes; j++)
            {
                (*(int8_t *)(dest + j)) = (*(int8_t *)(array + j));
            }
        }
    }
    else
    {
        for(size_t k = 0; k < size; k++)
        {
            (*(int64_t *)(dest + k)) = (*(int64_t *)(array + k));
        }
        if(last_bytes != 0)
        {
            for(size_t m = 0; m < last_bytes; m++)
            {
                (*(int8_t *)(dest + m)) = (*(int8_t *)(array + m));
            }
       
        }
    }
}

int64_t max(void * array, size_t size)
{
    int64_t max = (*(int64_t *)array);

    for(size_t i = 0; i < size; i++)
    {
        if(max < (*(int64_t *)(array + i)))
        {
            max = (*(int64_t *)(array + i));
        }
    }

    return max;
}