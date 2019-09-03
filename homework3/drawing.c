/**
 @file drawing.c
 @author Sam Whitlock (sjwhitlo)
 
 The main functions used to read and draw images. Takes two command
 line arguments. Prints error messages to stderr if not used properly.
 */

#include "image.h"
#include <stdio.h>
#include <stdlib.h>

/** The expected number of command line args, including command to run the file. */
#define EXPECTED_ARGS 3
/** The number to represent white. */
#define WHITE 255
/** The number to represent black. */
#define BLACK 0
/** An invalid script string. */
#define INVALID "Invalid script file"
/** A usage message. */
#define USAGE "usage: drawing <script_file> <image_file>"

/**
 Prints an error message with the string passed to the funciton, and terminates the
 program with an unsuccessful status.
 
 @param message[] the string passed into the method
 */
void printError(char message[])
{
    // Print to stderr
    fprintf(stderr, "%s\n", message);
    
    // Terminate with unsuccessful exit status
    exit(EXIT_FAILURE);
}

/**
 Parses the input file, and calls the appropriate function to draw the images described.
 Prints an error if the file does not match the expected format.
 
 @param image[][] The 2D image array
 @param *input The pointer to tht input file
 @sideeffect If the input is not valid, the program terminates with an unsuccessful status
 */
void parse(unsigned char image[ WIDTH ][ HEIGHT ], FILE *input)
{
    // Parameters to pass to functions
    int val1, val2, val3, val4, val5;
    char type = 'p';
    
    // Begin parsing
    // Scan letter at beginning ('l' or 'c')
    while (fscanf(input, " %c", &type) == 1) {
        // Scan appropriate number of digits
        if (type == 'c') {  // Scan Circle
            if (fscanf(input, "%d%d%d%d", &val1, &val2, &val3, &val4) == 4) {
                // If the color value is out of range, print error
                if (val4 < BLACK || val4 > WHITE) {
                    printError(INVALID);
                }
                drawCircle(image, val1, val2, val3, val4);
            } else {
                printError(INVALID);
            }
        } else if (type == 'l') {  // Scan Line
            if (fscanf(input, "%d%d%d%d%d", &val1, &val2, &val3, &val4, &val5) == 5) {
                // If the color value is out of range, print error
                if (val5 < BLACK || val5 > WHITE) {
                    printError(INVALID);
                }
                drawLine(image, val1, val2, val3, val4, val5);
            } else {
                printError(INVALID);
            }
        } else {
            printError(INVALID);
        }
    }
}

/**
 Structure of the program. Handles the inputs, and calls the appropriate functions.
 Improper files are handled with error messages, and program termination.
 
 @param argc The number of arguments passed into the function
 @param *argv[] A pointer to the array of arguments passed into the program
 @return Exit success if the program terminates successfully.
 */
int main(int argc, char *argv[])
{
    // Create an "image" to pass to functions
    unsigned char image[ WIDTH ][ HEIGHT ];
    
    // Check number of arguments. If not 2 parameters, exit.
    if (argc != EXPECTED_ARGS) {
        printError(USAGE);
    }
    
    // Attempt to read files. If unable to read, program terminates
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Can't open file: %s\n", argv[1]);
        printError(USAGE);
    }
    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fprintf(stderr, "Can't open file: %s\n", argv[2]);
        printError(USAGE);
    }
    
    // Clear the image with color white (255)
    clearImage(image, WHITE);
    
    // Parse the image
    parse(image, input);
    
    // Save image
    saveImage(image, output);
    
    // Close files
    fclose(input);
    fclose(output);
    
    // Exit success! :)
    return EXIT_SUCCESS;
}