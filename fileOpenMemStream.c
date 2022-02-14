#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *filePtr;

    // Open file
    filePtr = fopen("lipsum.data", "r");
    if (filePtr == NULL) {
        fprintf(stderr, "file is not available\n");
        return 1;
    }

    FILE *stream;
    char *bufferPtr = NULL;
    size_t size = 0;

    // Open stream
    stream = open_memstream(&bufferPtr, &size);
    if (stream == NULL) {
        fprintf(stderr, "fopen error\n");
        return 1;
    }

    // Write data from file to stream
    char ch;
    while ((ch = fgetc(filePtr)) != EOF) {
        fputc(ch, stream);
    }

    // Flush before read buffer
    fflush(stream);
    printf("%s", bufferPtr);

    // Close and free all memory stuff
    fclose(filePtr);
    fclose(stream);
    free(bufferPtr);

    return 0;
}

