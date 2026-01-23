#include <iostream>
#include <vector>
using namespace std;

const string CIPHERTEXT = "XQFETMHQEAYQRGZIUFTODKBFAMFVTG";
const int ALPHABET = 26;

int main(){
    for ( int i = 0; i <= ALPHABET; i++ ) {
        for ( int j = 0; j <= CIPHERTEXT.length(); j++ ) {
            if ( CIPHERTEXT[j] < 91 ) {
                cout<<CIPHERTEXT[j+i];
            }
            else
                cout<<65;
        }
    }
}