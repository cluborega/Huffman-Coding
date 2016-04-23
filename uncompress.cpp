/*
 * File: uncompress.cpp
 * Date: 04/18/2016
 * Description: Program to uncompress the input file.
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include "HCTree.hpp"

using namespace std;

static const char USAGE[] = "./uncompress called with incorrect arguments.\n Usage: ./uncompress infile outfile";

  int main (int argc, char *argv[]) {
    if(argc != 3) {
      cerr << USAGE << endl;
      return -1;
    }

    if(argv[1] == argv[2]){
      cerr << "Inputfile and outfile cannot have the same name";
      return -1;
    }

    ifstream infile;
    ofstream outfile;

    infile.open ( argv[1], ios::binary );
    if(!infile.is_open ()) {
      cerr<< "Error opening the input file." << endl;
      return -1;
    }

    vector<int> freqs( 256, 0 );
    size_t filesize = 0;
    size_t infilesize = 0;
    unsigned int numsymbols  = 0;
    int nextchar;
    
    //to calculate the size of infile
    infile.clear();
    while (1) {      
      infile.get();
      if (infile.eof()) break;
      infilesize++;   //num of bytes in the file
    }
    infile.clear();
    infile.close();

    //reopen infile to start uncompression process
    infile.open ( argv[1], ios::binary );
    printf("Reading header from file \"%s\"... ", argv[1]);
    for (size_t i = 0; i < freqs.size(); ++i) {
      infile >> nextchar;
      infile.get();
      if (nextchar != 0) {
        freqs[i] = nextchar;
        numsymbols++;
      }
      filesize += freqs[i];
    }
    cout << "done." <<endl;
    printf("Uncompressed file will have %d unique symbols and size %lu bytes.\n",
                                                          numsymbols, filesize);
    printf("Building Huffman code tree... ");
    HCTree hctree;
    if (filesize != 0) hctree.build ( freqs );
    cout << "done." << endl;
    BitInputStream bitin = BitInputStream (infile);
    outfile.open( argv[2], ios::binary );
    if (!outfile.is_open()){
      cerr<<"Error opening the output file"<<endl;
      return -1;
    }
    printf("Writing to file \"%s\"... ", argv[2]);
    
    // decode and write to the outfile
    int b;
    for( int i = 0; i < filesize; ++i ) {
      b = hctree.decode(bitin);
      outfile << (char) b;
    }
    cout << "done." <<endl;
    
    //int infile_size = infile.tellp();
    float ratio = (float)filesize/ (float)infilesize;
    printf("Uncompression ratio: %f\n",ratio);
    outfile.flush();
    infile.close();
    outfile.close();
    return 0;
  } //end main

