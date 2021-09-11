#include <iostream>
#include <algorithm>
using namespace std;


void printLog(int arr[], int arrlength, string message) {
	cout << message << endl;
	for (int i = 0; i < arrlength; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << "====================" << endl;
}

void copyArray(int* arr, int* temp, int n) {
	for (int i = 0; i < n; i++) {
		temp[i] = arr[i];
	}
}

void merge(int* arr, size_t left, size_t middle, size_t right) {
	size_t blockIt = 0, blockIt2 = 0;
	int* temp = new int[right - left];

	while ((left + blockIt < middle) && (middle + blockIt2 < right)) {
		if (arr[left + blockIt] < arr[middle + blockIt2]) {
			temp[blockIt + blockIt2] = arr[left + blockIt];
			blockIt++;
		} else {
			temp[blockIt + blockIt2] = arr[middle + blockIt2];
			blockIt2++;
		}
	}
	
	for (; left + blockIt < middle; blockIt++) {
		temp[blockIt + blockIt2] = arr[left + blockIt];
	}

	for (; middle + blockIt2 < right; blockIt2++) {
		temp[blockIt + blockIt2] = arr[middle + blockIt2];
	}

	for (int i = 0; i < (blockIt + blockIt2); i++) {
		arr[left + i] = temp[i];
	}

	delete[] temp;
}

void mergeSort(int arr[], int n) {
	for (int i = 1; i < n; i *= 2) {
		for (int j = 0; j < n - i; j += 2 * i) {
			merge(arr, j, j + i, min(j + 2 * i, n));
		}
		cout << "Block " << i * 2 << ": ";
		printLog(arr, n, "inside Merge sort:");
	}
}

void bubbleSort(int arr[], size_t size) {
	bool isFinished = true;

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
				isFinished = false;
			}
		}

		if (isFinished) return;
	}
}

void selectSort(int arr[], size_t size) {
	int minimalElementIndex = 0;

	for (int i = 0; i < size - 1; i++) {
		minimalElementIndex = i;

		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[minimalElementIndex]) {
				minimalElementIndex = j;
			}
		}

		if (minimalElementIndex != i) {
			int swap = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = swap;
		}
	}
}

int main() {
	const int ARR_SIZE = 12;
	int* arrBubble = new int[ARR_SIZE];
	int* arrSelect = new int[ARR_SIZE];
	int* arrMerge = new int[ARR_SIZE];
	int* array = new int[ARR_SIZE] {1, 5, 2, 65, 7, 9, 68, 12, 12, 7, 43 , 73};
	
	memcpy(arrBubble, array, ARR_SIZE * sizeof(array[0]));
	memcpy(arrSelect, array, ARR_SIZE * sizeof(array[0]));
	memcpy(arrMerge, array, ARR_SIZE * sizeof(array[0]));

	printLog(array, ARR_SIZE, "Starting array:");

	bubbleSort(arrBubble, ARR_SIZE);
	printLog(arrBubble, ARR_SIZE, "Bubble sort:");

	selectSort(arrSelect, ARR_SIZE);
	printLog(arrSelect, ARR_SIZE, "Select sort:");

	mergeSort(arrMerge, ARR_SIZE);
	//printLog(arrMerge, ARR_SIZE, "Merge sort:");

	cout << endl << endl << endl << endl;

	delete[] arrBubble;
	delete[] arrSelect;
	delete[] arrMerge;

	return 0;
}
