//#include <iostream>
//#include <vector>
//#include <string>
//#include <map>
//using namespace std;
//
//#define B 5555555
//
//int main() {
//    vector<vector<int>> towns = {
//        {B,  13, 7, 5, 2, 9},
//        {8,  B,  4, 7, 5, B},
//        {8,  7,  B, 3, 6, 2},
//        {5,  8,  1, B, B, 1},
//        {B,  6,  1, 4, B, 9},
//        {10, B,  8, 3, 7, B }
//    };
//
//    size_t graphSize = towns.size() - 1;
//
//    map<int, string> path;
//
//    int minDistance = INT_MAX;
//    int minIndex = 0;
//
//    int counter = 0;
//    for (long long i1 = 0; i1 <= graphSize; i1++) {
//        for (long long i2 = 0; i2 <= graphSize; i2++) {
//            for (long long i3 = 0; i3 <= graphSize; i3++) {
//                for (long long i4 = 0; i4 <= graphSize; i4++) {
//                    for (long long i5 = 0; i5 <= graphSize; i5++) {
//                        for (long long i6 = 0; i6 <= graphSize; i6++) {
//                            if (
//                                (i1 != i2) && (i1 != i3) && (i1 != i4) && (i1 != i5) && (i1 != i6) &&
//                                (i2 != i3) && (i2 != i4) && (i2 != i5) && (i2 != i6) &&
//                                (i3 != i4) && (i3 != i5) && (i3 != i6) &&
//                                (i4 != i5) && (i4 != i6) &&
//                                (i5 != i6)
//                                )
//                            {
//                                path[counter] = to_string(i1) + " > " + to_string(i2) + " > " + to_string(i3) + " > " + to_string(i4) + " > " + to_string(i5) + " > " + to_string(i6);
//                                //cout << path[counter] << "\n";
//
//                                if ((towns[i1][i2] + towns[i2][i3] + towns[i3][i4] + towns[i4][i5] + towns[i5][i6]) < minDistance) {
//                                    minDistance = towns[i1][i2] + towns[i2][i3] + towns[i3][i4] + towns[i4][i5] + towns[i5][i6];
//                                    //cout << minDistance << "\n";
//                                    minIndex = counter;
//                                }
//                                counter += 1;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        //cout << "\n";
//    }
//
//    cout << "Shortest way: " << path[minIndex] << "\nCost: " << minDistance;
//
//	return EXIT_SUCCESS;
//}