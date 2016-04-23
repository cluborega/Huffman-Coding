

#include <iostream>
#include "BitInputStream.hpp"
using namespace std;

/** Fill the buffer from the input */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}
/** Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed.
  * Return 1 if the bit read is 1;
  * Return 0 if the bit read is 0;
  */
int BitInputStream::readBit() {
  //if all bits in the buffer are read, fill the buffer first
  if (nbits > 7) fill();

  //get the bit at appropriate location in the bit
  //buffer, and return the appropriate int
  int i = 1 & (buf>>(7-nbits));
  nbits++; //increment the index
  return i;
}

