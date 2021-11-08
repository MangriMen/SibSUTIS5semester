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
    int graph[SIZE][SIZE] = { 0 }; // матрица связей
    int minimalDistance[SIZE] = { INT_MAX }; // минимальное расстояние
    int visitedVertexes[SIZE] = { 1 }; // посещенные вершины
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
        { // Если вершину ещё не обошли и вес меньше minWeight
            if ((visitedVertexes[i] == 1) && (minimalDistance[i] < minWeight))
            { // Переприсваиваем значения
                minWeight = minimalDistance[i];
                minIndex = i;
            }
        }
        // Добавляем найденный минимальный вес к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
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

    // Восстановление пути
    int lastVertexIndex = 1; // индекс предыдущей вершины
    memset(visitedVertexes, 0, sizeof visitedVertexes);
    int endIndex = SIZE - 1; // индекс конечной вершины = 5 - 1
    int weight = minimalDistance[endIndex]; // вес конечной вершины
    visitedVertexes[0] = endIndex; // начальный элемент - конечная вершина

    while (endIndex != 0) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < SIZE; i++) // просматриваем все вершины
            if (graph[i][endIndex] != 0)   // если связь есть
            {
                int temp = weight - graph[i][endIndex]; // определяем вес пути из предыдущей вершины
                if (temp == minimalDistance[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    endIndex = i;       // сохраняем предыдущую вершину
                    visitedVertexes[lastVertexIndex] = i; // и записываем ее в массив
                    lastVertexIndex++;
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

    // (начальная вершина оказалась в конце массива из lastVertexIndex элементов)
    printf("\n\nShortest path:\n");
    for (int i = lastVertexIndex - 1; i >= 0; i--)
    {
        printf("%5d ", visitedVertexes[i]);
    }

    return 0;
}