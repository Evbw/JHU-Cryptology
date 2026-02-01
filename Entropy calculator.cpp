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

/*Purpose: Calculates entropy (H(x) for x) based on an additive calculation
    Input: A vector of probabilities for a given plaintext, key, or cipher
    Variables:
        H: A double used to hold the accumulated value of the entropy of each individual probability
        p: A double used for looping through each individual probability from the vector
    Return: H, the entropy value
*/

double entropycalculation(vector<double> probs) {
    double H;
    for ( double p: probs ) {
        if ( p > 0.0 ) {
            H += -p * log2(p);  //The formula is the negative value of the probability multiplied by log base 2 of that probability.
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
            int c = e[k][p];            //Establish a ciphertext value in a given spot in the matrix
            cV[c] += kV[k] * pV[p];     //Add the ciphertext value to that part of the cV vector
        }
    }

    //Calculate H(P), H(K), H(C)
    double HP = entropycalculation(pV); //Calculate HP, HK, and HC with the appropriate vectors
    double HK = entropycalculation(kV);
    double HC = entropycalculation(cV);

    double hkGivenC = HK + HP - HC;     //Per the Example document

    double hpGivenC = 0.0;              //Declare value for H(P|C)
    double hpc = 0.0;                   //Declare holding value for the calculation of entropy
    double join = 0.0;                  //A cumulative value for the numerator of the calculation of H(P|C)
    vector<double> prxy(NUMP, 0.0);     //A vector for the value of Pr(x|y), for finding the entropy
    for ( int c = 0; c < NUMC; c++ ) {  //Hey! That's the name of the programming language!

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
        hpGivenC += cV[c] * hpc;        //Cumulative value of H(P|C)
    }

    cout<<endl<<"H(P) = "<<HP<<endl<<"H(K) = "<<HK<<endl<<"H(C) = "<<HC<<endl;

    cout<<endl<<"H(K|C) = "<<hkGivenC<<endl<<"H(P|C) = "<<hpGivenC<<endl;
    return 0;
}