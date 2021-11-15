#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define SIZE 5

using namespace std;

int setDistanceI(int graph[SIZE][SIZE], int i, int j, int distance)
{
	graph[i][j] = distance;
	graph[j][i] = distance;

	return 0;
}

int main()
{
	int graph[SIZE][SIZE] = {0};
	int minimalDistance[SIZE] = {0};
	int visitedVertexes[SIZE] = {0};
	int temp, minIndex, min;
	int beginIndex = 0;

	system("chcp 1251");
	system("cls");

	setDistanceI(graph, 0, 1, 25);
	setDistanceI(graph, 0, 2, 15);
	setDistanceI(graph, 0, 3, 7);
	setDistanceI(graph, 0, 4, 2);
	setDistanceI(graph, 1, 2, 6);
	setDistanceI(graph, 1, 3, 11111);
	setDistanceI(graph, 1, 4, 11111);
	setDistanceI(graph, 2, 3, 4);
	setDistanceI(graph, 2, 4, 11111);
	setDistanceI(graph, 3, 4, 3);

	for (int i = 0; i < SIZE; i++)
	{
		minimalDistance[i] = 11111;
		visitedVertexes[i] = 1;
	}

	minimalDistance[beginIndex] = 0;
	do
	{
		minIndex = 11111;
		min = 11111;
		for (int i = 0; i < SIZE; i++)
		{
			if ((visitedVertexes[i] == 1) && (minimalDistance[i] < min))
			{
				min = minimalDistance[i];
				minIndex = i;
			}
		}
		if (minIndex != 11111)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (graph[minIndex][i] > 0)
				{
					temp = min + graph[minIndex][i];
					if (temp < minimalDistance[i])
					{
						minimalDistance[i] = temp;
					}
				}
			}
			visitedVertexes[minIndex] = 0;
		}
	} while (minIndex < 11111);

	int ver[SIZE];
	int end = 4;
	ver[0] = end;
	int k = 1;
	int weight = minimalDistance[end];

	while (end != beginIndex)
	{
		for (int i = 0; i < SIZE; i++)
			if (graph[i][end] != 0)
			{
				int temp = weight - graph[i][end];
				if (temp == minimalDistance[i])
				{
					weight = temp;
					end = i;
					ver[k] = i;
					k++;
				}
					cout << temp;
			}
		cout << endl;
	}

	int row = 0;
	int col = 0;

	printf("Adjacency matrix:\n");
	for (int i = -1; i < SIZE; i++)
	{
		for (int j = -1; j < SIZE; j++)
		{
			if (i == -1 && j == -1) {
				printf("\t%c", ' ');
			}
			else if (i == -1) {
				printf("\t%d", row++);
			}
			else if (j == -1) {
				printf("\t%d", col++);
			}
			else {
				if (graph[i][j] == 11111) {
					printf("\t%s", "inf");
				}
				else {
					printf("\t%d ", graph[i][j]);
				}
			}
		}
		printf("\n");
	}

	printf("\nShortest vertexes distances:\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("\t%d ", minimalDistance[i]);
	}

	printf("\n\nShortest path:\n");
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);

	return 0;
}