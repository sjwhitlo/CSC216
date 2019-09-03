/**
 @file map.c
 @author Sam Whitlock (sjwhitlo)
 
 File containing map functions.
 */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** The initial map size. */
#define INITIAL_MAP_SIZE 3
/** Integer direction for north. */
#define NORTH 0
/** Integer direction for east. */
#define EAST 1
/** Integer direction for south. */
#define SOUTH 2
/** Integer direction for west. */
#define WEST 3
/** The char for the character facing north. */
#define NCHAR '^'
/** The char for the character facing east. */
#define ECHAR '>'
/** The char for the character facing south. */
#define SCHAR 'V'
/** The char for the character facing west. */
#define WCHAR '<'

/**
 Initializes the map with the the initial size and returns a pointer
 to the map.
 
 @param *rows A pointer to the number of rows in the map.
 @return A pointer to the map.
 */
char **initMap( int *rows ) {
    // Allocate enough space to store a pointer for every row.
    *rows = INITIAL_MAP_SIZE;
    char **map = (char **) malloc( *rows * sizeof( char * ) );
    
    // Fill in the rows with 3-character strings of spaces.
    for ( int i = 0; i < *rows; i++ ) {
        map[ i ] = (char *)malloc( INITIAL_MAP_SIZE + 1 );
        strcpy( map[ i ], "   " );
    }
    
    // Return the new map.
    return map;
}

/**
 Frees the map passed in as a parameter.
 
 @param **map A pointer to the map being freed.
 @param rows The number of rows in the map.
 */
void freeMap( char **map, int rows )
{
    for ( int i = 0; i < rows; i++ ) {
        free(map[ i ]);
    }
    
    free(map);
}

/**
 Prints out the map.
 
 @param **map A pointer to the map.
 @param rows The number of rows in the map.
 @param rowPos The row position of the player.
 @param colPos The column position of the player.
 @param dir The direction that the player is facing.
 */
void showMap( char **map, int rows, int rowPos, int colPos, int dir )
{
    // Calculate length of rows using strlen
    int len = strlen(map[0]);
    
    char player;
    if (dir == NORTH) {
        player = NCHAR;
    } else if (dir == EAST) {
        player = ECHAR;
    } else if (dir == SOUTH) {
        player = SCHAR;
    } else if (dir == WEST) {
        player = WCHAR;
    }
    
    // Print top border
    printf("+");
    for (int i = 0; i < len; i++) {
        printf("-");
    }
    printf("+\n");
    
    // Print map plus bounding border
    for (int i = 0; i < rows; i++) {
        // If this is the row that the player is on.
        // printf("Row %d\n|%s|\n", i + 1, map[i]);
        if (i == rowPos) {
            printf("|");
            for (int j = 0; j < len; j++) {
                printf("%c", (j == colPos) ? player : map[i][j]);
            }
            printf("|\n");
        } else{
            printf("|%s|\n", map[i]);
        }
    }
    
    // Print bottom border
    printf("+");
    for (int i = 0; i < len; i++) {
        printf("-");
    }
    printf("+\n");
}

/**
 Expands the map by allocating memory for a new one, copying the old map
 into the new one and freeing the memory of the old. The new map is
 expanded and shifted by the parameters passed into the function.
 Returns a pointer to the new map.
 
 @param **map A pointer to the map to be expanded.
 @param *rows A pointer to the number of rows in the map.
 @param extraRows The number of extra rows to be added to the map.
 @param extraCols The number of extra columns to be added to the map.
 @param shiftRows The number of rows to shift the map by.
 @param shiftCols The number of columns to shift the map by.
 @return A pointer to the new map.
 */
char **expandMap( char **map, int *rows, int extraRows,
                 int extraCols, int shiftRows, int shiftCols )
{
    // Update the rows
    int oldRows = *rows;
    *rows += extraRows;
    
    // Make new map of specified rows
    char **newMap = (char **) malloc( *rows * sizeof( char * ) );
    
    // Make a string to fill the rows with
    int oldCols = strlen(map[0]);
    int cols = oldCols + extraCols;
    char spaces[cols];
    for (int i = 0; i < cols; i++) {
        spaces[i] = ' ';
    }
    spaces[cols] = '\0';
    
    // Malloc columns and fill with spaces
    for ( int i = 0; i < *rows; i++ ) {
        newMap[i] = (char *)malloc(cols + 1);
        strcpy(newMap[i], spaces);
    }
    
    // Copy old map to newMap
    for (int i = 0; i < oldRows; i++) {
        // strcpy(newMap[i + shiftRows], map[i]);
        for (int j = 0; j < oldCols; j++) {
            newMap[shiftRows + i][shiftCols + j] = map[i][j];
        }
    }
    
    // Free old map
    freeMap(map, oldRows);
    
    return newMap;
}
