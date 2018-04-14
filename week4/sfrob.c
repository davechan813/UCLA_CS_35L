#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// name: Zhibang Chen
// UID: 804783490

int frobcmp(char const *a, char const *b)
{
    while (*a != ' ' && *b != ' ')
    {
        if ((*a ^ 42) > (*b ^ 42))
            return 1;
        else if((*a ^ 42) < (*b ^ 42))
            return -1;
        a++;
        b++;
    }
    
    if (*a == 32 && *b == 32) {
        return 0;
    } else if (*a == 32) {
        return 1;
    } else if (*b == 32) {
        return -1;
    }
    return 0;
}

int compare(void const *x, void const *y)
{
    return frobcmp( *((char**)x), *((char**)y) );
}

int main() {
    int init_space = 10;
    char* input_arr = (char*) malloc(sizeof(char) * init_space);
    
    if (input_arr == NULL)
    {
        fprintf(stderr, "Failure in allocating memory");
        exit(1);
    }
    char input_char = getchar();
    
    if (ferror(stdin))
    {
        fprintf(stderr, "Problem in standard input");
        exit(1);
    }
    
    
    if (input_char == EOF)
    {
        free(input_arr);
        exit(1);
    }
    
    int index = 0;
    int n_words = 0;
    while (input_char != EOF)
    {
        if (index >= init_space)
        {
            init_space *= 2;
            input_arr = (char*)realloc(input_arr, init_space);
            if (input_arr == NULL)
            {
                fprintf(stderr, "Failure in re-allocating memory");
                exit(1);
            }
        }
        
        
        
        if (input_char != ' ')
        {
            input_arr[index] = input_char;
            index++;
        }
        else if (index>1 && input_char == ' ')      
        {
            if (input_arr[index-1] != ' ')
            {
                n_words++;
                input_arr[index] = input_char;
                index++;
            }
        }
        input_char = getchar();
        
        
    }

    if (input_arr[index-1] != ' ')
    {
        if (index >= init_space)
        {
            init_space += 1; 
            input_arr =  (char*)realloc(input_arr, init_space);
            
            // check for failure
            if (input_arr == NULL)
            {
                fprintf(stderr, "Failure in re-allocating memory");
                exit(1);
            }
        }
        input_arr[index] = ' '; 
        n_words++;
    }
    
    char** input_line = (char**)malloc(sizeof(char*)*n_words);
    if (input_line == NULL)
    {
        fprintf(stderr, "Failure in re-allocating memory");
        exit(1);
    }
    
    char *temp_arr = input_arr;
    for (int j = 0; j < n_words; j++)
    {
        input_line[j] = input_arr;
        if (j+1 == n_words) 
        {
            break;
        }
        
        while ((*input_arr) != 32)
        {
            input_arr++; 
        }
        input_arr++; 
    }
    
    qsort(input_line, n_words, sizeof(char*), compare);
    
    
    char* output;
    for (int i=0; i<n_words; ++i)
    {
        output = input_line[i];
        putchar(*output);
        if (ferror(stdout))
        {
            fprintf(stderr, "Output Error");
            exit(1);
        }
        while (*output != 32)
        {
            output++; 
            putchar(*output);
        }
    }
    

    free(input_line);
    free(temp_arr);
    
    return 0;
}
