/**
 @file image.h
 @author Sam Whitlock (sjwhitlo)
 
 The header file for image.c
 */

#include <stdio.h>

/** Lets the other functions know that there is an int variable, HEIGHT. */
extern int HEIGHT;
/** Lets the other functions know that there is an int variable, WIDTH. */
extern int WIDTH;

/**
 Fills an image with the given color.
 
 @param image[][] The array of char values describing the color of the image.
 @param color The color to fill the image.
 */
void clearImage( unsigned char image[ WIDTH ][ HEIGHT ], unsigned char color );

/**
 Saves the image.
 
 @param image[][] The char array to save as an image.
 @param *outputfile A pointer to the output file.
 */
void saveImage( unsigned char image[ WIDTH ][ HEIGHT ], FILE *outputFile );

/**
 Draws a line. Calculates slope, and models the line arbitrarilly.
 
 @param image[][] The array of char values describing the image.
 @param x1 X value for point 1.
 @param y1 Y value for point 1.
 @param x2 X value for point 2.
 @param y2 Y value for point 2.
 @param color The color of the line.
 */
void drawLine( unsigned char image[ WIDTH ][ HEIGHT ], int x1, int y1, int x2, int y2, unsigned char color );

/**
 Draws a circle.
 
 @param image[][] The array of char values describing the image.
 @param cx X value center of circle.
 @param cy Y value center of circle.
 @param radius Radius of the circle.
 @param color The color of the circle.
 */
void drawCircle( unsigned char image[ WIDTH ][ HEIGHT ], int cx, int cy, int radius, unsigned char color );