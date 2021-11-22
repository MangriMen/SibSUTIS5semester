#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#define SIZE 5

using namespace std;

constexpr int INF = 11111;

int setDistanceI(int graph[SIZE][SIZE], int i, int j, int distance)
{
	graph[i][j] = distance;
	graph[j][i] = distance;

	return 0;
}

int main()
{
	int graph[SIZE][SIZE] = { 0 };
	int minimalDistance[SIZE] = { 0 };
	int visitedVertexes[SIZE] = { 0 };
	int temp = 0, minIndex = 0, min = 0;
	int beginIndex = 3;
	cin >> beginIndex;

	system("chcp 1251");
	system("cls");

	vector<vector<string>> finalTable(SIZE, vector<string>(SIZE + 3, "inf"));
	vector<string> tableHeader = { "S", "w", "D(w)" };
	for (size_t i = 0; i < SIZE; i++)
	{
		if (i != beginIndex) {
			tableHeader.push_back("D(" + to_string(i) + ")");
		}
	}
	finalTable.insert(finalTable.begin(), tableHeader);

	setDistanceI(graph, 0, 1, 25);
	setDistanceI(graph, 0, 2, 15);
	setDistanceI(graph, 0, 3, 7);
	setDistanceI(graph, 0, 4, 2);
	setDistanceI(graph, 1, 2, 6);
	setDistanceI(graph, 1, 3, INF);
	setDistanceI(graph, 1, 4, INF);
	setDistanceI(graph, 2, 3, 4);
	setDistanceI(graph, 2, 4, INF);
	setDistanceI(graph, 3, 4, 3);

	for (int i = 0; i < SIZE; i++)
	{
		minimalDistance[i] = INF;
		visitedVertexes[i] = 1;
	}

	minimalDistance[beginIndex] = 0;
	int counterD = 0;
	string pathsS = "";

	do
	{
		minIndex = INF;
		min = INF;
		for (int i = 0; i < SIZE; i++)
		{
			if ((visitedVertexes[i] == 1) && (minimalDistance[i] < min))
			{
				min = minimalDistance[i];
				minIndex = i;

				auto calculatedCol = find(finalTable[0].begin(), finalTable[0].end(), "D(" + to_string(i) + ")");
				if (calculatedCol != finalTable[0].end()) {
					size_t calculatedColInd = calculatedCol - finalTable[0].begin();

					string dist = to_string(minimalDistance[i]);

					finalTable[counterD][calculatedColInd] = dist;
					finalTable[counterD + 1][2] = dist;
				}
			}
			if ((visitedVertexes[i] == 1)) {
				if (counterD == 1 || minimalDistance[i] < min) {
					auto calculatedCol = find(finalTable[0].begin(), finalTable[0].end(), "D(" + to_string(i) + ")");
					if (calculatedCol != finalTable[0].end()) {
						size_t calculatedColInd = calculatedCol - finalTable[0].begin();

						string dist = to_string(minimalDistance[i]);
						dist = dist == to_string(INF) ? "inf" : dist;

						finalTable[counterD][calculatedColInd] = dist;
						finalTable[counterD + 1][2] = dist;
					}
				}
			}
		}
		if (minIndex != INF)
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

		counterD++;

		if (minIndex < INF)
		{
			pathsS += to_string(minIndex) + ",";
			finalTable[counterD][0] = pathsS;
			if (counterD > 1) {
				finalTable[counterD][1] = to_string(minIndex);
			}

			auto calculatedCol = find(finalTable[0].begin(), finalTable[0].end(), "D(" + to_string(minIndex) + ")");
			size_t calculatedColInd = calculatedCol - finalTable[0].begin();
			for (size_t i = counterD; i < finalTable.size(); i++) {
				finalTable[i][calculatedColInd] = "-";
			}
		}
	} while (minIndex < INF);

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
				//cout << temp;
			}
		//cout << endl;
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
				if (graph[i][j] == INF) {
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

	cout << "\n" << "\n" << "Table" << "\n";

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