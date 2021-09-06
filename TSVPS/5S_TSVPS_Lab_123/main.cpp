#include <iostream>
#include <vector>
#include <string>

using namespace std;

string input(string str) {
	string temp;
	cout << endl << str;
	cin >> temp;
	return temp;
}

template <typename T>
void fillRand(vector<T>& arr, size_t size) {
	arr.clear();
	for (size_t i = 0; i < size; i++) {
		arr.push_back(rand() % (size * size) - size);
	}
}

template <typename T>
void printArr(const vector<T>& arr) {
	for (const auto& i : arr) {
		cout << i << " ";
	}
}

template <typename T>
void printArrWithTitle(string message, const vector<T>& arr) {
	cout << endl << message << endl;
	printArr(arr);
	cout << endl;
}

template <typename T>
void printArrWithTitleInline(string message, const vector<T>& arr) {
	cout << endl << message;
	printArr(arr);
}

template<typename T>
void arrcpy(vector<T>& a, vector<T>& b) {
	b.clear();
	for (const auto& i : a) {
		b.push_back(i);
	}
}

template<typename T>
vector<T> getcopy(const vector<T>& a) {
	vector<T> b;
	for (const auto& i : a) {
		b.push_back(i);
	}
	return b;
}

template <typename T>
void bubbleSort(vector<T>& arr) {
	bool isContinue = true;
	for (size_t i = 0; (i < arr.size() - 1) && isContinue; i++, isContinue = true) {
		for (size_t j = 0; j < arr.size() - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				isContinue = false;
			}
		}
	}
}

template<typename T>
void selectSort(vector<T>& arr)
{
	size_t min_ = 0;
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		min_ = i;
		for (size_t j = i + 1; j < arr.size(); j++) {
			if (arr[j] < arr[min_]) {
				min_ = j;
			}
		}

		swap(arr[min_], arr[i]);
	}
}

template<typename T>
void merge(vector<T>& arr, size_t left, size_t middle, size_t right) {
	size_t it1 = 0;
	size_t it2 = 0;
	vector<T> result(right - left, 0);

	while ((left + it1 < middle) && (middle + it2 < right)) {
		if (arr[left + it1] < arr[middle + it2]) {
			result[it1 + it2] = arr[left + it1];
			it1++;
		}
		else {
			result[it1 + it2] = arr[middle + it2];
			it2++;
		}
	}

	while (left + it1 < middle) {
		result[it1 + it2] = arr[left + it1];
		it1++;
	}

	while (middle + it2 < right) {
		result[it1 + it2] = arr[middle + it2];
		it2++;
	}

	for (size_t i = 0; i < (it1 + it2); i++) {
		arr[left + i] = result[i];
	}
}

template<typename T>
void mergeSort(vector<T>& arr) {
	cout << endl << "Merge sort steps" << endl;
	for (size_t i = 1; i < arr.size(); i *= 2) {
		for (size_t j = 0; j < arr.size() - i; j += 2 * i) {
			merge(arr, j, j + i, min(j + 2 * i, arr.size()));
		}
		printArrWithTitleInline(to_string(i * 2) + ": ", arr);
	}
	cout << endl;
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	vector<int> arr;
	size_t size = 0;

	try {
		size = stoi(input("Enter size: "));
	} catch(const std::exception& a) {
		cout << "Wrong input";
		return - 1;
	}

	fillRand(arr, size);
	printArrWithTitle("Original:", arr);

	vector<int> vectorBubble = getcopy(arr);
	vector<int> vectorSelect = getcopy(arr);
	vector<int> vectorMerge = getcopy(arr);

	bubbleSort(vectorBubble);
	printArrWithTitle("Bubble Sort:", vectorBubble);

	selectSort(vectorSelect);
	printArrWithTitle("Select Sort:", vectorSelect);

	printArrWithTitle("Original:", vectorMerge);
	mergeSort(vectorMerge);
	printArrWithTitle("Merge Sort:", vectorMerge);
}