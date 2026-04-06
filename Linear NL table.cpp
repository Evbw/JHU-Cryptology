#include <iostream>
#include <iomanip>
using namespace std;

/*Purpose: To XOR elements between an unencrypted text and the encrypted version via means of a mask
    Input: A mask and a value, encrypted or unencrypted
    Variables:
        bits: The bits that will be compared from the initial value, selected for comparison by the mask
        parity: Accumulation of the selected bits, returning 0 or 1 (XOR returns 1 or 0)
    Return: parity - Either 0 or 1 after the bits are shifted and all bits filtered through the mask are calculated
*/


int xord(int mask, int val) {
    int bits = mask & val;
    int parity = 0;
    while (bits) {
        parity ^= (bits & 1);
        bits >>= 1;                 //Shift bits right to continue XOR operation
    }
    return parity;
}

int main() {
    int sbox[16] = {0x7, 0x3, 0xA, 0x5, 0x4, 0x8, 0x9, 0x2, 0xE, 0x6, 0xC, 0x1, 0xD, 0xB, 0x0, 0xF};    //Hardcoded S-Box

    for ( int a = 0; a < 16; a++ ) {                //Beginning my "if"inite loop
        for ( int b = 0; b < 16; b++ ) {
            int count = 0;                          //Reset the count at the beginning of each b comparison
            for ( int x = 0; x < 16; x++ ) {
                int y = sbox[x];                    //Add a variable to cycle through the substitution values of the s-box
                int ax = xord(a, x);                //XOR the original value with the mask a
                int by = xord(b, y);                //XOR or the substitution value with the mask b
                if ( ax == by ) {
                    count++;                        //If the values are linearly approximate, increase the count.
                }
            }
            cout<<setw(6)<<count;
        }
        cout<<endl;
    }

    return 0;
}