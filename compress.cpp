/* File: compress.cpp
 * Date: 04/18/2016
 * Description: Program to compress the input file.
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include "HCTree.hpp"

using namespace std;

static const char USAGE[] = "./compress called with incorrect arguments.\n Usage: ./compress infile outfile";

  int main (int argc, char *argv[]) {
    
    //print usage if wrong number of arguments
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

    infile.open(argv[1], ios::binary);

    if (!infile.is_open()) {
      cerr<<"Error in opening the file." <<endl;
      return -1;
    }
    infile.clear();

    vector<int> freqs (256, 0);
    size_t filesize = 0;
    unsigned int uniqueSymbols = 0;
    unsigned char nextchar;

    printf("Reading from file \"%s\"... ", argv[1]);
    
    while (1) {      
      nextchar = infile.get();
      if (infile.eof()) break;

      freqs[nextchar]++;
      filesize++;   //num of bytes in the file

      if (freqs[nextchar] == 1) ++uniqueSymbols;
    }

    cout << "done." << endl;
    printf("Found %d unique symbols in input file of size %lu bytes.\n",
                                                uniqueSymbols, filesize);
    infile.close();

    cout << "Building Huffman code tree... ";
    HCTree hctree; //create HCTree object
    if (filesize != 0) hctree.build (freqs);  //build Huffman tree
    cout << "done." << endl;

    printf("Writing to file \"%s\"... ", argv[2]);

    //create header in the output file
    outfile.open (argv[2], ios::binary);
    if (!outfile.is_open()) return -1;
    for(int i = 0; i < 256; ++i) outfile.write((char*)&freqs[i], sizeof(int));// << freqs[i] << endl;
    outfile.flush();
    cout << "done." << endl;
    BitOutputStream bitout = BitOutputStream (outfile);
    infile.open (argv[1], ios::binary);  
    for(size_t i = 0; i < filesize; ++i) {
      nextchar = infile.get();
      if (!infile.good()) break;
      hctree.encode(nextchar, bitout);
    }
    int outfile_size = outfile.tellp();
    float ratio = (float)outfile_size/ (float)filesize;
    printf("Output file has size %d bytes.\n", outfile_size);
    printf("Compression ratio: %.3f\n",ratio);
    
    bitout.flush();
    infile.close();
    outfile.close();
  }//end main
