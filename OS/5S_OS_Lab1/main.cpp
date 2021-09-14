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

	friend bool operator==(const Student &A, const Student &B);

	friend ostream &operator<<(std::ostream &out, const Student &student);
};

ostream &operator<<(ostream &out, const Student &student)
{
	out << "Name: " << student.name << " Mark: " << student.mark;
	return out;
}

bool operator==(const Student &A, const Student &B)
{
	return (A.name == B.name);
}

template <typename T>
class List
{
public:
	List() : head(nullptr) {}
	~List()
	{
		clear();
	}

	void push_front(const T &data)
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

	void push_back(const T &data)
	{
		size_++;
		Node *temp = new Node(data, nullptr, tail);

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
		while (head != nullptr)
		{
			pop_back();
		}
	}

	size_t size()
	{
		return size_;
	}

	void insert(const T &data, const size_t index)
	{
		size_++;

		Node *temp = head;
		for (size_t i = 0; (temp->next != nullptr) && (i < index); i++)
		{
			temp = temp->next;
		}

		Node *newElement = new Node(data, temp->next, temp);

		temp->next->prev = newElement;
		temp->next = newElement;
	}

	T remove(const size_t index)
	{
		Node *temp = head;
		for (size_t i = 0; (temp->next != nullptr) && (i < index); i++)
		{
			temp = temp->next;
		}

		T tempData = temp->data;

		if (temp == head)
		{
			pop_front();
		}
		else if (temp == tail)
		{
			pop_back();
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			size_--;
			delete temp;
		}

		return tempData;
	}

	size_t find(const T &data)
	{
		Node *temp = head;
		for (size_t i = 0; temp->next != nullptr; i++)
		{
			if (data == temp->data)
			{
				return i;
			}
			temp = temp->next;
		}

		return string::npos;
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

	bool saveToFile(const string filename)
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

	names.resize(10);

	cout << "List size: " << list.size() << endl;
	cout << endl;

	for (size_t i = 0; i < names.size(); i++)
	{
		list.push_back(Student(names[i], rand() % 4 + 2));
	}

	for (size_t i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}

	cout << endl;
	cout << "List size: " << list.size() << endl;
	cout << endl;

	cout << "Removed element 0: " << list.remove(0) << endl;
	cout << endl;

	for (size_t i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}

	cout << endl;
	cout << "List size: " << list.size() << endl;

	list.insert(Student("Inserted boy", 10), 3);

	cout << endl;
	for (size_t i = 0; i < list.size(); i++)
	{
		cout << list[i] << endl;
	}
	cout << endl;
	cout << "List size: " << list.size() << endl;
	cout << endl;

	cout << "Searching for Inserted boy: ";
	size_t foundIndex = list.find(Student("Inserted boy"));
	if (foundIndex != string::npos)
	{
		cout << "Index: " << foundIndex;
	}
	else
	{
		cout << "Student not found";
	}
	cout << endl;

	if (!list.saveToFile("journal.bin"))
	{
		cout << "Failed to write list to file" << endl;
	}

	list.clear();

	cout << endl
		 << "List cleaned" << endl
		 << endl;

	cout << "List size: " << list.size() << endl;

	return 0;
}