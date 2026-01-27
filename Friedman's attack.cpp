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

//Target value for character coincidence frequency and search limit for a likely key length
const double TARGETM_G = 0.065;
const int SEARCHLIMIT = 10;

//An index of coincidence for two random characters (sum of (1/26)^2 = 1/26 ~ 0.0385)
const double RIC = 0.0385;

/*Purpose:  Shifts the input character based on ASCII, with A = 65 being the baseline
    Input: A character, c, and a shift amount
    Variables:
        x: Used to calculate the amount that the character is shifted.
    Return: A character, offset a certain amount from A, from 0-25 (A-Z)
*/

char shiftUpper(char c, int shift) {
    int x = (c - 'A') + shift;
    x %= ALPHABET;
    if ( x < 0 ) {
        x += ALPHABET;
    }
    return char('A' + x);
}

double indexOfCoincidence(string s) {
    if ( s.size() < 2 ) {
        return 0.0
    }

    array <int, ALPHABET> f{};
    for ( char c : s ) f[c - 'A']++;
    int N = s.size();
    int num = 0;
    for ( int i = 0; i < ALPHABET; i++ ) {
        num += 1 * f[i] * (f[i] - 1);
    }
    int den = N * (N - 1);
    return ( den == 0 ) ? 0.0 : (double)num/(double)den;
}

int friedmanEstimate(string ct) {
    double ic = indexOfCoincidence(ct);
}

int chooseKeyLengthFriedman(string ct, int maxKeyLength ) {
    
    int estimate = friedmanEstimate(ct);
}

/*Purpose: Computes M_i for a column of the key, assuming a specific key letter.
    Input: A string, ct, and a and integers for the column and i (specific letter of the alphabet)
    Variables:
        freq: And array for each letter of the alphabet to tabulate frequency
        n: A count of the number of iterations through the for loop
    Return: A double, the sum divided by the number of for loop iterations
*/

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

/*Purpose: Determines the best key for a column by finding the closest value to TARGETM_G
    Input: A string of ciphertext and an integer for the column
    Variables:
        best: An integer that is as close as possible to the TARGETM_G
        diff and bestDiff: Doubles that are compared to determine the small different from the TARGETM_G
        M: A double that is used for comparison and assignment for the frequency of a letter
    Return:
        A number from 0-25 representing the letters A-Z
*/

int bestKeyForColumn(string ct, int col) {
    int best = 0;
    double bestDiff = 100;
    double M = 0.0;
    double diff = 0.0;
    
    for ( int i = 0; i < ALPHABET; i++ ) {
        M = computeM_forColumnKey(ct, col, i);
        diff = (M > TARGETM_G) ? (M - TARGETM_G) : (TARGETM_G - M);

        if ( diff < bestDiff ){
            bestDiff = diff;
            best = i;
        }
    }
    return best;
}

int main() {

    string ct = CIPHERTEXT;

    int keyLength = chooseKeyLengthFriedman(ct, SEARCHLIMIT);
    
    //Establish an array for finding the best column for the shifting of an encrypted letter
    array<int, KEYLENGTH> keyShift{};
    for ( int col = 0; col < KEYLENGTH; col++ ) {
        keyShift[col] = bestKeyForColumn(CIPHERTEXT, col);
    }

    //Given the array keyShift has the best value for every column, establish a key and push the values onto it
    string key;

    for ( int k = 0; k < KEYLENGTH; k++ ) {
        key.push_back(char('A' + keyShift[k]));
    }

    //Print out the original ciphertext and the key

    cout<<CIPHERTEXT<<endl;

    cout<<"Key: "<<key<<endl;

    //Then add the values of the plaintext properly offset by the corresponding key value

    string plaintext;
    for ( int i = 0; i < CIPHERTEXT.size(); i++ ) {
        int k = keyShift[i % KEYLENGTH];
        plaintext.push_back(shiftUpper(CIPHERTEXT[i], -k));
    };

    cout<<"Plaintext: "<<plaintext<<endl;
    return 0;
}