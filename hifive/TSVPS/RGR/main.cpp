#include <iostream>
#include <list>
#include <utility>
#include <memory>
#include <cfloat>
#include <mutex>
#include <atomic>
#include "matrix.hpp"

#define B DBL_MAX

using namespace std;

class BruteforceSolver {
public:
    BruteforceSolver(const Matrix<double>& m);

    void solve();
    
    bool step();

    list<size_t> getSolution() const;
    double getRecord() const;

private:
    double cost(vector<size_t> solution) const;

    void candidateSolution(vector<size_t> solution);

    Matrix<double> _matrix;
   
    double _bestCost;

    list<size_t> _bestPath;

    vector<size_t> _lastPath;
};

BruteforceSolver::BruteforceSolver(const Matrix<double>& m) : _matrix(m), _bestCost(DBL_MAX) {
    _lastPath.resize(m.size());
    
    for (size_t i = 0; i < m.size(); ++i) {
        _lastPath[i] = i;
    }

    candidateSolution(_lastPath);
}

void BruteforceSolver::solve() {
    if (_matrix.size() <= 2) throw "Error: Matrix size is incorrect.";

    while (step()) {
        for (size_t i = 0; i < _lastPath.size(); ++i) {
            cout << _lastPath[i];
            if (i != _lastPath.size() - 1) {
                cout << " > ";
            }
        }
        cout << endl;
    }
}

bool BruteforceSolver::step() {
    size_t n = _lastPath.size() - 1;
    int j = n - 2;
    int k = n - 1;

    while (j != -1 && _lastPath[j] >= _lastPath[j + 1]) j--;
    
    if (j == -1) return false;

    while (_lastPath[j] >= _lastPath[k]) k--;

    swap(_lastPath[j], _lastPath[k]);

    int l = j + 1;
    int r = n - 1;
    
    while (l < r) {
        swap(_lastPath[l++], _lastPath[r--]);
    }
    
    candidateSolution(_lastPath);
 
    return true;
}

list<size_t> BruteforceSolver::getSolution() const {
    return _bestPath;
}

double BruteforceSolver::getRecord() const {
    return _bestCost;
}

double BruteforceSolver::cost(vector<size_t> solution) const {
    double result = 0;
    
    for (size_t i = 1; i < solution.size(); ++i) {
        result += _matrix(solution[i - 1], solution[i]);
    }
    
    result += _matrix(solution.back(), solution.front());
    
    return result;
}

void BruteforceSolver::candidateSolution(vector<size_t> solution) {
    double curCost = cost(solution);

    if (curCost >= _bestCost)  return;
    
    _bestCost = curCost;
    _bestPath.clear();

    for (const auto& iter : solution) {
        _bestPath.push_back(iter);
    }

    _bestPath.push_back(solution.front());
}

class BranchAndBound {
public:
    typedef list<pair<size_t, size_t>> arclist;

    BranchAndBound(const Matrix<double>& m, double record = B);

    void solve();

    list<size_t> getSolution() const;
    
    double getRecord() const;
   
    bool isSolved() const;

private:
    void handleMatrix(const Matrix<double>& m, const arclist& arcs, double bottomLimit);
    
    double cost(const arclist& arcs) const;
    
    void candidateSolution(const arclist& arcs);
    
    void addInfinity(Matrix<double>& m);

    double subtractFromMatrix(Matrix<double>& m) const;

    arclist findBestZeros(const Matrix<double>& matrix) const;
  
    static double getCoefficient(const Matrix<double>& m, size_t r, size_t c);

    void logPath(const arclist& path);

    unique_ptr<Matrix<double>> _sourceMatrix;

    double _bestCost;

    arclist _arcs;

    list<size_t> _bestPath;

    arclist _lastStep;

    double _infinity;
};

