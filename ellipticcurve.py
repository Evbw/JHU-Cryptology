import math

def isNonSingular(a, b, p):
    return 0 != (( 4*a*a*a + 27*b*b) % p)

def main():
    a = 1
    b = 28
    p = 71

    if not isNonSingular(a, b, p):
        print("Invalid value")
        return 0
    
if __name__ == "__main__":
    main()