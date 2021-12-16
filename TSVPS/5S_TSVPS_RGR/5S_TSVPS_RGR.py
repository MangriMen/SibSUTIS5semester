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


def minus(A, B, counters):
    if isinstance(A, list) and isinstance(B, list):
        Q = [[0 for _ in range(len(A))] for _ in range(len(A))]

        for i in range(len(Q)):
            for j in range(len(Q)):
                Q[i][j] = A[i][j] - B[i][j]
                counters['sum'] += 1
        return Q

    counters['sum'] += 1
    return A - B


def plus(A, B, counters):
    if isinstance(A, list) and isinstance(B, list):
        Q = [[0 for _ in range(len(A))] for _ in range(len(A))]

        for i in range(len(Q)):
            for j in range(len(Q)):
                Q[i][j] = A[i][j] + B[i][j]
                counters['sum'] += 1
        return Q

    counters['sum'] += 1
    return A + B


def mul(A, B, counters):
    if isinstance(A, list) and isinstance(B, list):
        return fastMatrixMultiply(A, B, counters)

    counters['mul'] += 1
    return A * B


def fastMatrixMultiply(A, B, counters):
    M1 = mul(
        minus(getMQuarter(A, 2), getMQuarter(A, 4), counters),
        plus(getMQuarter(B, 3), getMQuarter(B, 4), counters),
        counters
    )
    M2 = mul(
        plus(getMQuarter(A, 1), getMQuarter(A, 4), counters),
        plus(getMQuarter(B, 1), getMQuarter(B, 4), counters),
        counters
    )
    M3 = mul(
        minus(getMQuarter(A, 1), getMQuarter(A, 3), counters),
        plus(getMQuarter(B, 1), getMQuarter(B, 2), counters),
        counters
    )
    M4 = mul(
        plus(getMQuarter(A, 1), getMQuarter(A, 2), counters),
        getMQuarter(B, 4),
        counters
    )
    M5 = mul(
        getMQuarter(A, 1),
        minus(getMQuarter(B, 2), getMQuarter(B, 4), counters),
        counters
    )
    M6 = mul(
        getMQuarter(A, 4),
        minus(getMQuarter(B, 3), getMQuarter(B, 1), counters),
        counters
    )
    M7 = mul(
        plus(getMQuarter(A, 3), getMQuarter(A, 4), counters),
        getMQuarter(B, 1),
        counters
    )

    C1 = plus(minus(plus(M1, M2, counters), M4, counters), M6, counters)
    C2 = plus(M4, M5, counters)
    C3 = plus(M6, M7, counters)
    C4 = minus(plus(minus(M2, M3, counters), M5, counters), M7, counters)

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

    counters['sum'] += 18
    counters['mul'] += 7

    return C


def dgemmBlas(A, B, counters):
    C = [[0 for _ in range(len(A))] for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(A)):
            for k in range(len(A)):
                C[i][j] += A[i][k] * B[k][j]
                counters['sum'] += 1
                counters['mul'] += 1
    return C


def main():
    matrixSize = 2
    with open('out.csv', 'w+') as file:
        file.write("Size;Regular +;Regular *;Fast +;Fast *;Regular total;Fast total\n")
        while matrixSize <= 512:
            print("Processing: ", matrixSize, "*", matrixSize, "...", sep=" ")
            A = [[pow(-1, x + y) for x in range(matrixSize)] for y in range(matrixSize)]
            B = [[x + y for x in range(matrixSize)] for y in range(matrixSize)]

            regCounters = dict()
            regCounters['sum'] = 0
            regCounters['mul'] = 0

            fastCounters = dict()
            fastCounters['sum'] = 0
            fastCounters['mul'] = 0

            dgemmBlas(A, B, regCounters)
            fastMatrixMultiply(A, B, fastCounters)

            outStr = str(matrixSize) + " x " + str(matrixSize) + ";" \
                + str(regCounters['sum']) + ";" \
                + str(regCounters['mul']) + ";" \
                + str(fastCounters['sum']) + ";" \
                + str(fastCounters['mul']) + ";" \
                + str(regCounters['sum'] + regCounters['mul']) + ";" \
                + str(fastCounters['sum'] + fastCounters['mul']) + ";" \
                + "\n"

            file.write(outStr)
            file.flush()

            matrixSize *= 2


if __name__ == '__main__':
    main()
