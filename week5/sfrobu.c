#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int isIgnore = 0;

char decode (const char* c){
    if(isIgnore == 0)
        return (*c) ^ 42;
    else {
        if((*c ^ 42) >= 'a' && (*c ^ 42) <= 'z')
            return toupper(*c ^ 42);
        else
            return (*c) ^ 42;
    }
}

int frobcmp(char const *a, char const *b) {
    if (!a && !b)
        return 0;
    else if (!a)
        return -1;
    else if (!b)
        return 1;
    else {
        int i = 0, j = 0;        
        while (i < strlen(a) && i < strlen(b)) {
            if (*(a + i) != ' ' && *(b + i) != ' ') {
                if (decode(a + i) > decode(b + i))
                    return 1;
                else if (decode(a + i) < decode(b + i))
                    return -1;
            } 
            else
                break;
            i++;
        }
        
        if (strlen(a) == strlen(b))
            return 0;
        else if (strlen(a) > strlen(b))
            return 1;
        else
            return -1;
    }
}

void checkAllocate(void *array) {
    if (!array) {
        fprintf(stderr, "malloc failed\n");
        exit(-1);
    }
}


void checkWrite(int ret) {
    if (ret < 0) {
        fprintf(stderr, "write failed\n");
        exit(-1);
    }
}

void fillLines(char **lines, char *input, int count) {
    size_t inputIndex, lineIndex;
    char *line = input;
    for (inputIndex = 0, lineIndex = 0; inputIndex < count; inputIndex++) {
        if (input[inputIndex] == ' ') {
            lines[lineIndex++] = line;
           line = input + inputIndex + 1;
        }
    }
}

int cmpWrapper(const void* a, const void* b);




void strWrite(const char* str)
{
    ssize_t ret;
    while (1) {
        ret = write(STDOUT_FILENO, str, 1);
        checkWrite(ret);
        if (*str++ == ' ')
            return;
    }
}


int main(int argc, char const *argv[]) {
    struct stat buf;
    if (fstat(0, &buf) < 0) {
        fprintf(stderr, "Error reading file.\n");
        exit(1);
    } 
    int bufSize = buf.st_size + 1;
    char *input = (char*)malloc(bufSize * sizeof(char));
    checkAllocate(input);
    
    int count = 0, lineNum = 0;
    char reader;
    while(read(0, &reader, 1) > 0) {
        if (count == 0 && reader == ' ')
            break;
        if (reader == ' ')
            lineNum++;
        input[count++] = reader;
        if (count >= bufSize) {
            input = realloc(input, 2 * bufSize);
	    bufSize *= 2;
        }
    }
    if (count < bufSize) {
        input[count] = ' ';
        count++;
        lineNum++;
    }
    char **lines = (char**)malloc(lineNum * sizeof(char*));
    checkAllocate(lines);
    fillLines(lines, input, count);
    checkAllocate(lines);
    
    if (argc == 2) {
	if (argv[1][0] == '-' && argv[1][1] == 'f')
	    isIgnore = 1;
    }
    int i = 0;
    int (* cmp) (const void *, const void *);
    cmp = &cmpWrapper; 
    qsort(lines, lineNum, sizeof(char*), cmp);
    
    for (i = 0; i < lineNum; i++)
        strWrite(lines[i]);
    
    free(input);
    free(lines);
}

inline
int cmpWrapper(const void* a, const void* b) {
    return frobcmp(*((char const**) a), *((char const**) b));
}
