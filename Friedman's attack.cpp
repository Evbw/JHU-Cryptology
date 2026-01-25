/*
    File name: Friedman's attack
    Purpose: Simple program for decrypting a known cipher with known key length.
*/

#include <iostream>
#include <array>
using namespace std;

//Declare probabilities as determined by table 2.1 of the Cryptography: Theory and Practice Fourth edition textbook
const array<double, 26> PROBABILITY = { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070,
    0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060,
    0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

//Ciphertext to be decrypted and length of the alphabet
const string CIPHERTEXT = "BNWEOMZOBNTALBAECJHKXSFGYZXMBNBVZSBXMETRRTNOLTUWGXKOTJTUFIAYFCLTOWMPXPEGVMLSBXICMTVFZBAEZAGMWSTWKLBJXKMZTDRTNOZIAYBAMWVUXILHNJWILWEAMQGGGZXKHDRAGBAESAKAMPYSVMMHRJXNHRRAYGHUJJBBXTUWVWWENKVTXVRJEGTSCGLABBYWRWNAEWUGWESAGQMIBFGWMSZSKBXNBMZPMOQWUCZIGTKQTNXWKVBGUSGBHEEJBAAUZSGJNTGGKMTLYQYWNLGZBVZSHHRWNNRWWIVOZHNBXRCSNTXHEDBKAISQHCYIAVMPTTLGNZXSCWGLBNTSEUHSGSETROHJMQFEBFMPXOEQLBTRGLNZGIAYLWFENLMMGTVGGBHPESVBBCNDMPBNTKBBPIYDBUIRBNXGHUELAMHRVWLQYYBMYQGDGZTBROHJXAIEAVBVZAYEHAMAYDRWNRGAFMHNCJTKMIPWLBTRGLNZGIAYLWFENLMMGTVGGBHTUWHZXTVUTTMHVFZABTJAETBMCJHDXYBMKXKAPLBKXDBFTTWKAMMP";
const int ALPHABET = 26;

//Known key length and a target value for character coincidence frequency
const int KEYLENGTH = 6;
const double TARGETM_G = 0.065;

char shiftUpper(char c, int shift) {
    int x = (c - 'A') + shift;
    x % ALPHABET;
    if ( x < 0 ) {
        x += ALPHABET;
    }
    return char('A' + x);
}

double computeM_forColumnKey(string ct, int col, int i) {
    array<int, ALPHABET> freq{};
    int n = 0;

    for ( int pos = col; pos < ct.size(); pos += KEYLENGTH ) {
        char c = shiftUpper(ct[pos], -i);
        freq[c - 'A']++;
        n++;
    }

    double sum = 0.0;

    if ( n == 0 ) return sum;

    for ( int j = 0; j < ALPHABET; j++ ) {
        sum += double(freq[j]) * PROBABILITY[j];
    }
    return sum / double(n);
}

int bestKeyForColumn(string ct, int col) {
    int best = 0;
    double bestDiff = 100;
    double M = 0.0;
    double diff = 0.0;
    
    for ( int i = 0; i < ALPHABET; i++ ) {
        M = computeM_forColumnKey(ct, col, i) 
        diff = (M > TARGETM_G) ? (M - TARGETM_G) : (TARGETM_G - M);

        if ( diff < bestDiff ){
            bestDiff = diff;
            best = i;
        }
    }
    return best;
}

int main() {
    
    //Establish an array for finding the best column for the shifting of an encrypted letter
    array<int, KEYLENGTH> keyShift{};
    for ( int col = 0; col < KEYLENGTH; col++ ) {
        keyShift[col] = bestKeyForColumn(CIPHERTEXT, col);
    }

}