BranchAndBound::BranchAndBound(const Matrix<double>& m, double record)
    :_bestCost(record), _infinity(0) {
    _sourceMatrix = make_unique<Matrix<double>>(m);
    
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = i + 1; j < m.size(); j++) {
            _infinity += (m.item(i, j) + m.item(j, i));
        }
    }
    
    for (size_t i = 0; i < _sourceMatrix->size(); i++) {
        _sourceMatrix->item(i, i) = _infinity;
    }
}

void BranchAndBound::solve() {
    handleMatrix(*_sourceMatrix, arclist(), 0);
    _bestPath.push_back(0);
    
    while (!_arcs.empty()) {
        auto iter = _arcs.begin();

        while (iter != _arcs.end()) {
            if (iter->first == _bestPath.back()) {
                _bestPath.push_back(iter->second);
                iter = _arcs.erase(iter);
            } else {
                ++iter;
            }
        }
    }
}

list<size_t> BranchAndBound::getSolution() const {
    return _bestPath;
}

double BranchAndBound::getRecord() const {
    return _bestCost;
}

bool BranchAndBound::isSolved() const {
    return _bestPath.size() != 1;
}

void BranchAndBound::handleMatrix(const Matrix<double>& m, const arclist& path, double bottomLimit) {
    if (m.size() < 2) throw logic_error("Error: Matrix size is incorrect.");

    arclist temp(path);

    int i = int(m.item(0, 0) >= _infinity);
    temp.emplace_back(m.rowIndex(0), m.columnIndex(i));
    temp.emplace_back(m.rowIndex(1), m.columnIndex(1 - i));

  /*  list<size_t> tempPath;
    tempPath.push_back(0);

    while (!temp.empty()) {
        bool flag = false;
        auto iter = temp.begin();

        while (iter != temp.end()) {
            if (iter->first == tempPath.back()) {
                flag = true;
                tempPath.push_back(iter->second);
                iter = temp.erase(iter);
            }
            else {
                ++iter;
            }
        }
        
        if (!flag) {
            tempPath.push_back(temp.front().second);
            temp.erase(temp.begin());
        }
    }*/

    for (const auto& i : temp) {
        cout << "(" << i.first << " " << i.second << ")" << " ";
    }
    cout << endl;

    if (m.size() == 2) {
        logPath(path);
        int i = int(m.item(0, 0) >= _infinity);

        arclist result(path);
        
        result.emplace_back(m.rowIndex(0), m.columnIndex(i));
        result.emplace_back(m.rowIndex(1), m.columnIndex(1 - i));

        candidateSolution(result);
        return;
    }
    
    Matrix<double> matrix(m);
    
    bottomLimit += subtractFromMatrix(matrix);

    if (bottomLimit > _bestCost) {
        //cout << bottomLimit << endl;
        logPath(path);
        return;
    }

    auto zeros = findBestZeros(matrix);

    auto edge = zeros.front();
    auto newMatrix(matrix);
    newMatrix.removeRowColumn(edge.first, edge.second);
    auto newPath(path);
    newPath.emplace_back(matrix.rowIndex(edge.first),
        matrix.columnIndex(edge.second));
    addInfinity(newMatrix);
    handleMatrix(newMatrix, newPath, bottomLimit);

    newMatrix = matrix;
    newMatrix(edge.first, edge.second) = _infinity + 1;
    handleMatrix(newMatrix, path, bottomLimit);
}

double BranchAndBound::cost(const arclist& arcs) const {
    double result = 0;

    for (auto& iter : arcs) {
        result += _sourceMatrix->item(iter.first, iter.second);
    }

    return result;
}

void BranchAndBound::candidateSolution(const arclist& arcs) {
    double curCost;

    if (_bestCost < (curCost = cost(arcs))) {
        return;
    }
    
    _bestCost = curCost;
    _arcs = arcs;
}

