/*
    File name: Friedman's attack
    Purpose: Simple program for decrypting a known cipher with known key length.
*/

#include <iostream>
#include <array>
using namespace std;

//Declare probabilities as determined by table 2.1 of the Cryptography: Theory and Practice Fourth edition textbook
static const array<double, 26> PROBABILITY = { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070,
    0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060,
    0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

int main() {
    
}