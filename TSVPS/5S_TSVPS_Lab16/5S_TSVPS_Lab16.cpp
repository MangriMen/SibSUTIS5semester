#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum MethodType
{
	ExhausiveSearchRec,
	BranchAndBound
};

class Item
{
public:
	double weight, cost;

	Item(double weight = 1, double cost = 1)
	{
		weight = weight;
		cost = cost;
	}
};

class AbstractBackpack
{
public:
	double maxWeight;

	MethodType Method;

	AbstractBackpack(double maxWeight)
	{
		this->maxWeight = maxWeight;
	}

	double TotalCost(vector<Item>& items, vector<bool>& inBackpack)
	{
		double result = 0;
		for (int i = 0; i < items.size(); i++)
		{
			if (inBackpack[i])
				result += items[i].cost;
		}
		return result;
	}

	double TotalCost(vector<Item>& items, vector<unsigned>& inBackpack)
	{
		double result = 0;
		for (int i = 0; i < items.size(); i++)
			result += inBackpack[i] * items[i].cost;
		return result;
	}

	virtual vector<unsigned> SolveUnlimited(vector<Item>& items) = 0;

	double TotalWeight(vector<Item>& items, vector<bool>& inBackpack)
	{
		double result = 0;
		for (int i = 0; i < items.size(); i++)
		{
			if (inBackpack[i])
				result += items[i].weight;
		}
		return result;
	}

	double TotalWeight(vector<Item>& items, vector<unsigned>& inBackpack)
	{
		double result = 0;
		for (int i = 0; i < items.size(); i++)
			result += inBackpack[i] * items[i].weight;
		return result;
	}
};

class BranchAndBoundBackpack : public AbstractBackpack
{
public:
	class OrderedItem : public Item
	{
	public:
		int number;
		
		OrderedItem() {}

		OrderedItem(double w, double c, int i) : Item(w, c)
		{
			this->number = i;
		}
	};

	vector<bool> result;
	vector<Item> items;
	vector<unsigned> resultUnl;
	double maxCost;

	BranchAndBoundBackpack(double maxWeight = 100) : AbstractBackpack(maxWeight)
	{

	}

	//override MethodType Method
	//{
	//	get { return MethodType.BranchAndBound; }
	//}

	vector<unsigned> SolveUnlimited(vector<Item>& items)
	{
		auto defaultOrder = GetDefaultOrder(items);
		auto ordered(defaultOrder);
		auto kekF = [](OrderedItem const& s1, OrderedItem const& s2) -> bool
		{
			return static_cast<bool>(s1.cost / s1.weight);
		};
		sort(ordered.begin(), ordered.end(), kekF);
		//auto ordered = defaultOrder.OrderByDescending<OrderedItem, double>
		//	((i) = > i.cost / i.weight)
		//	.ToArray();
		for (size_t i = 0; i < this->items.size(); i++)
		{
			this->items[i] = ordered[i];
		}
		//this->items = ordered;
		maxCost = 0;
		resultUnl = vector<unsigned>(items.size());
		auto testVector = vector<unsigned>(items.size());
		SolveUnlimitedRec(testVector);
		return RestoreUnlimitedSolution(ordered);
	}

	/// <summary>
	/// Получает массив упорядоченных элементов.
	/// </summary>
	/// <param name="items">Массив неупорядоченных элементов.</param>
	/// <returns>Возвращает массив упорядоченных элементов.</returns>
	vector<OrderedItem> GetDefaultOrder(vector<Item>& items)
	{
		vector<OrderedItem> temp(items.size());
		for (int i = 0; i < items.size(); i++)
		{
			temp[i] = OrderedItem(items[i].weight, items[i].cost, i);
		}
		return temp;
	}
	/// <summary>
	/// Восстанавливает порядок решения, используя упорядоченную последовательность.
	/// </summary>
	/// <param name="items">Массив упорядоченных элементов.</param>
	/// <returns>Возвращает решене задачи.</returns>
	vector<bool> RestoreSolution(vector<OrderedItem>& items)
	{
		vector<bool> res(items.size());
		for (int i = 0; i < items.size(); i++)
		{
			res[items[i].number] = result[i];
		}
		return res;
	}
	/// <summary>
	/// Восстанавливает порядок решения, используя упорядоченную последовательность.
	/// </summary>
	/// <param name="items">Массив упорядоченных элементов.</param>
	/// <returns>Возвращает решене задачи.</returns>
	vector<unsigned> RestoreUnlimitedSolution(vector<OrderedItem>& items)
	{
		vector<unsigned> res(items.size());
		for (int i = 0; i < items.size(); i++)
		{
			res[items[i].number] = resultUnl[i];
		}
		return res;
	}

	/// <summary>
	/// Рекурсивная процедура решения задачи о неограниченном рюкзаке .
	/// </summary>
	/// <param name="vector">Проверяемое решение.</param>
	/// <param name="i">Номер проверяемого элемента решения.</param>
	/// <param name="c">Общая стоимость решения к текущему моменту.</param>
	/// <param name="w">Общий вес решения к текущему моменту.</param>
	void SolveUnlimitedRec(vector<unsigned>& vec, int i = 0, double c = 0, double w = 0)
	{
		if (i == vec.size()) //надо принять решение
		{
			//к этому шагу мы дойдём, только если вес рюкзака будет меньше допустимого, 
			//т.к. проверки выполняются до запуска ветви
			if (c > maxCost)
			{
				maxCost = c;
				//resultUnl = vec.
				//vec.CopyTo(resultUnl, 0);
			}
		}
		else
		{
			double oneMoreC = c + items[i].cost;
			double oneMoreW = w + items[i].weight;
			if (oneMoreW <= maxWeight) //не перебираем по весу
			{
				vec[i]++;
				//если оценка сверху больше масимальной стоимости
				if (CalculateUpperBound(oneMoreC, oneMoreW, i - 1) > maxCost)
					SolveUnlimitedRec(vec, i, oneMoreC, oneMoreW);
			}
			//если оценка сверху больше масимальной стоимости
			if (CalculateUpperBound(c, w, i) > maxCost) {
				SolveUnlimitedRec(vec, i + 1, c, w);
			}
			vec[i] = vec[i] > 0 ? vec[i] - 1 : 0;
		}
	}

	double CalculateUpperBound(double c, double w, int i)
	{
		double ub = c + (maxWeight - w) * ((i + 1 < items.size()) ?
			(items[i + 1].cost / items[i + 1].weight) : 0);
		return ub;
	}
};

int main()
{
	size_t backpackSize = 21;

	vector<Item> items(5);
	items[0] = Item(5, 10);
	items[1] = Item(10, 12);
	items[2] = Item(15, 22);
	items[3] = Item(7, 8);
	items[4] = Item(6, 14);

	AbstractBackpack* b = new BranchAndBoundBackpack(backpackSize);
	vector<unsigned> result = b->SolveUnlimited(items);
}