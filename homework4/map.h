/**
 @file map.h
 @author Sam Whitlock (sjwhitlo)
 
 This is the header file for map.c. It defines the functions used in the file.
 */

/**
 Initializes the map with the the initial size and returns a pointer
 to the map.
 
 @param *rows A pointer to the number of rows in the map.
 @return A pointer to the map.
 */
char **initMap( int *rows );

/**
 Frees the map passed in as a parameter.
 
 @param **map A pointer to the map being freed.
 @param rows The number of rows in the map.
 */
void freeMap( char **map, int rows );

/**
 Prints out the map.
 
 @param **map A pointer to the map.
 @param rows The number of rows in the map.
 @param rowPos The row position of the player.
 @param colPos The column position of the player.
 @param dir The direction that the player is facing.
 */
void showMap( char **map, int rows, int rowPos, int colPos, int dir );

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
                 int extraCols, int shiftRows, int shiftCols );
