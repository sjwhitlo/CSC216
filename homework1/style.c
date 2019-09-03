/*
 @file style.c
 @author Sam Whitlock (sjwhitlo)
 
 Prints characters a-z on seperate lines, and one multiple of 7 for every multiple of 10 less than 100.
 */

#include <stdio.h>

/*
 Prints lowercase characters a-z on seperate lines.
 */
void sleepy()
{
	for ( char c = 'a'; c <= 'z'; c++ ) {
		printf( "%c", c );
	}
	printf( "\n" );
}

/*
 Returns the next lowest multiple of 7.
 @param x the int to start the search for the next multiple of 7 from.
 @return The next lowest multiple of 7.
 */
int grumpy( int x )
{
    while ( x % 7 != 0 ) {
        x++;
    }
    return x;
}

/* 
 Prints one multiple of 7 for every multiple of 10 less than 100.
 */
void dopey()
{
    for ( int i = 1; i < 100; i += 10 ) {
        int x = grumpy( i );
        printf( "%d\n", x );
    }
}

/*
 Program starting point. Prints characters a-z on seperate lines, and one multiple of 7 for every multiple of 10 less than 100.
 @return Exit status of the program.
 */
int main()
{
    sleepy();
    dopey();
    return 0;
}
