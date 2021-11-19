#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

#define SIZE 5
#define inf 11111

int setDistanceI(int graph[SIZE][SIZE], int i, int j, int distance)
{
	graph[i][j] = distance;
	graph[j][i] = distance;

	return 0;
}

int main()
{
	system("chcp 1251");
	system("cls");

	int graph[SIZE][SIZE] = {0};
	int minimalDistance[SIZE] = {0};
	int visitedVertexes[SIZE] = {0};
	int temp, minIndex, min;
	int beginIndex = 0;

	vector<vector<string>> finalTable(SIZE, vector<string>(SIZE + 3, "-"));
	vector<string> tableHeader = {"S", "w", "D(w)"};
	for (size_t i = 0; i < SIZE - 1; i++)
	{
		tableHeader.push_back("D(" + to_string(i + 1) + ")");
	}
	finalTable.insert(finalTable.begin(), tableHeader);
	for (size_t i = 2; i <= SIZE; i++)
	{
		finalTable[i][1] = to_string(SIZE - i + 1);
	}

	setDistanceI(graph, 0, 1, 25);
	setDistanceI(graph, 0, 2, 15);
	setDistanceI(graph, 0, 3, 7);
	setDistanceI(graph, 0, 4, 2);
	setDistanceI(graph, 1, 2, 6);
	setDistanceI(graph, 1, 3, inf);
	setDistanceI(graph, 1, 4, inf);
	setDistanceI(graph, 2, 3, 4);
	setDistanceI(graph, 2, 4, inf);
	setDistanceI(graph, 3, 4, 3);

	for (size_t i = 0; i < SIZE; i++)
	{
		minimalDistance[i] = inf;
		visitedVertexes[i] = 1;
	}

	minimalDistance[beginIndex] = 0;
	int counterD = 0;
	string pathsS = "";

	do
	{
		minIndex = inf;
		min = inf;
		for (size_t i = 0; i < SIZE; i++)
		{
			if ((visitedVertexes[i] == 1) && (minimalDistance[i] < min))
			{
				min = minimalDistance[i];
				minIndex = i;
				if (i != 0)
				{
					finalTable[counterD][i + 2] = to_string(minimalDistance[i]);
					finalTable[counterD + 1][2] = to_string(minimalDistance[i]);
				}
			}
		}
		if (minIndex < inf)
		{
			for (size_t i = 0; i < SIZE; i++)
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

		counterD++;

		if (minIndex < inf)
		{
			pathsS += to_string(minIndex) + ",";
			finalTable[counterD][0] = pathsS;
		}
	} while (minIndex < inf);

	int ver[SIZE];
	int end = SIZE - 1;
	ver[0] = end;
	int k = 1;
	int weight = minimalDistance[end];

	while (end != beginIndex)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
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
			}
		}
	}

	for (size_t i = 0; i < SIZE + 1; i++)
	{
		for (size_t j = 0; j < tableHeader.size(); j++)
		{
			cout << setw(10) << finalTable[i][j];
		}
		cout << endl;
	}

	return 0;
}