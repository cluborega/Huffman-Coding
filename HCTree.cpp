/*
 * File: HCTree.cpp
 * Date: 04/15/2016
 * Description: Contains function prototypes for the HCTree class.
 */

#include <iostream>
#include <vector>
#include <stack>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;
    
    void deleteAllNodes (HCNode* node) {
      if (node->c1 != 0) deleteAllNodes (node->c1);
      if (node->c0 != 0) deleteAllNodes (node->c0);
      delete node;
      node = 0;
    }

    HCTree:: ~HCTree() {
      if (root) deleteAllNodes (root);
    }

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree:: build(const vector<int>& freqs) {
      priority_queue <HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

      //for loop to first create a forest using a priority queue
      for (int i = 0; i < 256; i++) {
        if (freqs[i] > 0) {
          HCNode* n = new HCNode (freqs[i], (byte) i);
          leaves[i] = n;
          pq.push(n);
        }
      } //end for i<256 loop

      while (pq.size() > 1) {
        HCNode *n1 = pq.top();
        pq.pop();
        HCNode *n2 = pq.top();
        pq.pop();

        int newCount = n1->count + n2->count;
        byte newSymbol;
        if (n1->symbol < n2->symbol)
          newSymbol = n1->symbol;
        else
          newSymbol = n2->symbol;

        HCNode *newNode = new HCNode (newCount, newSymbol);
        
        //update children pointers
        newNode->c0 = n1;
        newNode->c1 = n2;

        //update parent pointers
        n1->p = newNode;
        n2->p = newNode;
        
        //push the new trie in the heap
        pq.push(newNode);
      }//end while loop
      if (pq.size() == 0) return;
      root = pq.top(); //assign new root
    }

   // void encode(byte symbol, BitOutputStream& out) const{}

    /**
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USED FOR THE CHECKPOINT ONLY
     */
    void HCTree::encode(byte symbol, BitOutputStream& out) const {
      stack<int> stk;
      HCNode* curr = leaves[symbol];
      //cout << "debug in encode method" <<endl;
      while (curr->p != 0) {
        //cout << curr << "current node "<<endl;
        if (curr == curr->p->c0) stk.push(0);
        else stk.push(1);
        curr = curr->p;
      }//end while
      while (!stk.empty()) {
        out.writeBit(stk.top());
        stk.pop();
      }
      //for( vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it ) {
        //out.writeBit(*it);
      //}
    }

   // int decode(BitInputStream& in) const{}

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USED FOR THE CHECKPOINT ONLY
     */
    int HCTree::decode(BitInputStream& in) const {
      HCNode* n = root;
      int nextint;
      while (n->c0 || n->c1) {
        nextint = in.readBit();
        if (nextint == 0) n = n->c0;
        if (nextint == 1) n = n->c1;
      }//end while
      return n->symbol;
    }
