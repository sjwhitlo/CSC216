/**
 @file image.c
 @author Sam Whitlock (sjwhitlo)
 
 Handles all of the drawing functions of the program.
 */

#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** The height of the image. */
int HEIGHT = 255;
/** The width of the image. */
int WIDTH = 255;

void clearImage( unsigned char image[ WIDTH ][ HEIGHT ], unsigned char color )
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            image[x][y] = color;
        }
    }
}

void saveImage( unsigned char image[ WIDTH ][ HEIGHT ], FILE *outputFile )
{
    fprintf(outputFile, "P2\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(outputFile, "%3d", (int) image[x][y]);
            if (x != (WIDTH - 1)) {
                fprintf(outputFile, " ");
            }
        }
        fprintf(outputFile, "\n");
    }
}

void drawLine( unsigned char image[ WIDTH ][ HEIGHT ], int x1, int y1, int x2, int y2, unsigned char color )
{
    // Calculate the size of the line
    int xlen = abs(x2 - x1);
    int ylen = abs(y2 - y1);
    
    // Short circuit out if slope is undef
    if (y1 == y2) {
        for (int x = x1; x != x2; x += ((x2 - x1) / xlen)) {
            if (x < WIDTH && y1 < HEIGHT && x >= 0 && y1 >= 0) {
                image[x][y1] = color;
            }
        }
        if (x2 < WIDTH && y1 < HEIGHT && x2 >= 0 && y1 >= 0) {
            image[x2][y1] = color;
        }
        // Short curcuit out
        return;
    } else if (x1 == x2) {
        for (int y = y1; y != y2; y += ((y2 - y1) / ylen)) {
            if (x1 < WIDTH && y < HEIGHT && x1 >= 0 && y >= 0) {
                image[x1][y] = color;
            }
        }
        if (x2 < WIDTH && y1 < HEIGHT && x2 >= 0 && y1 >= 0) {
            image[x2][y1] = color;
        }
        // Short curcuit out
        return;
    }
    
    // Calculate slope
    double slope = ((double) y2 - y1) / (x2 - x1);
    
    // Sample the line at uniformly spaced locations (linelength - 2)
    // lineLength - 2 because of the end points
    if (xlen > ylen) {
        // find max and min
        int xmin = (x1 < x2) ? x1 : x2;
        int xmax = (x1 > x2) ? x1 : x2;
        for (int x = xmin; x <= xmax; x++) {  // Check the conditional operator
            int y = round(slope * (x - x1) + y1);
            if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                image[x][y] = color;
            }
        }
    } else {
        // find max and min
        int ymin = (y1 < y2) ? y1 : y2;
        int ymax = (y1 > y2) ? y1 : y2;
        for (int y = ymin; y <= ymax; y++) {  // Check the conditional operator
            int x = round(((y - y1) / slope) + x1);
            if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                image[x][y] = color;
            }
        }
    }
}

void drawCircle( unsigned char image[ WIDTH ][ HEIGHT ], int cx, int cy, int radius, unsigned char color )
{
    // For the whole graph, calculate the distance to the center.
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Draw any pixel whose point is inside the radius the color assigned.
            if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius * radius) {
                image[x][y] = color;
            }
        }
    }
}