void BranchAndBound::addInfinity(Matrix<double>& m) {
    vector<bool> infRow(m.size(), false), infColumn(m.size(), false);

    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m.size(); j++)
            if (m.item(i, j) == _infinity) {
                infRow[i] = true;
                infColumn[j] = true;
            }
    }
    
    size_t notInf;
    for (size_t i = 0; i < infRow.size(); i++) {
        if (!infRow[i]) {
            notInf = i;
            break;
        }
    }

    for (size_t j = 0; j < infColumn.size(); j++) {
        if (!infColumn[j]) {
            m.item(notInf, j) = _infinity;
            break;
        }
    }
}

double BranchAndBound::subtractFromMatrix(Matrix<double>& m) const {
    double substractSum = 0;
    vector<double> minRow(m.size(), DBL_MAX), minColumn(m.size(), DBL_MAX);

    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            if (m(i, j) < minRow[i]) {
                minRow[i] = m(i, j);
            }
        }

        for (size_t j = 0; j < m.size(); ++j) {
            if (m(i, j) < _infinity) {
                m(i, j) -= minRow[i];
            }
            
            if ((m(i, j) < minColumn[j])) {
                minColumn[j] = m(i, j);
            }
        }
    }

    for (size_t j = 0; j < m.size(); ++j) {
        for (size_t i = 0; i < m.size(); ++i) {
            if (m(i, j) < _infinity) {
                m(i, j) -= minColumn[j];
            }
        }
    }

    for (auto i : minRow) substractSum += i;
    for (auto i : minColumn) substractSum += i;

    return substractSum;
}

BranchAndBound::arclist BranchAndBound::findBestZeros(const Matrix<double>& matrix) const {
    arclist zeros;
    list<double> coeffList;

    double maxCoeff = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            if (!matrix(i, j)) {
                zeros.emplace_back(i, j);
                coeffList.push_back(getCoefficient(matrix, i, j));
                maxCoeff = max(maxCoeff, coeffList.back());
            }
        }
    }

    auto zIter = zeros.begin();
    auto cIter = coeffList.begin();
    while (zIter != zeros.end()) {
        if (*cIter != maxCoeff) {
            zIter = zeros.erase(zIter);
            cIter = coeffList.erase(cIter);
        }
        else {
            ++zIter;
            ++cIter;
        }
    }

    return zeros;
}

double BranchAndBound::getCoefficient(const Matrix<double>& m, size_t r, size_t c) {
    double rmin = DBL_MAX;
    double cmin = DBL_MAX;

    for (size_t i = 0; i < m.size(); ++i) {
        if (i != r) rmin = min(rmin, m(i, c));
        if (i != c) cmin = min(cmin, m(r, i));
    }

    return rmin + cmin;
}

void BranchAndBound::logPath(const BranchAndBound::arclist& path) {
    _lastStep = path;
}

const Matrix<double> getDistanceMatrix()  {
    vector<vector<double>> distMatr = {
        {B,  13, 7, 5, 2, 9},
        {8,  B,  4, 7, 5, B},
        {8,  7,  B, 3, 6, 2},
        {5,  8,  1, B, B, 1},
        {B,  6,  1, 4, B, 9},
        {10, B,  8, 3, 7, B }
    };

    Matrix<double> distances(distMatr.size());
    
    for (size_t i = 0; i < distMatr.size(); ++i) {
        for (size_t j = 0; j < distMatr[i].size(); j++) {
            distances(i, j) = distMatr[i][j];
        }
    }

    return distances;
}

int main() {
    const Matrix<double> matrix = getDistanceMatrix();

    BruteforceSolver *solve1 = new BruteforceSolver(matrix);
    solve1->solve();
    cout << "Bruteforce: " << endl;
    for (const auto& i : solve1->getSolution()) {
        cout << i << " ";
    }
    cout << endl << "Cost: "  << solve1->getRecord() << endl << endl;

    BranchAndBound* solve2 = new BranchAndBound(matrix);
    solve2->solve();
    cout << "Branches: " << endl;
    for (const auto& i : solve2->getSolution()) {
        cout << i << " ";
    }
    cout << endl << "Cost: " << solve2->getRecord();

    return EXIT_SUCCESS;
}