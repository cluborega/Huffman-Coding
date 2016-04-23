#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    char buf;       //one byte buffer of bits
    int nbits;      //how many bits have benn read from buf
    istream& in;    //the input stream to use

public:
    BitInputStream(istream& s) : in(s) {
      buf= 0;   //clear buffer
      nbits =8; //initialize bit index
    }
    
    /** Fill the buffer from the input */
    void fill();
    /** Read the next bit from the bit buffer.
      * Fill the buffer from the input stream first if needed.
      * Return 1 if the bit read is 1;
      * Return 0 if the bit read is 0;
      */
    int readBit();

};
#endif
