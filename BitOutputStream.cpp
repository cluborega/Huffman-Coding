/*
 *
 * File: BitOutputStream.cpp
 * Date: 04/20/2016
 * Description: Our own way of writing bits to a file.
 * into the byte.
 */

#include <iostream>
#include "BitOutputStream.hpp"
using namespace std;

  /** Send the buffer to the output, and clear it */
  void BitOutputStream::flush() {
    out.put (buf);
    out.flush ();
    buf = nbits = 0;
  }

  /** Write the least significant bit of the argument to
    * the bit buffer, and increment the bit buffer index.
    * But flush the buffer first, if it is full.
    */
  void BitOutputStream::writeBit(int i) {
    if (nbits == 8) flush();
    buf = buf|(i<<(7-nbits));
    nbits++;
  }
