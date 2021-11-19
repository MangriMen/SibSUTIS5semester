#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double unboundedKnapsack(
    int maxWeight,
    const vector<int> &items,
    const vector<double> &costs,
    vector<int> &itemsInBackpack,
    int min = -1)
{
    if (maxWeight < 0)
    {
        return 0;
    }

    vector<double> summ(items.size());
    vector<vector<int>> Faa(items.size(), vector<int>(summ.size()));

    itemsInBackpack.clear();
    itemsInBackpack.resize(items.size());
    itemsInBackpack.shrink_to_fit();

    size_t r = 0;

    for (size_t i = 0; i < summ.size(); i++)
    {
        summ[i] = (unboundedKnapsack(maxWeight - items[i], items, costs, Faa[i], static_cast<int>(i)));
        r += !summ[i];
    }

    if (r == summ.size())
    {
        itemsInBackpack[min]++;
        return costs[min];
    }
    else
    {
        r = max_element(summ.begin(), summ.end()) - summ.begin();
        if (min == -1)
        {
            Faa[r].swap(itemsInBackpack);
            return summ[r];
        }
        else
        {
            itemsInBackpack.swap(Faa[r]);
            itemsInBackpack[min]++;
            return summ[r] + costs[min];
        }
    }
}

void printItems(const vector<int> &items, const vector<double> &costs)
{
    for (size_t i = 0; i < items.size(); i++)
    {
        cout << "Item \"" << i + 1
             << "\""
             << "\n"
             << "\tWeight: " << items[i] << "\n"
             << "\tCost: " << costs[i]
             << "\n";
    }
    cout << "\n";
}

void printResult(int maxWeight, double maxCost, const vector<int> &itemsInBackpack)
{
    cout << "Maximum weight: "
         << maxWeight
         << "\n"
         << "Maximum cost: "
         << maxCost
         << "\n\n";

    for (size_t i = 0; i < itemsInBackpack.size(); i++)
    {
        cout << "Number of \""
             << i + 1
             << "\""
             << " is "
             << itemsInBackpack[i]
             << "\n";
    }
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned>(time(NULL)));

    int maxWeight = 0;

    vector<int> items;
    vector<double> costs;

    cout << "Enter the maximum weight capacity of the knapsack: ";
    cin >> maxWeight;
    cout << "\n";

    items.push_back(3);
    items.push_back(5);
    items.push_back(8);
    costs.push_back(8);
    costs.push_back(14);
    costs.push_back(23);

    printItems(items, costs);

    vector<int> itemsInBackpack;
    double maxCost = unboundedKnapsack(maxWeight, items, costs, itemsInBackpack);

    printResult(maxWeight, maxCost, itemsInBackpack);

    return EXIT_SUCCESS;
}