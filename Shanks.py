import math

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

def main():

    p1 = 24691
    n = p1-1
    alpha = 106
    beta = 12375
    x1 = shanks(p1, n, alpha, beta)
    print(x1)

    p2 = 458009
    n = p2-1
    alpha = 6
    beta = 248338
    x2 = shanks(p2, n, alpha, beta)
    print(x2)

if __name__ == "__main__":
    main()