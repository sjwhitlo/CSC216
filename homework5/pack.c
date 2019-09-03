/**
 * @file pack.c
 * @author Sam Whitlock (sjwhitlo)
 *
 * Takes two (or 3) command line arguments. Reads a file, and converts it
 * to a compressed version based on the wordlist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "wordlist.h"
#include "bits.h"

/** Usage message. */
#define USAGE "usage: pack <input.txt> <compressed.raw> [word_file.txt]"
/** Can't open file. */
#define FILE_ERROR "Can't open file: %s\n"
/** Invalid word file. */
#define INVAL_WORD_FILE "Invalid word file"
/** Invalid char code. */
#define CHAR_CODE "Invalid character code: %x"
/** Expected number of command line arguments. */
#define CMD_ARGS 3
/** Initial size. */
#define INIT_SIZE 5
/** Size of an error char string. */
#define ECHAR 30

/**
 * Prints an error message passed in as a paramater.
 *
 * @param message a pointer to the message to be printed.
 */
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

/**
 * Reads in a file passed in as a parameter. Returns a pointer to
 * the buffer.
 *
 * @param fp A pointer to the file
 * @return The buffered string
 */
char *readFile(FILE *fp)
{
    // Allocate a string with a small, initial capacity.
    int capacity = INIT_SIZE;
    char *buffer = malloc( capacity * sizeof(char) );
    
    // Number of characters we're currently using.
    int len = 0;
    
    // Add chars to the end of the buffer.
    char in;
    while (fscanf(fp, "%c", &in) == 1 && in != EOF) {
        // Invalid chars
        if (!validChar(in)) {
            char invalChar[ECHAR];
            sprintf(invalChar, CHAR_CODE, in & 0xFF);
            error(invalChar);
        }
        
        // If going to write outside of bounds
        if (len == capacity - 2) {
            capacity *= 2;
            buffer = (char *)realloc(buffer, capacity * sizeof(char));
        }
        buffer[len++] = in;
        buffer[len + 1] = '\0';
    }
    
    // Return the buffer
    return buffer;
}

/**
 * Takes two files as parameters. One to compress, and the compressed
 * file. Optionally, a third file can be listed, the alternate word list.
 *
 * @param argc the number of command line arguments
 * @param argv the command line arguments
 */
int main( int argc, char *argv[] )
{
    char *wordFile = "words.txt";
    
    // If args are not correct
    if (argc != CMD_ARGS && argc != (CMD_ARGS + 1)) {
        error(USAGE);
    }
    // Set word file to alt list
    if (argc == CMD_ARGS + 1) {
        wordFile = argv[CMD_ARGS];
    }
    
    // Check for errors in the wordlist before in the files
    WordList *wordList = readWordList( wordFile );
    
    // Read in filenames
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wb");
    
    // Errors for not able to open file
    if (!input) {
        fprintf(stderr, FILE_ERROR, argv[1]);
        error(USAGE);
    }
    if (!output) {
        fprintf(stderr, FILE_ERROR, argv[2]);
        error(USAGE);
    }
    
#ifdef DEBUG
    // Report the entire contents of the word list, once it's built.
    printf( "---- word list -----\n" );
    for ( int i = 0; i < wordList->len; i++ )
        printf( "%d == %s\n", i, wordList->words[ i ] );
    printf( "--------------------\n" );
#endif
    // Read the contents of the whole file into one big buffer.  This could be more
    // efficient, but it simplifies the rest of the program.
    char *buffer = readFile( input );
    
    // Write out codes for everything in the buffer.
    int pos = 0;
    PendingBits pending = { 0, 0 };
    
    while ( buffer[ pos ] ) {
        // Get the next code.
        int code = bestCode( wordList, buffer + pos );
#ifdef DEBUG
        printf( "%d <- %s\n", code, wordList->words[ code ] );
#endif
        // Write it out and move ahead by the number of characters we just encoded.
        writeCode( code, &pending, output );
        pos += strlen( wordList->words[ code ] );
    }
    
    // printf("Break\n");
    
    // Write out any remaining bits in the last, partial byte.
    flushBits( &pending, output );
    
    // Free memory
    freeWordList(wordList);
    fclose(input);
    fclose(output);
    free(buffer);
    
    return EXIT_SUCCESS;
}
