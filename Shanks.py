import math

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