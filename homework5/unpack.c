/**
 * @file unpack.c
 * @author Sam Whitlock (sjwhitlo)
 *
 * Takes two (or 3) command line arguments. Reads a compressed file,
 * and converts it to an uncompressed version based on the wordlist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "wordlist.h"
#include "bits.h"

/** Usage message. */
#define USAGE "usage: unpack <compressed.raw> <output.txt> [word_file.txt]"
/** Can't open file. */
#define FILE_ERROR "Can't open file: %s\n"
/** Expected number of command line arguments. */
#define CMD_ARGS 3

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
 * Takes two files as parameters. One to uncompress, and the output.
 * Optionally, a third file can be listed, the alternate word list.
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
    
    // Read WordList
    WordList *wordList = readWordList( wordFile );
    
    // Read in filenames
    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "w");
    
    // Errors for not able to open file
    if (!input) {
        fprintf(stderr, FILE_ERROR, argv[1]);
        error(USAGE);
    }
    if (!output) {
        fprintf(stderr, FILE_ERROR, argv[2]);
        error(USAGE);
    }
    
    // Create the things to send to readCode
    PendingBits pending = {0, 0};
    int code;
    
    // Read the code
    while ((code = readCode(&pending, input)) != -1) {
        // Output
        fprintf(output, "%s", wordList->words[code]);
    }
    
    // Free memory
    freeWordList(wordList);
    fclose(input);
    fclose(output);
    
    return EXIT_SUCCESS;
}
