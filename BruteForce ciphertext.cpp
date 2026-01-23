#include <iostream>
#include <vector>
using namespace std;

const string CIPHERTEXT = "XQFETMHQEAYQRGZIUFTODKBFAMFVTG";
const int ALPHABET = 26;
const int OFFSET = 32;

int main(){

    char c = 0;

    for ( int i = 1; i <= ALPHABET; i++ ) {
        for ( int j = 0; j < CIPHERTEXT.length(); j++ ) {
            c = CIPHERTEXT[j] + i;
            if ( c > 90 ) {
                c = c - ALPHABET;
                cout<<(char)tolower(c);
            }
            else
                cout<<(char)tolower(c);
        }
        cout<<endl;
    }
}