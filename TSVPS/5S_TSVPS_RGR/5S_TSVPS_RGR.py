regSum = 0
regMul = 0
fastSum = 0
fastMul = 0


def getMQuarter(A, num):
    if isinstance(A, list):
        matrixSize = len(A)
        quarterSize = int(matrixSize / 2)
        Q = [[0 for _ in range(quarterSize)] for _ in range(quarterSize)]

        if num == 1:
            startI = 0
            endI = quarterSize
            startJ = 0
            endJ = quarterSize
        elif num == 2:
            startI = 0
            endI = quarterSize
            startJ = quarterSize
            endJ = matrixSize
        elif num == 3:
            startI = quarterSize
            endI = matrixSize
            startJ = 0
            endJ = quarterSize
        elif num == 4:
            startI = quarterSize
            endI = matrixSize
            startJ = quarterSize
            endJ = matrixSize
        else:
            raise RuntimeError("Quarter is greater than 4 or less then 0")

        for iQ, i in zip(range(quarterSize), range(startI, endI)):
            for jQ, j in zip(range(quarterSize), range(startJ, endJ)):
                Q[iQ][jQ] = A[i][j]
        if len(Q) == 1 and len(Q[0]) == 1:
            return Q[0][0]

        return Q

    return A


def minus(A, B):
    global fastSum, fastMul

    if isinstance(A, list) and isinstance(B, list):
        Q = [[0 for _ in range(len(A))] for _ in range(len(A))]

        for i in range(len(Q)):
            for j in range(len(Q)):
                Q[i][j] = A[i][j] - B[i][j]
                fastSum += 1
        return Q

    fastSum += 1
    return A - B


def plus(A, B):
    global fastSum, fastMul

    if isinstance(A, list) and isinstance(B, list):
        Q = [[0 for _ in range(len(A))] for _ in range(len(A))]

        for i in range(len(Q)):
            for j in range(len(Q)):
                Q[i][j] = A[i][j] + B[i][j]
                fastSum += 1
        return Q

    fastSum += 1
    return A + B


def mul(A, B):
    global fastMul

    if isinstance(A, list) and isinstance(B, list):
        return fastMatrixMultiply(A, B)

    fastMul += 1
    return A * B


def fastMatrixMultiply(A, B):
    M1 = mul(
        minus(getMQuarter(A, 2), getMQuarter(A, 4)),
        plus(getMQuarter(B, 3), getMQuarter(B, 4))
    )
    M2 = mul(
        plus(getMQuarter(A, 1), getMQuarter(A, 4)),
        plus(getMQuarter(B, 1), getMQuarter(B, 4))
    )
    M3 = mul(
        minus(getMQuarter(A, 1), getMQuarter(A, 3)),
        plus(getMQuarter(B, 1), getMQuarter(B, 2))
    )
    M4 = mul(
        plus(getMQuarter(A, 1), getMQuarter(A, 2)),
        getMQuarter(B, 4)
    )
    M5 = mul(
        getMQuarter(A, 1),
        minus(getMQuarter(B, 2), getMQuarter(B, 4)),
    )
    M6 = mul(
        getMQuarter(A, 4),
        minus(getMQuarter(B, 3), getMQuarter(B, 1)),
    )
    M7 = mul(
        plus(getMQuarter(A, 3), getMQuarter(A, 4)),
        getMQuarter(B, 1)
    )

    C1 = plus(minus(plus(M1, M2), M4), M6)
    C2 = plus(M4, M5)
    C3 = plus(M6, M7)
    C4 = minus(plus(minus(M2, M3), M5), M7)

    if isinstance(C1, list):
        C = [[] for _ in range(len(A))]

        indexC = 0
        for i in range(int(len(C) / 2)):
            C[indexC] = [*C1[i], *C2[i]]
            indexC += 1

        for i in range(int(len(C) / 2)):
            C[indexC] = [*C3[i], *C4[i]]
            indexC += 1
    else:
        C = [[C1, C2], [C3, C4]]

    return C


def dgemmBlas(A, B):
    global regSum, regMul
    C = [[0 for _ in range(len(A))] for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(A)):
            for k in range(len(A)):
                C[i][j] += A[i][k] * B[k][j]
                regSum += 1
                regMul += 1
    return C


def main():
    global regSum, regMul, fastSum, fastMul

    matrixSize = 2
    with open('out.csv', 'w+') as file:
        file.write("Size;Regular +;Regular *;Fast +;Fast *;Regular total;Fast total\n")
        while matrixSize <= 512:
            print("Processing: ", matrixSize, "*", matrixSize, "...", sep=" ")
            regSum = 0
            regMul = 0
            fastSum = 0
            fastMul = 0

            A = [[pow(-1, x + y) for x in range(matrixSize)] for y in range(matrixSize)]
            B = [[x + y for x in range(matrixSize)] for y in range(matrixSize)]

            dgemmBlas(A, B)
            fastMatrixMultiply(A, B)

            outStr = str(matrixSize) + " x " + str(matrixSize) + ";" \
                + str(regSum) + ";" \
                + str(regMul) + ";" \
                + str(fastSum) + ";" \
                + str(fastMul) + ";" \
                + str(regSum + regMul) + ";" \
                + str(fastSum + fastMul) + ";" \
                + "\n"

            file.write(outStr)
            file.flush()

            matrixSize *= 2


if __name__ == '__main__':
    main()
