/*
    File name: Friedman's attack
    Purpose: Simple program for decrypting a known cipher with known key length.
*/

#include <iostream>
#include <array>
#include <vector>
#include <cmath>
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

//An index of coincidence for two random characters (sum of (1/26)^2 = 1/26 ~ 0.0385). ICDIFF = 0.065 - 0.0385
const double RIC = 0.0385;
const double ICDIFF = 0.0265;

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

/*Purpose:  Computes the Index of Coincidence (IC) for a given string of ciphertext.
    Input: A string, s, consisting of letters A-Z (no lowercase)
    Variables:
        f: An array to count the frequency of each letter in the alphabet
        n: Total number of characters in a string
        num: The numerator of the IC formula {f[i](f[i] - 1)}
        den: The denominator of the IC formula {n(n-1)}
    Return: A double representing the IC or likelihood that two randomly chosen characters from the input string are identical
*/

double indexOfCoincidence(string s) {
    if ( s.size() < 2 ) {
        return 0.0;
    }

    array <int, ALPHABET> f{};
    for ( char c : s ) f[c - 'A']++;
    int n = s.size();
    int num = 0;
    for ( int i = 0; i < ALPHABET; i++ ) {
        num += 1 * f[i] * (f[i] - 1);
    }
    int den = n * (n - 1);
    return ( den == 0 ) ? 0.0 : (double)num/(double)den;
}

/*Purpose:  Extracts a substring to a single column
    Input: A string, ct, containing the ciphertext string, an int, column for the column index, and an int keyLength
            representing the assumed keyLength.
    Variables:
        columnText: A string used to store every keyLength character from ct starting at index column
        position: An integer used to step through ct at intervals of keyLength.
    Return: A string containing all characters from the ct that belong to the specified column.
*/

string getColumn (string ct, int column, int keyLength) {
    string columnText;
    for ( int position = column; position < (int)ct.size(); position += keyLength ) {
        columnText.push_back(ct[position]);
    }
    return columnText;
}

/*Purpose:  Computes the average Index of Coincidence (IC) for all given an assumed key length.
    Input: A string, ct, containing the ciphertext string and an int keyLength representing the assumed keyLength.
    Variables:
        sum: Accumulates the Index of Coincidence for each column.
        columns: Counts the columns that have enough characters to produce a valid IC value.
        col: An integer to iterate over each column index.
    Return: A double representing the mean IC over all valid columns for the given key length.
*/

double averageColumnIC(string ct, int keyLength) {
    if ( keyLength < 0 ) return 0.0;
    double sum = 0.0;
    int columns = 0;
    for ( int col = 0; col < keyLength; col++ ) {
        string c = getColumn(ct, col, keyLength);
        if ( c.size() >= 2 ) {
            sum += indexOfCoincidence(c);
            columns++;
        }
    }
    return (columns == 0) ? 0.0 : sum / (double)columns;
}

/*Purpose:  Estimates the Vigenere key length using Friedman's Index of Coincidence (IC) method applied to a ciphertext.
    Input: A string, ct, containing the ciphertext.
    Variables:
        ic: The IC over the whole ciphertext.
        n: Total number of characters in the ciphertext.
        num: The difference between English and random IC values.
        den: A normalization term accounting for ciphertext length and deviation from random coincidence.
    Return: An integer representing the estimated key length, rounded to the nearest whole number.
*/

int friedmanEstimate(string ct) {
    double ic = indexOfCoincidence(ct);
    double n = (double)ct.size();
    double num = ICDIFF * n;
    double den = (TARGETM_G - ic) + n * (ic - 0.0385);
    if ( den < 0.0 ) {
        return 1;
    }
    int k = (int)round(num/den);
    if ( k < 1 ) {
        k = 1;
    }
    return k;
}

