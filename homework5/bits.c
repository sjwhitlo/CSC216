/**
 * @file bits.c
 * @author Sam Whitlock (sjwhitlo)
 *
 * Performs bit operations to read and write codes from files.
 */

#include <stdio.h>

#include "bits.h"

/** Ints for an array of masks. */
#define MASKS 0x000, 0x001, 0x003, 0x007, 0x00f, 0x01f, 0x03f, 0x07f, 0x0ff
/** Seven = 7. */
#define SEVEN 7

/** Write the 9 low-order bits from code to the given file.
 @param code bits to write out, a value betteen 0 and 2^9 - 1.
 @param pending pointer to storage for unwritten bits left over
 from the previous call to writeCode().  After this call, any bits
 that partially fill the next byte will be left in the pending
 struct, to be written in the next call.
 @param fp file we're writing to, opened for writing.
 */
void writeCode( int code, PendingBits *pending, FILE *fp )
{
    // Left shift code by bit count
    code = code << pending->bitCount;
    // Add pending's bits to the low order bits of code
    code |= pending->bits;
    // Mask and write low order 8 bits to file
    unsigned char toWrite = code & 0xFF;
    fputc(toWrite, fp);
    // Right shift by 8 bits
    code = code >> BITS_PER_BYTE;
    // Update bits and bitCount
    pending->bits = code & 0xFF;
    // pending->bitCount = BITS_PER_CODE - pending->bitCount;
    pending->bitCount = (pending->bitCount + 1) % BITS_PER_BYTE;
    
    // If there are 8 bits in pending, write them to file
    // And set bits and bitCount to 0.
    if (pending->bitCount == 0) {
        // Write
        fputc(pending->bits, fp);
        // Clear everything
        pending->bits = 0;
        pending->bitCount = 0;
    }
}

/** If there are any bits buffered in pending, write them out to the
 given file in the low-order bit positions of a byte, leaving zeros
 in the high-order bits.
 @param pending pointer to storage for unwritten bits left over
 from the most recent call to writeCode().
 @param fp file these bits are to be written to, opened for writing.
 */
void flushBits( PendingBits *pending, FILE *fp )
{
    if (pending->bitCount > 0) {
        unsigned char toWrite = 0x00;
        toWrite |= pending->bits;
        // Write
        fputc(toWrite, fp);
        // Clear everything
        pending->bits = 0;
        pending->bitCount = 0;
    }
}

/** Read and return the next 9-bit code from the given file.
 @param pending pointer to storage for left-over bits read during
 the last call to readCode().
 @param fp file bits are being read from, opened for reading.
 @return value of the 9-bit code read in, or -1 if we reach the
 end-of-file before getting 9 bits.
 */
int readCode( PendingBits *pending, FILE *fp )
{
    // Define the masks
    int mask[] = {MASKS};
    // Temp storage for bits
    char tmpBits;
    // If there are 0 pending bits, read the next byte to pending
    // Set pending bits to 8
    if (pending->bitCount == 0) {
        if ((tmpBits = fgetc(fp)) == EOF) {
            // return -1 if no next byte
            return -1;
        }
        // Set the bits to what was read in
        pending->bits = tmpBits;
        pending->bitCount = BITS_PER_BYTE;
    }
    
    // The number of bits to read from the next byte
    int toRead = BITS_PER_CODE - pending->bitCount;
    // set code to bits
    int code = pending->bits;
    // Read next byte into pending - DO NOT CHANGE BITCOUNT
    // If no next byte, return -1
    if ((tmpBits = fgetc(fp)) == EOF) {
        // return -1 if no next byte
        return -1;
    }
    // Set the bits to what was read in
    pending->bits = tmpBits;
    // Temporarily mask the low order bits left to read
    int tmp = pending->bits;
    // Mask tmp
    tmp &= mask[BITS_PER_CODE - pending->bitCount];
    tmp = tmp << pending->bitCount;
    // Add the two parts together
    code += tmp;
    // right shift bits by the number just read
    pending->bits = pending->bits >> toRead;
    // update bit count (bitCount + 7) % BITS_PER_BYTE
    pending->bitCount = (pending->bitCount + SEVEN) % BITS_PER_BYTE;
    // Return the int
    return code;
}
