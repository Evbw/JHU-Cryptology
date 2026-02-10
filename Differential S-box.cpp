#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int sbox[16] = {0xF, 0x0, 0xB, 0xD, 0x1, 0xC, 0x6, 0xE, 0x2, 0x9, 0x8, 0x4, 0x5, 0xA, 0x3, 0x7};    //Hardcoded S-Box

    for ( int xdiff = 0; xdiff < 16; xdiff++ ) {            //Beginning my "if"inite loop
        for ( int ydiff = 0; ydiff < 16; ydiff++ ) {
            int count = 0;                                  //Reset the count at the beginning of each encrypted comparison
            for ( int x = 0; x < 16; x++ ) {
                int xstar = x ^ xdiff;
                if ( (sbox[x] ^ sbox[xstar]) == ydiff ) {
                    count++;
                }
            }
        }
    }

    return 0;
}