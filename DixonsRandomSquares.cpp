#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    int n = 347881;

    int base[] = {-1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
    int base_size = 10;
    vector<int> smooth_z;
    vector<int> smooth_vals;
    vector<vector<int>> smooth_exponents;

    for ( int z = 600; z = 660; z++ ) {
        int z2 = (z*z) % n;

        int candidates[2] = {z2, z2 - n};

        for ( int c = 0; c < 2; c++ ) {
            int val = candidates[c];
            int temp = val;

            vector<int> exponents(10, 0);

            for ( int i = 1; i < base_size; i++ ) {
                while ( temp % base[i] == 0 ) {
                    temp /= base[i];
                    exponents[i + 1]++;
                }
            }

            if ( temp == 1) {
                smooth_z.push_back(z);
                smooth_vals.push_back(val);
                smooth_exponents.push_back(exponents);
                break;
            }
        }
    }

    int num_smooth = smooth_z.size();

    for ( int a = 0; a < num_smooth; a++ ) {
        for ( int b = a + 1; b < num_smooth; b++ ) {
            for ( int c = b + 1; c < num_smooth; c++ ) {
                vector<int> combined(10, 0);
                bool all_even = true;

                for ( int i = 0; i < 10; i++ ) {
                    combined[i] = smooth_exponents[a][i] + smooth_exponents[b][i] + smooth_exponents[c][i];
                    if ( combined[i] % 2 != 0 ) {
                        all_even = false;
                        break;
                    }
                }
                if (!all_even) {
                    continue;
                }
                
                cout<<"Valid combination found: z = "<<smooth_z[a]<<", "<<smooth_z[b]<<", "<<smooth_z[c]<<endl;

                int x = (smooth_z[a] * smooth_z[b]) % n;
                x = (x * smooth_z[c]) % n;

                int y = 1;
                int half_exp;
                for ( int i = 0; i < base_size; i++ ) {
                    half_exp = combined[i + 1] / 2;
                    for ( int j = 0; j < half_exp; j++ ) {
                        y = (y*base[i]) % n;
                    }
                }
                
                int diff = (x - y % n + n) % n;
                int sum = (x + y) % n;
                int ga = diff;
                int gb = n;
                int t;
                while ( gb != 0 ) {
                    t = gb;
                    gb = ga % gb;
                    ga = t;
                }
            }
        }
    }
}