/**
 * @file wordlist.c
 * @author Sam Whitlock (sjwhitlo)
 *
 * Portion of the program that does the actual handling of the
 * WordList
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "wordlist.h"

/** Can't open file. */
#define WORD_FILE_ERROR "Can't open word file: %s\n"
/** File error message. */
#define INVAL_WORD_FILE "Invalid word file\n"

/** Tabs are valid characters. */
#define VALID_TAB '\t'
/** New lines are valid characters. */
#define VALID_NL '\n'
/** Carraige returns are valid characters. */
#define VALID_RET '\r'
/** Space is the lowest possible char valid. */
#define VALID_MIN ' '
/** Tilda is the highest possible char valid. */
#define VALID_MAX '~'
/** Initial size. */
#define INIT_SIZE 5
/** Max number of words in a word file. */
#define NUM_WORDS_MAX 414

/**
 * Compares two words lexicographically , and returns negative if
 * the first comes first, 0 if the same, and positive if the first
 * comes after the second.
 *
 * @param a A pointer to the first word
 * @param b A pointer to the second word
 * @return neg if a < b, 0 if equal, else pos
 */
int compareWords(const void *a, const void *b)
{
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;
    
    return strncmp(ia, ib, WORD_MAX);
}

/**
 * Returns true if the char is valid
 *
 * @param ch The char being checked
 * @return true if the char is valid
 */
bool validChar( char ch )
{
    if (ch == VALID_TAB) {
        return true;
    } else if (ch == VALID_RET) {
        return true;
    } else if (ch == VALID_NL) {
        return true;
    } else if (ch >= VALID_MIN && ch <= VALID_MAX) {
        return true;
    } else {
        return false;
    }
}

/**
 * Adds the given char to the given wordList.
 *
 * @param list A pointer to the WordList
 * @param ch The char to be added
 */
void addChar(WordList *list, unsigned char ch)
{
    if (list->len == list->capacity - 1) {
        list->capacity *= 2;list->words =
        (Word *)realloc(list->words, list->capacity * sizeof(Word));
    }
    
    // Assign the char
    char term = '\0';
    char w[WORD_MAX + 1];
    sprintf(w, "%c%c", ch, term);
    
    // Assign to rear
    strncpy(list->words[list->len], w, 1);
    (list->len)++;
}

/**
 * Builds the WordList from one pointer to a string.
 *
 * @param fname a pointer to the string
 * @return The WordList
 */
WordList *readWordList( char const *fname )
{
    // Try to read in file
    FILE *wf = fopen(fname, "r");
    // If file not found, print error and exit.
    if (!wf) {
        // Print error message to stderr
        fprintf(stderr, WORD_FILE_ERROR, fname);
        // Exit unsuccessfully
        exit(EXIT_FAILURE);
    }
    
    // Create the WordList {len, capacity, *word}
    WordList *list = (WordList *)malloc(sizeof(WordList));
    list->len = 0;
    list->capacity = INIT_SIZE;
    list->words = (Word *)malloc(sizeof(Word) * list->capacity);
    
    // Variables for temp storage
    int num = 0;
    char w[WORD_MAX + 1];
    
    // Add the 98 chars
    addChar(list, '\t');
    addChar(list, '\n');
    addChar(list, '\r');
    for (char i = VALID_MIN; i <= VALID_MAX; i++) {
        addChar(list, i);
    }
    
    // Counter variable
    int count = 0;
    // Read in word list
    while (fscanf(wf, "%d %s", &num, w) == 2) {
        // Increment counter
        count++;
        // If the number of chars is greater than expected, exit
        if (num > WORD_MAX || count > NUM_WORDS_MAX) {
            fprintf(stderr, INVAL_WORD_FILE);
            freeWordList(list);
            exit(EXIT_FAILURE);
        }
        // Resize if needed
        if (list->len == list->capacity - 1) {
            list->capacity *= 2;
            list->words = (Word *)realloc(list->words,
                                          list->capacity * sizeof(Word));
        }
        // Assign to rear
        strncpy(list->words[list->len], w, num);
        (list->len)++;
    }
    
    // Sort the list
    // void *base, size num items, size in bytes of each element, cmpr
    qsort(list->words, list->len, sizeof(Word), compareWords);
    
    /**
    for (int i = 0; i < list->len; i++) {
        printf("\'%s\'\n", list->words[i]);
    }
    */
    
    // Return the pointer to WordList
    return list;
}

/**
 * Returns the best code for the sequence of chars.
 *
 * @param wordList A pointer to the wordlist
 * @param str The sequence of characters being searched for
 * @return The code
 */
int bestCode( WordList *wordList, char const *str )
{
    // Char to hold the string being searched for
    char keyStr[WORD_MAX + 1];
    
    // Search while not matched
    Word *key = NULL;
    
    for (int i = WORD_MAX; i > 0; i--) {
        // Check the next string
        strncpy(keyStr, str, i);
        keyStr[i] = '\0';
        
        // Try to get the key
        key = (Word *)bsearch(keyStr, wordList->words, wordList->len,
                              sizeof(Word), compareWords);
        // printf("The key is: %lu\n", (key - wordList->words) / sizeof(Word));
        
        if (key != NULL) {
            // Return the index of the string
            return (key - wordList->words); // / sizeof(Word);
        }
    }
    
    // otherwise, return -1
    return -1;
}

/**
 * Frees the WordList
 *
 * @param wordList The wordlist being freed
 */
void freeWordList( WordList *wordList )
{
    // Free the words array
    free(wordList->words);
    // Free the WordList
    free(wordList);
}
