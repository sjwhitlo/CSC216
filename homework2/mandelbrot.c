/**
 @file mandelbrot.c
 @author Sam Whitlock (sjwhitlo)
 The program prints out a reprsention of Mandelbrot based on user specified values.
 */

#include <stdio.h>
#include <stdlib.h>

/** Dwell cut-off for drawing with ' ' */
#define LEVEL_1 10

/** Dwell cut-off for drawing with '.' */
#define LEVEL_2 20

/** Dwell cut-off for drawing with ':' */
#define LEVEL_3 30

/** Dwell cut-off for drawing with '-' */
#define LEVEL_4 40

/** Dwell cut-off for drawing with '=' */
#define LEVEL_5 50

/** Dwell cut-off for drawing with '+' */
#define LEVEL_6 60

/** Dwell cut-off for drawing with '*' */
#define LEVEL_7 70

/** Dwell cut-off for drawing with '#' */
#define LEVEL_8 80

/** Dwell cut-off for drawing with '%' */
#define LEVEL_9 90

/** Defines the height of the picture. */
#define HEIGHT 35
/** Defines the width of the picture. */
#define WIDTH 70

/**
 Calculates the dwell for the current point.
 @param cReal The real value to calculate the dwell for.
 @param cImag The imaginary value to calculate the dwell for.
 @return The dwell.
 */
int testPoint( double cReal, double cImag )
{
    // Copy parameters
    double zReal = cReal;
    double zImag = cImag;
    // Initialize dwell
    int dwell = 0;
    
    // Compute the dwell
    while (dwell < LEVEL_9 ) {
        // z = z^2 + c
        double xReal = (zReal * zReal) - (zImag * zImag) + cReal;
        double xImag = 2 * zReal * zImag + cImag;
        zReal = xReal;
        zImag = xImag;
        // If the magnitude of z > 2, break
        if ( ((zReal * zReal) + (zImag * zImag)) > (2 * 2)) {
            break;
        }
        // Increment dwell
        dwell++;
    }
    
    // Return the dwell
    return dwell;
}

/**
 Takes the int passed as a parameter and returns the char associated with that dwell value.
 @param dwell The dwell value.
 @return The char value associated with the dwell value.
 */
char dwellSymbol( int dwell )
{
    if (dwell < LEVEL_1) {
        return ' ';
    } else if (dwell < LEVEL_2) {
        return '.';
    } else if (dwell < LEVEL_3) {
        return ':';
    } else if (dwell < LEVEL_4) {
        return '-';
    } else if (dwell < LEVEL_5) {
        return '=';
    } else if (dwell < LEVEL_6) {
        return '+';
    } else if (dwell < LEVEL_7) {
        return '*';
    } else if (dwell < LEVEL_8) {
        return '#';
    } else if (dwell < LEVEL_9) {
        return '%';
    } else {
        return '@';
    }
}

/**
 Draws the figure based on character input.
 @param minReal The minimum real value that can be calculated.
 @param minImag The minimum real value that can be calculated.
 @param size The size above the bounds of the min values.
 */
void drawFigure( double minReal, double minImag, double size )
{
    long double imagIncrement = (size / (double) (HEIGHT - 1));
    long double realIncrement = (size / (double) (WIDTH - 1));
    
    // Loop through the box
    for (long double y = minImag + size; y >= minImag - imagIncrement/2; y -= imagIncrement) {
        for (long double x = minReal; x <= minReal + size + realIncrement/2; x += realIncrement) {
            putchar(dwellSymbol(testPoint(x, y)));
        }
        putchar('\n');
    }
}

/**
 Validates if the entered value is an acceptable input. Program terminates if the
 input is invalid.
 @param matches 1 if the value matches.
 */
void validateInput(int matches)
{
    if (matches == 1) {
        return;
    } else if (matches == 0) {
        printf("Invalid input\n");
    }
    // If it gets here, input unexpected. Terminate program.
    exit(EXIT_FAILURE);
}

/**
 The main function in the program. It takes values for minReal, minImag, and size,
 and displays a represention of the Mandelbrot figure for those values.
 @return EXIT_SUCCESS for successful termination
 */
int main()
{
    // Declare variables
    double minReal;
    double minImag;
    double size;
    
    // Get user input
    printf("Minimum real: ");
    int matches = scanf("%lf", &minReal);
    validateInput(matches);
    
    printf("Minimum imaginary: ");
    matches = scanf("%lf", &minImag);
    validateInput(matches);
    
    printf("Size: ");
    matches = scanf("%lf", &size);
    validateInput(matches);
    
    // Call drawFigure
    drawFigure(minReal, minImag, size);
    
    // return EXIT_SUCCESS
    return EXIT_SUCCESS;
}
