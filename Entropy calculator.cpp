/*
    File name: Entropy calculator
    Purpose: Simple program for calculating the entropy of fixed probabilities and keys
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//There is a fixed number of plaintext elements, keys, and ciphertexts
const int NUMP = 3, NUMK = 3, NUMC = 4;

double entropycalculation(vector<double> probs) {
    double H;
    for ( double p: probs ) {
        if ( p > 0.0 ) {
            H += -p * log2(p);
        }
    }
    return H;
}

int main() {
    //Values for a, b, and c stored in a vector
    vector<double> pV = { 1.0/6.0, 2.0/6.0, 3.0/6.0 };
    //Values for keys, which are equiprobably, in a vector
    vector<double> kV(NUMK,1.0/3.0 );

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

    //Calculate H(P), H(K), H(C)
    double HP = entropycalculation(pV);
    double HK = entropycalculation(kV);
    double HC = entropycalculation(cV);

    double hkGivenC = HK + HP - HC;

    double hpGivenC = 0.0;
    double hpc = 0.0;
    double join = 0.0;
    vector<double> prxy(NUMP, 0.0);
    for ( int c = 0; c < NUMC; c++ ) { //Hey! That's the name of the programming language!
        //if (cV[c] <= 0.0) continue;

        for ( int p = 0; p < NUMP; p++ ) {
            join = 0.0;
            for ( int k = 0; k < NUMK; k++ ) {
                if (e[k][p] == c) {
                    join += pV[p] * kV[k];
                }
            }
            prxy[p] = join / cV[c];    
        }
        hpc = entropycalculation(prxy);
        hpGivenC += cV[c] * hpc;
    }

    cout<<endl<<"H(P) = "<<HP<<endl<<"H(K) = "<<HK<<endl<<"H(C) = "<<HC<<endl;

    cout<<endl<<"H(K|C) = "<<hkGivenC<<endl<<"H(P|C) = "<<hpGivenC<<endl;
}