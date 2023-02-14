#include "StringFunctions.h"

//==============================================================================

size_t my_strlen(const char* str)
{
    size_t sum = 0;

    while (str[sum] != '\0')
        sum++;

    return sum;
}

//==============================================================================

size_t my_null_strlen(const char* str)
{
    size_t sum = 0;

    while (str[sum] != '\0')
        sum++;

    return sum + 1;
}

//==============================================================================

size_t my_puts(const char* str)
{
    size_t i = 0;

    if (my_strlen(str) != 0)
    {
        for (; i < my_strlen(str); i++)
            putchar(str[i]);
    }

    return i;
}

//==============================================================================

char* my_strchr(char* str, char chr)
{
    for(size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == chr)
            return str + i + 1;
    }

    return NULL;
}

//==============================================================================

char* my_strcpy(char* dest, const char* src)
{
    size_t i = 0;

    do{
        dest[i] = src[i];
        i++;
    } while(src[i] != '\0');
    
    dest[i] = '\0';

    return dest;
}

//==============================================================================

char* my_strncpy(char* dest, const char* src, size_t n)
{
    size_t i = 0;

    for(; i < my_strlen(src); i++)
    {
        if(i < n)
            dest[i] = src[i];
    }
    
    for(; i < n; i++)
        dest[i] = '\0';

    return dest;
}

//==============================================================================

char* my_strcat(char* dest, const char* append)
{
    size_t i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0');  
    
    return dest;
}

//==============================================================================

char* my_strncat(char* dest, const char* append, size_t n)
{
    size_t i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0')
    {
        if (j == n)
            return dest;
    }
    
    return dest;
}

//==============================================================================

const char* my_fgets(FILE* stream, size_t size_of_dest, char* dest)
{
    if (stream != NULL)
    {
        int ch = fgetc(stream);

        const char* dest_start = dest;

        while ((ch != '\n') && (ch != EOF) && ((size_t)(dest - dest_start) < size_of_dest))
        {
            *dest = (char)ch;
            dest++;
            ch = fgetc(stream);
        }

        *dest = '\0';

        return dest_start;
    }

    else
    {
        return nullptr;
    }
}

//==============================================================================

char* my_strdup(char* src)
{
    size_t length = my_null_strlen(src);

    char* dest = (char*)calloc(length, sizeof(char));

    my_strncpy(dest, src, length);

    return dest;
}

//==============================================================================

size_t my_getline(char** lineptr, size_t* n, FILE* stream)
{
    rewind(stream); 

    if ((*lineptr == nullptr) || (*n == 0))
    {
        size_t chars_num = 0;
        
        int ch = fgetc(stream);

        for(; (ch != '\n') && (ch != EOF); chars_num++)
        {
            ch = fgetc(stream);
        }

        rewind(stream);

        if(*n == 0)
        {
            *n = chars_num + 1;
        }

        char* new_lineptr = (char*)calloc(*n, sizeof(char));

        for(size_t i = 0; i < chars_num + 1; i++)
        {
            new_lineptr[i] = (char)getc(stream);
        }

        rewind(stream);

        new_lineptr[chars_num] = '\0';

        *lineptr = new_lineptr;

        return ++chars_num;
    }

    else 
    {
        size_t buffer_size = *n;

        size_t chars_num  = 0;

        int ch = fgetc(stream);

        for(; (ch != '\n') && (ch != EOF); chars_num++)
        {
            ch = fgetc(stream);
        }
        
        rewind(stream);

        if (buffer_size >= chars_num + 1)
        {
            for(size_t i = 0; i < chars_num; i++)
            {
                (*lineptr)[i] = (char)getc(stream);
            }

            rewind(stream);

            (*lineptr)[chars_num] = '\0';

            return ++chars_num;
        }

        else
        {
            *lineptr = (char*)realloc(*lineptr, (chars_num + 1)*sizeof(char));

            for(size_t i = 0; i < chars_num; i++)
            {
                (*lineptr)[i] = (char)getc(stream);
            }

            rewind(stream);

            (*lineptr)[chars_num] = '\0';

            return ++chars_num;
        }
    }
}
