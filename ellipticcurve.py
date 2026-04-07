import math

def f(x, a, b, p):
    return (x*x*x + a*x + b) % p

def main():
    a = 1
    b = 28
    p = 71

    testexp = (p-1)//2
    rootexp = (p+1)//4

    for x in range(0,p):
        r = f(x, a, b, p)
        if pow(r,testexp,p) == 1:
            y1 = pow(r,rootexp,p)
            y2 = (-y1) % p
            print(f"({x}, {y1})")
            print(f"({x}, {y2})")
        if r == 0:
            print(f"({x}, 0)")

if __name__ == "__main__":
    main()