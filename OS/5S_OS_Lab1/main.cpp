#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Student
{
private:
	string name;
	int mark;

public:
	Student(string name, int mark = 0)
	{
		this->name = name;
		this->mark = mark;
	}

	string getName()
	{
		return name;
	}

	int getMark()
	{
		return mark;
	}

	void setName(string name_)
	{
		name = name_;
	}

	void setMark(int mark_)
	{
		mark = mark_;
	}

	void write(ostream &file)
	{
		size_t nameSize = name.size();
		file.write(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
		file.write(reinterpret_cast<char *>(&name), nameSize);
		file.write(reinterpret_cast<char *>(&mark), sizeof(mark));
	}

	static Student read(istream &file)
	{
		Student temp("temp");
		size_t nameSize = 0;
		file.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
		file.read(reinterpret_cast<char *>(&temp.name), nameSize);
		file.read(reinterpret_cast<char *>(&temp.mark), sizeof(temp.mark));
		return temp;
	}

	friend std::ostream &operator<<(std::ostream &out, const Student &student);
};

std::ostream &operator<<(std::ostream &out, const Student &student)
{
	out << "Name: " << student.name << " Mark: " << student.mark;
	return out;
}

template <typename T>
class List
{
public:
	List() : head(nullptr) {}

	void push_front(T data)
	{
		size_++;
		Node *temp = new Node(data, nullptr, tail);

		if (head == nullptr)
		{
			head = tail = temp;
			return;
		}

		head->prev = temp;
		head = temp;
	}

	void push_back(T data)
	{
		size_++;
		Node *temp = new Node(data, nullptr, tail);

		cout << data;

		if (head == nullptr)
		{
			head = tail = temp;
			return;
		}

		tail->next = temp;
		tail = temp;
	}

	T pop_front()
	{
		if (head == nullptr)
		{
			throw std::out_of_range("List is empty");
		}
		size_--;

		Node *temp = head;
		T tempData = temp->data;
		head = head->next;
		head->prev = nullptr;
		delete temp;

		return tempData;
	}

	T pop_back()
	{
		if (tail == nullptr)
		{
			throw std::out_of_range("List is empty");
		}
		size_--;

		Node *temp = tail;
		T tempData = temp->data;

		tail = tail->prev;
		if (tail != nullptr)
		{
			tail->next = nullptr;
		}
		else
		{
			head = tail;
		}
		delete temp;

		return tempData;
	}

	void clear()
	{
		size_ = 0;
		while (head != nullptr)
		{
			pop_back();
		}
	}

	size_t size()
	{
		return size_;
	}

	T &operator[](const size_t index)
	{
		Node *temp = head;
		for (size_t i = 0; (temp->next != nullptr) && (i < index); i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}

	bool saveToFile(string filename)
	{
		ofstream file(filename, ios::out | ios::binary);

		if (!file.is_open())
		{
			return false;
		}

		Node *temp = head;
		while (temp->next != nullptr)
		{
			temp->data.write(file);
			temp = temp->next;
		}

		file.close();

		return true;
	}

	bool readFromFile(string filename)
	{
		ifstream file(filename, ios::in | ios::binary);

		if (!file.is_open())
		{
			return false;
		}

		while (!file.eof())
		{
			this->push_back(Student::read(file));
		}

		file.close();

		return true;
	}

public:
	class Node
	{
	public:
		T data;
		Node *next;
		Node *prev;

		Node(T data, Node *next = nullptr, Node *prev = nullptr) : data(data), next(next), prev(prev) {}
	};

private:
	Node *head = nullptr;
	Node *tail = nullptr;
	size_t size_ = 0;
};

int main()
{
	srand(time(NULL));
	List<Student> list;

	vector<string> names =
		{"Joffery Basis",
		 "Jio Basos",
		 "Jofry Basas",
		 "Jefry Bibos",
		 "Jeffry Basos",
		 "Jefry Bisis",
		 "Gefery Bizas",
		 "Jofo Bizis",
		 "Geff Bizos",
		 "Jofy Bibis",
		 "Jefion Benzos",
		 "Jofar Bisis",
		 "Gefery Bibos",
		 "Jefi Bizis",
		 "Jiry Bibos",
		 "Jeffery Basis",
		 "Jiery Bisis",
		 "Joffrington Bibis",
		 "Jofo Benzos",
		 "Jeff Bisos",
		 "Geffry Bezas",
		 "Geffery Bizos",
		 "Jefy Benzis",
		 "Joff Bibis",
		 "Jofry Basos",
		 "Jify Bizas",
		 "Geffrington Basas",
		 "Jefery Bisis",
		 "Joffi Basos",
		 "Gefy Bisas",
		 "Jeffrington Benzas",
		 "Jify Bezas",
		 "Joffery Bibos",
		 "Jeff Basis",
		 "Jefion Bibos",
		 "Jiery Bizos",
		 "Geffrington Bezos",
		 "Jofy Bisis",
		 "Jefar Basis",
		 "Jofar Bezis",
		 "Jefery Bizas",
		 "Gefry Basis",
		 "Jify Basas",
		 "Jefi Bibas",
		 "Jifi Bibas",
		 "Geffi Bibas",
		 "Jefar Benzas",
		 "Jefion Bisis",
		 "Geffrington Bezos",
		 "Jiery Basas"};

	for (size_t i = 0; i < names.size(); i++)
	{
		list.push_back(Student(names[i], rand() % 4 + 2));
	}

	for (size_t i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}

	cout << endl;

	if (!list.saveToFile("journal.bin"))
	{
		cout << "Failed to write list to file" << endl;
	}

	for (size_t i = 0; i < names.size() - 1; i++)
	{
		list.pop_back();
	}
	// list.clear();
	// list.pop_back();
	cout << endl
		 << "List cleaned"
		 << endl;

	if (!list.readFromFile("journal.bin"))
	{
		cout << "Failed to write list to file" << endl;
	}

	for (size_t i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}

	return 0;
}