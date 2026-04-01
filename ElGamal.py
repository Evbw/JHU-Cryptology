import math
import sys
import fileinput

def shanks(p, n, alpha, beta):

    m = math.isqrt(n)             #Set the square root of n

    if m*m < n:
        m += 1

    alpha_m = pow(alpha, m, p)      #Start the baby steps. a^m mod p
    L1 = {}                         #Dictionary to store the list
    power = 1                       #a^(m*0) = 1
    for j in range(m):
        L1[power] = j
        power = (power*alpha_m) % p

    alpha_inv = pow(alpha, -1, p)   #Start the giant steps. a^(-1) mod p
    gamma = beta % p                #i = 0: B*a^0
    for i in range(m):
        if gamma in L1:             #Find a matching set of coordinates
            j = L1[gamma]
            return (m*j+i) % n      #log_a(B) = (m*j+i) mod n
        gamma = (gamma*alpha_inv) % p
    
    return None

def read_ciphertexts(filename):
    pairs = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                r, s = line.split(',')
                pairs.append = ((int(r), int(s)))
    return pairs
    

def main():
    p = 649663831
    alpha = 295850
    beta = 56181604
    n = p-1

    filename = 'cipher.txt'

    a = shanks(p, n, alpha, beta)
    print(f"{a}")

    ciphertexts = read_ciphertexts(filename)


if __name__ == "__main__":
    main()