#include <iostream>
#include <vector>
#include <string>
using namespace std;

unsigned long long sam(unsigned long long c, unsigned long long x, unsigned long long n, unsigned long long z) {
    vector<int> bits;
    unsigned long long temp = x;

    while ( temp > 0 ) {
        bits.push_back(temp % 2);
        temp /= 2;
    }

    int l = bits.size();

    for ( int i = l - 1; i >= 0; i-- ) {
        z = z * z % n;
        if ( bits[i] == 1 ) {
            z = z * c % n;
        }
    }

    return z;
}

long long eea(long long a, long long b, long long &s, long long &t) {

    long long a0 = a;
    long long b0 = b;
    long long t0 = 0;
    long long s0 = 1;
    long long q = a0/b0;
    long long r = a0-q*b0;

    long long temp;

    while ( r > 0 ) {
        temp = t0-q*t;
        t0 = t;
        t = temp;
        temp = s0-q*s;
        s0 = s;
        s = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0-q*b0;
    }
    r = b0;

    return r;
}

long long mod_inverse(long long totient, long long e) {
    long long t = 1;
    long long s = 0;
    long long gcd = eea(totient, e, s, t);

    if ( gcd != 1 ) {
        cout<<"Error: e = "<<e<<" has no inverse modulo "<<totient<<"."<<endl;
        return -1;
    }

    t = ((t%totient)+totient)%totient;
    return t;
}

long long encode_block(char c1, char c2, char c3) {
    int v1 = toupper(c1) - 'A';
    int v2 = toupper(c2) - 'A';
    int v3 = toupper(c3) - 'A';
    v1 *= 676;                          //676 = 26^2
    v2 *= 26;
    long long result = v1 + v2 + v3;
    return result;
}

string decode_block(long long value) {
    string result;
    return result;
}

unsigned long long encrypt(unsigned long long m, unsigned long long e, unsigned long long n) {
    return sam(m, e, n, 1);
}

unsigned long long decrypt(unsigned long long c, unsigned long long d, unsigned long long n) {
    return sam(c, d, n, 1);
}

//Note that much of this code is refactored from an assignment I did as a team in Assembly for prerequisite class
//https://github.com/Evbw/RSATeam2/blob/master/RSA.s
int main() {

    long long p = 853;
    long long q = 223;
    long long n = (p*q);
    long long totient = (p-1)*(q-1);
    long long e;

    cout<<endl<<"The value for p and q are 853 and 223, respectively."<<endl;
    cout<<"n = p * q = "<<n<<endl;
    cout<<"phi(n) = (p - 1) * (q - 1) = "<<totient<<endl;

    cout<<"Enter a value for the public exponent, e"<<endl;
    cout<<"(Value must be between 1 and "<<totient<<", and coprime to "<<totient<<"):"<<endl;
    cin>>e;
    
    long long d = mod_inverse(totient, e);
    if ( d == -1 ) {
        cout<<"Invalid value. Exiting."<<endl;
        return 1;
    }

    cout<<"Public key: (e, n) = ("<<e<<", "<<n<<")"<<endl;
    cout<<"Private key: (d, n) = ("<<d<<", "<<n<<")"<<endl;

    int choice = 0;
    while ( choice != -1 ) {
        cout<<"Choose an option:"<<endl;
        cout<<"1 - Encrypt a message (base-26 blocks)"<<endl;
        cout<<"2 - Decrypt a message (base-26 blocks)"<<endl;
        cout<<"-1 Exit"<<endl;
        cin>>choice;

        if ( choice == 1 ) {                                        //Encryption routine
            string message;
            cout<<"Enter a message (letters only)"<<endl;
            cin>>message;

            while ( message.length() % 3 != 0 ) {                   //Pad the message if necessary
                message += 'A';
            }

            vector<unsigned long long>ciphertext;

            for ( int i = 0; i < static_cast<int>(message.length()); i += 3 ) {
                long long m = encode_block(message[i], message[i+1], message[i+2]);
                unsigned long long c = encrypt(m, e, n);
                ciphertext.push_back(c);
            }

            cout<<"Full ciphertext:"<<endl;
            for ( int i = 0; i < ciphertext.size(); i++ ) {
                cout<<ciphertext[i];
            }
            cout<<endl;
        }

        else if ( choice == 2 )  {                                  //Dencryption routine 
            string plaintext = "";
            unsigned long long c;
            cout<<"Please enter the ciphertext:"<<endl;
            while ( cin >> c ) {
                unsigned long long m = decrypt(c, d, n);
                string block = decode_block(m);
            }
            
        }

        if ( choice == 0 || choice > 2 || choice < -1 ) {
            continue;
        }

    }

    return 0;
}