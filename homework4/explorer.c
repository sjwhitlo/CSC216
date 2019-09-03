/**
 @file explorer.c
 @author Sam Whitlock (sjwhitlo)
 
 The main file for the program. Takes user input, or a file containing
 commands and explores a map.
 */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** Used to make the player turn left. */
#define TURN_LEFT 3
/** The number of directions the player can face. */
#define DIRECTIONS 4
/** String for command to turn left. */
#define LEFT "left"
/** String for command to turn right. */
#define RIGHT "right"
/** String for command to go forward. */
#define FORWARD "forward"
/** String for command to quit. */
#define QUIT "quit"
/** Integer direction for north. */
#define NORTH 0
/** Integer direction for east. */
#define EAST 1
/** Integer direction for south. */
#define SOUTH 2
/** Integer direction for west. */
#define WEST 3
/** The error message for being blocked. */
#define BLOCKED "Blocked"
/** The error message for an inconsistent map. */
#define INCONSISTENT "Inconsistent map"
/** The error for usage commands from the command line. */
#define USAGE "usage: explorer [script_file]"
/** The error for invalid commands from the command line. */
#define INVALID "Invalid command"
/** The number of characters acceptable for the command parameter. */
#define INDIR 9
/** The number of characters for what the character sees. */
#define CHARTOKENS 5
/** The number of characters that the player should see. */
#define SEESLEN 3

/**
 Prints an error message based on the string passed as a parameter and
 terminates the program with unsuccessful exit status.
 
 @param message[] The error message to be printed.
 */
void error(char message[])
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

/**
 Moves the player on the map. Valid commandsd are "forward", "left", and "right".
 If not one of those commands, an error is displayed for  an invalid command, and
 terminates unsuccessfully. If there is a '#' in front of the character,
 then an error message is displayed notifying the player that their way is
 blocked. Then the program terminates unsuccessfully.
 
 @param **map A pointer to the map that the player is exploring.
 @param *rowPos A pointer to the position of the player in the map.
 @param *colPos A pointer to the position of the player in the map.
 @param *s A pointer to the command for what the player is going to do.
 @param *dir A pointer to the direction that the player is facing.
 */
void move(char **map, int *rowPos, int *colPos, const char *s, int *dir)
{
    if (strcmp(s, LEFT) == 0) {
        *dir += TURN_LEFT;
        *dir %= DIRECTIONS;
    } else if (strcmp(s, RIGHT) == 0) {
        (*dir)++;
        *dir %= DIRECTIONS;
    } else if (strcmp(s, FORWARD) == 0) {
        if (*dir == NORTH) {
            if (map[*rowPos - 1][*colPos] == '#') {
                error(BLOCKED);
            } else {
                (*rowPos)--;
            }
        } else if (*dir == EAST) {
            if (map[*rowPos][*colPos + 1] == '#') {
                error(BLOCKED);
            } else {
                (*colPos)++;
            }
        } else if (*dir == SOUTH) {
            if (map[*rowPos + 1][*colPos] == '#') {
                error(BLOCKED);
            } else {
                (*rowPos)++;
            }
        } else if (*dir == WEST) {
            if (map[*rowPos][*colPos - 1] == '#') {
                error(BLOCKED);
            } else {
                (*colPos)--;
            }
        }
    } else {
        error(INVALID);
    }
}

/**
 Writes the map and the displays the player's current position and direction. An error is
 displayed if the map is inconsistent and the program terminates unsuccessfully.
 
 @param **map A pointer to the map.
 @param rows The number of rows in the map.
 @param rowPos The row position of the player.
 @param colPos The column position of the player.
 @param dir The direction that the player is facing.
 @param *tokens A pointer to the characters that the player sees.
 */
