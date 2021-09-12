#include <iostream>

using namespace std;

template <typename T>
class List {
public:
	List() {
		head = tail;
		cout << "List init" << endl;
	}

	~List() {
		clear();
	}

	void clear() {
		Node* temp = head;
		while (temp != nullptr) {
			pop_back();
		}
	}

	void push_back(T data) {
		Node temp = Node(data, nullptr, nullptr);
		if (tail == nullptr) {
			tail = &temp;
			if (head.next == nullptr) {
				head.next = tail;
			}
			return;
		}

		tail->next = &temp;
		temp.prev = tail;
		tail = &temp;
	}

	// void push_front() {

	// }

	T pop_back() {
		Node* temp = tail;
		tail = tail->prev;

		T tempData = temp->data;
		temp->prev = nullptr;
		delete temp;

		return tempData;
	}

	// T pop_front() {

	// }

	T& operator[] (const size_t index) {
		Node* temp = head;

		// for (size_t i = 0; i < index; i++) {
		// 	cout << temp->data << endl;
		// 	if (temp->next == nullptr) {
		// 		exit(-3);
		// 	}
		// 	temp = temp->next;
		// }

		return temp->data;
	}

	class Node {
	public:
		T data;
		Node* next;
		Node* prev;
		Node(T data, Node* next = nullptr, Node* prev = nullptr) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
};

int main()
{
	List<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	// list.push_back(1);


	cout << list[4];

	return 0;
}