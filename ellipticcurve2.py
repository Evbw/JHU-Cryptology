import math

def modinv(val, p):                                         
    return pow(val, p - 2, p)                               #Computer modular inverse using Fermat's Little Theorem

def point_add(P, Q, p):
    x1 = P[0]                                               #Add points P and Q on an elliptic curve over F_p
    y1 = P[1]                                               #Using secant line formula (Case 1: x1 != x2)
    x2 = Q[0]                                               #lambda = (y2 - y1)/(x2 - x1)
    y2 = Q[1]
    lam = ((y2 - y1) * modinv(x2 - x1, p)) % p
    x3 = (lam * lam - x1 - x2) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def point_negate(P, p):
    return (P[0], (-P[1]) % p)                              #Compute Additive Inverse (Case 2: x1 = x2 and y1 = -y2)

def point_double(P, a, p):
    x1 = P[0]                                               #Double point p on the curve (Case 3: x1 = x2 and y1 = y2)
    y1 = P[1]                                               #lambda = (3x1^2 + a)/(2y1)
    lam = ((3 * x1 * x1 + a) * modinv(2 * y1, p)) % p
    x3 = (lam * lam - 2 * x1) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def main():
    a = 1                                                   #Parameters for y^2 = x^3 + x + 26 over Z_127
    b = 26
    p = 127
    Pa1 = (9, 16)                                           #Hardcoded points
    Pa2 = (6, 11)
    Pb = (11, 15)
    Pc = (4, 27)

    #Part A: point addition P1 + P2 where P1 != P2
    A = point_add(Pa1, Pa2, p)
    print(f"Addition: {A}")
    
    #Part B: point negation -P = (x, -y mod p)
    B = point_negate(Pb, p)
    print(f"Negation: {B}")

    #Part C: point doubling P + P = 2P
    C = point_double(Pc, a, p)
    print(f"Doubling: {C}")

if __name__ == "__main__":
    main()