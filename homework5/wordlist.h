/**
 * @file wordlist.h
 * @author Sam Whitlock (sjwhitlo)
 *
 * Header file for wordlist.c. Includes functions pertaining to the
 * WordList.
 */

#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#include <stdbool.h>

/** Maximum length of a word in wordlist. */
#define WORD_MAX 20

/**
 * Compares two words lexicographically , and returns negative if
 * the first comes first, 0 if the same, and positive if the first
 * comes after the second.
 *
 * @param a A pointer to the first word
 * @param b A pointer to the second word
 * @return neg if a < b, 0 if equal, else pos
 */
int compareWords(const void *a, const void *b);

/**
 * Returns true if the char is valid
 *
 * @param ch The char being checked
 * @return true if the char is valid
 */
bool validChar( char ch );

/** Word type, used to store elements of the word list,
    with room for a word of up to 20 characters. */
typedef char Word[ WORD_MAX + 1 ];

/** Representation for the whole wordlist.  It contains
    the list of words as a resizable, dynamically allocated
    array, along with supporting fields for resizing. */
typedef struct {
  /** Number of words in the wordlist. */
  int len;

  /** Capacity of the wordlist, so we can know when we need to resize. */
  int capacity;

  /** List of words.  Should be sorted lexicographically once the word list
      has been read in. */
  Word *words;
} WordList;

/**
 * Adds the given char to the given wordList.
 *
 * @param list A pointer to the WordList
 * @param ch The char to be added
 */
void addChar(WordList *list, unsigned char ch);

/**
 * Builds the WordList from one pointer to a string.
 *
 * @param fname a pointer to the string
 * @return The WordList
 */
WordList *readWordList( char const *fname );

/**
 * Returns the best code for the sequence of chars.
 *
 * @param wordList A pointer to the wordlist
 * @param str The sequence of characters being searched for
 * @return The code
 */
int bestCode( WordList *wordList, char const *str );

/**
 * Frees the WordList
 *
 * @param wordList The wordlist being freed
 */
void freeWordList( WordList *wordList );

#endif
