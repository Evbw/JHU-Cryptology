import math

def point_add(P, Q, a, p):
    x1 = P[0]
    y1 = P[1]
    x2 = Q[0]
    y2 = Q[1]
    lam = ((y2 - y1) * modinv(x2 - x1, p)) % p

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

if __name__ == "__main__":
    main()