/*Purpose:  Selects the most likely Vigenere key length by evaluating candidates based on Friedman statistics
    Input: A string, ct, containing the ciphertext string and an int maxKeyLength representing the maximum key length to be tested.
    Variables:
        estimate: An initial key length estimate obtained from Friedman's formula.
        bestK: The key length that best matches expected occurences of letters in English.
        bestScore: The smallest deviation from the target IC value.
        k: An integer used to iterate through candidate key lengths.
        avgIC: The average IC across columns for a given k.
        score: A weighted measure of how closely avgIC matches English IC.
    Return: An integer representing the most probable key length.
*/

int chooseKeyLengthFriedman(string ct, int maxKeyLength ) {
    
    int estimate = friedmanEstimate(ct);
    int bestK = 1;
    double bestScore = 100;
    double avgIC = 0;
    double score = 0;

    for ( int k = 1; k <= maxKeyLength; k++ ) {
        avgIC = averageColumnIC(ct, k);
        score = fabs(avgIC - TARGETM_G);
        score += 0.001 * fabs(k - estimate);

        if ( score < bestScore ) {
            bestScore = score;
            bestK = k;
        }
    }
    return bestK;
}

/*Purpose: Computes M_i for a column of the key, assuming a specific key letter.
    Input: A string, ct, an int for the column, an int for a specific letter of the alphabet i, and an int for the keyLength
    Variables:
        freq: And array for each letter of the alphabet to tabulate frequency
        n: A count of the number of iterations through the for loop
    Return: A double, the sum divided by the number of for loop iterations
*/

double computeM_forColumnKey(string ct, int col, int i, int keyLength) {
    array<int, ALPHABET> freq{};
    int n = 0;

    for ( int pos = col; pos < ct.size(); pos += keyLength ) {
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
    Input: A string of ciphertext, an int for the column, and an int for the keyLength
    Variables:
        best: An integer that is as close as possible to the TARGETM_G
        diff and bestDiff: Doubles that are compared to determine the small different from the TARGETM_G
        M: A double that is used for comparison and assignment for the frequency of a letter
    Return:
        A number from 0-25 representing the letters A-Z
*/

int bestKeyForColumn(string ct, int col, int keyLength) {
    int best = 0;
    double bestDiff = 100;
    double M = 0.0;
    double diff = 0.0;
    
    for ( int i = 0; i < ALPHABET; i++ ) {
        M = computeM_forColumnKey(ct, col, i, keyLength);
        diff = (M > TARGETM_G) ? (M - TARGETM_G) : (TARGETM_G - M);

        if ( diff < bestDiff ){
            bestDiff = diff;
            best = i;
        }
    }
    return best;
}

int main() {

    //Declare a variable to pass to functions containing the ciphertext
    string ct = CIPHERTEXT;

    //Guess a key length
    int keyLength = chooseKeyLengthFriedman(ct, SEARCHLIMIT);

    cout<<"Estimated key length: "<<keyLength<<endl<<endl;
    
    //Establish an array for finding the best column for the shifting of an encrypted letter
    vector<int> keyShift(keyLength);

    for ( int col = 0; col < keyLength; col++ ) {
        keyShift[col] = bestKeyForColumn(CIPHERTEXT, col, keyLength);
    }

    //Given the array keyShift has the best value for every column, establish a key and push the values onto it
    string key;

    for ( int k = 0; k < keyLength; k++ ) {
        key.push_back(char('A' + keyShift[k]));
    }

    //Print out the original ciphertext and the key

    cout<<"Ciphertext: "<<CIPHERTEXT<<endl<<endl;

    cout<<"Key: "<<key<<endl<<endl;

    //Then add the values of the plaintext properly offset by the corresponding key value

    string plaintext;
    for ( int i = 0; i < CIPHERTEXT.size(); i++ ) {
        int k = keyShift[i % keyLength];
        plaintext.push_back(shiftUpper(CIPHERTEXT[i], -k));
    };

    cout<<"Plaintext: "<<plaintext<<endl;
    return 0;
}