void writeMap( char **map, int rows, int rowPos, int colPos, int dir, char *tokens)
{
    // When map expands, the location of the player has to change based on the expand
    if (dir == NORTH) {
        int row = rowPos - 1;
        int col = colPos - 1;
        // Write to positions above the player from left to right
        for (int i = 0; tokens[i]; i++) {
            if (map[row][col + i] == ' ' || map[row][col + i] == tokens[i]) {
                map[row][col + i] = tokens[i];
            } else {
                error(INCONSISTENT);
            }
        }
    } else if (dir == EAST) {
        int row = rowPos - 1;
        int col = colPos + 1;
        // Write to positions to the right of the player from top to bottom
        for (int i = 0; tokens[i]; i++) {
            if (map[row + i][col] == ' ' || map[row + i][col] == tokens[i]) {
                map[row + i][col] = tokens[i];
            } else {
                error(INCONSISTENT);
            }
        }
    } else if (dir == SOUTH) {
        int row = rowPos + 1;
        int col = colPos + 1;
        // Write to positions below the player from right to left
        for (int i = 0; tokens[i]; i++) {
            if (map[row][col - i] == ' ' || map[row][col - i] == tokens[i]) {
                map[row][col - i] = tokens[i];
            } else {
                error(INCONSISTENT);
            }
        }
    } else {
        int row = rowPos + 1;
        int col = colPos - 1;
        // Write to positions to the left of the player from bottom to top
        for (int i = 0; tokens[i]; i++) {
            if (map[row - i][col] == ' ' || map[row - i][col] == tokens[i]) {
                map[row - i][col] = tokens[i];
            } else {
                error(INCONSISTENT);
            }
        }
    }
}

/**
 The main function of the program. The program starts here. It can read input from a file
 or from standard input. If the command line arguments are incorrect, a usage message is
 displayed, and the program terminated unsuccessfully. If the program cannot open a file,
 it is terminated unsuccessfully as well.
 
 A player explores a map.
 
 @param argc The number of command line arguments.
 @param *argv[] A pointer the the command line argument.
 */
int main(int argc, char *argv[])
{
    // Declare all variables
    int rows;
    char **map = initMap(&rows);
    int rowPos = 1;
    int colPos = 1;
    int dir = 0;
    char inDir[INDIR];
    char sees[CHARTOKENS];
    FILE *input = NULL;
    
    // If argc == 2, set the input file to argv[1]
    // If argv[1] is invalid, print error message
    // If argc == 1, set the input to stdin
    if (argc == 1) {
        input = stdin;
    } else if (argc == 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Can't open movement script: %s\n", argv[1]);
            error(USAGE);
        }
    } else {
        error(USAGE);
    }
    
    // Get first input - matches %c%c%c
    fscanf(input, "%3s", sees);
    // Write map
    writeMap(map, rows, rowPos, colPos, dir, sees);
    
    // Show the map
    showMap(map, rows, rowPos, colPos, dir);
    
    // Read input
    while (fscanf(input, "%8s", inDir) == 1) {
        if (strcmp(inDir, QUIT) == 0) {
            break;
        }
        if (fscanf(input, "%4s", sees) == 1) {
            // Move
            move(map, &rowPos, &colPos, inDir, &dir);
            // If position is on an edge, expand map
            // If on top edge, add row to top
            if (rowPos == 0) {
                map = expandMap(map, &rows, 1, 0, 1, 0);
                // Increment player position
                rowPos++;
            }
            // If on right edge, add column to end
            if (colPos == (strlen(map[0]) - 1)) {
                map = expandMap(map, &rows, 0, 1, 0, 0);
            }
            // If on bottom edge, add row at end
            if (rowPos == (rows - 1)) {
                map = expandMap(map, &rows, 1, 0, 0, 0);
            }
            // If on left edge, add column to front
            if (colPos == 0) {
                map = expandMap(map, &rows, 0, 1, 0, 1);
                // Increment player position
                colPos++;
            }
            if (strlen(sees) != SEESLEN) {
                error(INVALID);
            }
            // Write map
            writeMap(map, rows, rowPos, colPos, dir, sees);
            // Show map
            showMap(map, rows, rowPos, colPos, dir);
        }
    }
    
    // Free the map
    freeMap(map, rows);
    
    // Return Exit success
    return 0;
}
