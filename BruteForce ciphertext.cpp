#include <iostream>
#include <vector>
using namespace std;

const string CIPHERTEXT = "XQFETMHQEAYQRGZIUFTODKBFAMFVTG";
const int ALPHABET = 26;

int main(){

    for ( int i = 0; i <= ALPHABET; i++ ) {
        for ( int j = 0; j <= CIPHERTEXT.length(); j++ ) {
            char c = CIPHERTEXT[j];
            if ( c < 91 ) {
                c = c + i;
                cout<<c;
            }
            else
                cout<<'A';
        }
        cout<<endl;
    }
}