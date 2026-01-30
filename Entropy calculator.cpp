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
    vector<double> pV = { 1.0/6.0, 2.0/6.0, 3.0/6.0 };
    //Values for keys, which are equiprobably, in a vector
    vector<double> kV = { 1.0/3.0 };

    //Encryption matrix e[k][p] = c (with 0, 1, 2, 3 corresponding to ciphertext 1, 2, 3, 4)
    int e[NUMK][NUMP] {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 0}
    };

    //Compute value for P(C)
    vector<double> cV(NUMC, 0.0);
    for ( int k = 0; k < NUMK; k++ ) {
        for ( int p = 0; p < NUMP; p++ ) {
            int c = e[k][p];
            cV[c] += kV[k] * pV[p];
        }
    }
}