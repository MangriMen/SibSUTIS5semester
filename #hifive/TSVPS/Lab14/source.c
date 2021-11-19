#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

int setDistance(int graph[SIZE][SIZE], int i, int j, int distance) {
    graph[i][j] = distance;
    graph[j][i] = distance;
    
    return 0;
}

int main()
{
    // Init
    int graph[SIZE][SIZE] = { 0 };
    int minimalDistance[SIZE] = { INT_MAX };
    int visitedVertexes[SIZE] = { 1 };
    int minIndex = INT_MAX;
    int minWeight = INT_MAX;

    minimalDistance[0] = 0;

    setDistance(graph, 0, 1, 25);
    setDistance(graph, 0, 2, 15);
    setDistance(graph, 0, 3, 7);
    setDistance(graph, 0, 4, 2);
    setDistance(graph, 1, 2, 6);
    setDistance(graph, 1, 3, 0);
    setDistance(graph, 1, 4, 0);
    setDistance(graph, 2, 3, 4);
    setDistance(graph, 2, 4, 0);
    setDistance(graph, 3, 4, 3);

    // Algorithm
    do {
        minIndex = INT_MAX;
        minWeight = INT_MAX;
        for (int i = 0; i < SIZE; i++)
        {
            if ((visitedVertexes[i] == 1) && (minimalDistance[i] < minWeight))
            { 
                minWeight = minimalDistance[i];
                minIndex = i;
            }
        }

        if (minIndex != INT_MAX)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (graph[minIndex][i] > 0)
                {
                    int tempSum = minWeight + graph[minIndex][i];
                    if (tempSum < minimalDistance[i])
                    {
                        minimalDistance[i] = tempSum;
                    }
                }
            }
            visitedVertexes[minIndex] = 0;
        }
    } while (minIndex < INT_MAX);

    memset(visitedVertexes, 0, sizeof visitedVertexes);
    int lastVertexIndex = 1;
    int endIndex = SIZE - 1;
    visitedVertexes[0] = endIndex + 1;
    int weight = minimalDistance[endIndex];

    while (endIndex != 0)
    {
        for (int i = 0; i < SIZE; i++) {
            if (graph[i][endIndex] != 0)
            {
                int temp = weight - graph[i][endIndex];
                if (temp == minimalDistance[i])
                {                
                    weight = temp;
                    endIndex = i;
                    visitedVertexes[lastVertexIndex] = i + 1;
                    lastVertexIndex++;
                    printf("%d\n", i);
                }
            }
        }
    }

    // Data print
    printf("Adjacency matrix:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%5d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("\nShortest vertexes distances:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%5d ", minimalDistance[i]);
    }

    printf("\n\nShortest path:\n");
    for (int i = lastVertexIndex - 1; i >= 0; i--)
    {
        printf("%5d ", visitedVertexes[i]);
    }

    return 0;
}