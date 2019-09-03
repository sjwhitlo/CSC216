/**
 @file comments.c
 @author Sam Whitlock (sjwhitlo)
 The program prints out the number of total characters, comments, and
 the percentage of comment characters in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/** Exit status for an empty file. */
#define EMPTY_INPUT 100
/** Exit status for acomment that is not terminated. */
#define COMMENT_NOT_TERMINATED 101

/** Total count of characters. */
int totalChars = 0;

/** Total count of characters that are part of a comment. */
int commentChars = 0;

/** Total number of comments in the input. */
int commentCount = 0;

/**
 Processes the comments increments char counts.
 Exits the program if a comment is unterminated.
 */
void processComment()
{
    // While more chars:
    int ch;
    bool star = false;
    // getChar() to read input
    while ( (ch = getchar()) != EOF) {
        // while there's a next charachter:
        // TODO some code
        // Increment totalChars
        totalChars++;
        commentChars++;
        // if matches "/*"
        if (star) {
            if (ch == '/') {
                return;
            }
            star = false;
        } else if (ch == '*') {
            star = true;
        } else {
            star = false;
        }
        
    }
    // Look for "*/"
    // if found, return null
    // else increment totalChars and commentChars
    
    // end while
    
    // If the comment is not terminated at end of file:
    printf("Unterminated comment\n");
    exit(COMMENT_NOT_TERMINATED);
}

/**
 The main function. Counts the characters, and calls the processComment method.
 @return EXIT_SUCCESS if the program executes successfully, and EMPTY_INPUT otherwise.
 */
int main()
{
    int ch;
    bool slash = false;
    // getChar() to read input
    while ( (ch = getchar()) != EOF) {
        // while there's a next charachter:
        // TODO some code
        // Increment totalChars
        totalChars++;
        // if matches "/*"
        if (slash) {
            if (ch == '*') {
                commentCount++;
                commentChars += 2;
                processComment();
            }
            slash = false;
        } else if (ch == '/') {
            slash = true;
        } else {
            slash = false;
        }
        
    }
    
    // Empty input
    if (totalChars == 0) {
        printf("Empty input\n");
        return EMPTY_INPUT;
    } else {
        printf("Input characters: %d\n", totalChars);
        printf("Comments: %d (%.2f%%)\n", commentCount, (100 * commentChars)/(double) totalChars);
        return EXIT_SUCCESS;
    }
}