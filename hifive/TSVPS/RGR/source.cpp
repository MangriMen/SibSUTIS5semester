#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

typedef size_t T_town;
typedef vector<T_town> T_path_val;
typedef vector<int> T_row;
typedef vector<T_row> T_matr;
typedef set<T_town> T_towns;

class T_path
{
    T_matr dist_matr_;

    T_path_val currentPath;
    int currentPathLen;

    T_path_val shortestPath;
    int shortestPathLen;

    T_towns freeTowns;

public:
    T_path(T_matr const &dist_matr) : dist_matr_(dist_matr), shortestPathLen(numeric_limits<int>::max()) {
        for (T_town t{}; t < dist_matr.size(); ++t) {
            freeTowns.insert(t);
        }

        push_town_with_delta_dist(0);
    }

    void find_shortest() {
        do {
            if (successfully_fill_better_path()) {
                shortestPath = currentPath;
                shortestPathLen = currentPathLen;
            }
        } while (successfully_inc_back_town());
    }

    void print_shortest() {
        cout << endl;

        for (auto town : shortestPath) {
            cout << town + 1 << '\t';
        }

        cout << endl;
    }

private:
    void push_town_with_delta_dist(T_town town, int delta_dist = 0) {
        currentPath.emplace_back(town);
        freeTowns.erase(town);
        currentPathLen += delta_dist;
    }

    bool successfully_fill_better_path() {
        while (!path_is_full() && successfully_push_min_good_town());

        return path_is_full();
    }

    bool path_is_full() {
        return currentPath.size() >= dist_matr_.size() + 1;
    }

    bool successfully_push_min_good_town() {
        return currentPath.size() == dist_matr_.size()
                   ? successfully_push_good_town(0)
                   : successfully_push_good_min_free_town_not_less_than(0);
    }

    bool successfully_push_good_town(T_town town) {
        auto delta_dist = dist_matr_[currentPath.back()][town];

        bool bool_res = currentPathLen + delta_dist < shortestPathLen;

        if (bool_res) {
            push_town_with_delta_dist(town, delta_dist);
        }

        return bool_res;
    }

    bool successfully_push_good_min_free_town_not_less_than(T_town town_start) {
        for (auto i = freeTowns.lower_bound(town_start); i != freeTowns.end(); i++) {
            if (successfully_push_good_town(*i)) return true;
        }

        return false;
    }

    bool successfully_inc_back_town() {
        return currentPath.size() > 1
            && (successfully_push_good_min_free_town_not_less_than(pop_and_get_town() + 1) || successfully_inc_back_town());
    }

    //// what the fuck is this style
    //bool successfully_inc_back_town() {
    //    return currentPath.size() > 1

    //        && (successfully_push_good_min_free_town_not_less_than(
    //            pop_and_get_town() + 1)

    //            || successfully_inc_back_town());
    //}

    T_town pop_and_get_town() {
        auto back_town = currentPath.back();
        currentPath.pop_back();

        if (back_town) {
            freeTowns.insert(back_town);
        }

        auto penultimate_town = currentPath.back();

        currentPathLen -= dist_matr_[penultimate_town][back_town];

        return back_town;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int towns_total = 0;
    cout << "Enter towns (2 or more): ";
    cin >> towns_total;
    if (towns_total < 2) { return EXIT_FAILURE; }

    cout << "Enter distances between towns:" << endl;

    T_matr dist_matr(towns_total, T_row(towns_total));
    for (T_town L{}; L < T_town(towns_total); ++L) {
        for (T_town R{}; R < T_town(towns_total); ++R) {
            if (L == R) { continue; }
            cout << L + 1 << " to " << R + 1 << ":\t";
            cin >> dist_matr[L][R];
        }
    }

    T_path path(dist_matr);

    path.find_shortest();
    path.print_shortest();

    return EXIT_SUCCESS;
}