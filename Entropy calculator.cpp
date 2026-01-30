/*
    File name: Entropy calculator
    Purpose: Simple program for calculating the entropy of fixed probabilities and keys
*/

#include <iostream>
#include <vector>
using namespace std;

//There is a fixed number of plaintext elements, keys, and ciphertexts
const int NUMP = 3, NUMK = 3, NUMC = 4;

int main() {
    //Values for a, b, and c stored in a vector
    vector<double> p = { 1.0/6.0, 2.0/6.0, 3.0/6.0 };
    //Values for keys, which are equiprobably, in a vector
    vector<double> k = { 1.0/3.0 };

}