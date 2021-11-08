#include <iostream>
#include <vector>

using namespace std;

enum MethodType
{
	ExhausiveSearchRec,
	BranchAndBound
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

class BranchAndBoundBackpack : AbstractBackpack
{
public:
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
		auto ordered = defaultOrder.OrderByDescending<OrderedItem, double>((i) = > i.cost / i.weight).ToArray();
		this->items = ordered;
		maxCost = 0;
		resultUnl = vector<unsigned>(items.size());
		auto testVector = vector<unsigned>(items.size());
		SolveUnlimitedRec(testVector);
		return RestoreUnlimitedSolution(ordered);
	}

	/// <summary>
	/// �������� ������ ������������� ���������.
	/// </summary>
	/// <param name="items">������ ��������������� ���������.</param>
	/// <returns>���������� ������ ������������� ���������.</returns>
	vector<OrderedItem> GetDefaultOrder(vector<Item>& items)
	{
		auto temp = new OrderedItem[items.size()];
		for (int i = 0; i < items.size(); i++)
		{
			temp[i] = new OrderedItem(items[i].weight, items[i].cost, i);
		}
		return temp;
	}
	/// <summary>
	/// ��������������� ������� �������, ��������� ������������� ������������������.
	/// </summary>
	/// <param name="items">������ ������������� ���������.</param>
	/// <returns>���������� ������ ������.</returns>
	vector<bool> RestoreSolution(vector<OrderedItem>& items)
	{
		vector<bool>& res = new bool[items.size()];
		for (int i = 0; i < items.size(); i++)
		{
			res[items[i].Number] = result[i];
		}
		return res;
	}
	/// <summary>
	/// ��������������� ������� �������, ��������� ������������� ������������������.
	/// </summary>
	/// <param name="items">������ ������������� ���������.</param>
	/// <returns>���������� ������ ������.</returns>
	vector<unsigned> RestoreUnlimitedSolution(vector<OrderedItem>& items)
	{
		vector<unsigned>& res = new unsigned[items.size()];
		for (int i = 0; i < items.size(); i++)
		{
			res[items[i].Number] = resultUnl[i];
		}
		return res;
	}

	/// <summary>
	/// ����������� ��������� ������� ������ � �������������� ������� .
	/// </summary>
	/// <param name="vector">����������� �������.</param>
	/// <param name="i">����� ������������ �������� �������.</param>
	/// <param name="c">����� ��������� ������� � �������� �������.</param>
	/// <param name="w">����� ��� ������� � �������� �������.</param>
	private void SolveUnlimitedRec(vector<unsigned>& vec, int i = 0, double c = 0, double w = 0)
	{
		if (i == vec.size()) //���� ������� �������
		{
			//� ����� ���� �� �����, ������ ���� ��� ������� ����� ������ �����������, 
			//�.�. �������� ����������� �� ������� �����
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
			if (oneMoreW <= maxWeight) //�� ���������� �� ����
			{
				vector[i]++;
				//���� ������ ������ ������ ����������� ���������
				if (CalculateUpperBound(oneMoreC, oneMoreW, i - 1) > maxCost)
					SolveUnlimitedRec(vec, i, oneMoreC, oneMoreW);
			}
			//���� ������ ������ ������ ����������� ���������
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

	class OrderedItem : Item
	{
	public:
		int number;

		OrderedItem(double w, double c, int i) : Item(w, c)
		{
			this->number = i;
		}
	};
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

int main()
{
	size_t backpackSize = 21;

	vector<Item> items(5);
	items[0] = Item(5, 10);
	items[1] = Item(10, 12);
	items[2] = Item(15, 22);
	items[3] = Item(7, 8);
	items[4] = Item(6, 14);

	AbstractBackpack b = BranchAndBoundBackpack(backpackSize);
	usigned[] result = b.SolveUnlimited(task.Item1);
}