import math

def modinv(val, p):
    return pow(val, p - 2, p)

def point_add(P, Q, a, p):
    x1 = P[0]
    y1 = P[1]
    x2 = Q[0]
    y2 = Q[1]
    lam = ((y2 - y1) * modinv(x2 - x1, p)) % p
    x3 = (lam * lam - x1 - x2) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def point_negate(P, p):
    return (P[0], (-P[1]) % p)

def main():
    a = 1
    b = 26
    p = 127
    Pa1 = (9, 16)
    Pa2 = (6, 11)
    Pb = (11, 15)
    Pc = (4, 27)

    A = point_add(Pa1, Pa2, a, p)
    print(f"Addition: {A}")
    
    B = point_negate(Pb, p)
    print(f"Negation: {B}")

if __name__ == "__main__":
    main()