/*
 * File: HCNode.cpp
 * Date: 04/16/2016
 * Description: This file compares this HCNode and other HCNode for priority
 * ordering. Smaller count means higher priority
 * */

#include "HCNode.hpp"

bool HCNode::operator < (const HCNode& other) {
  //if counts are different, just compare counts and return
  if (count != other.count) return count > other.count;
  
  //if counts are equal, compare symbols
  return symbol < other.symbol;
}

bool comp (HCNode* one, HCNode* other) {
  return (*one < *other);
}
