#pragma once
#include <iostream>
#include "Element.h"

template<typename T>
class List {
private:
	Element<T>* head = nullptr;
	Element<T>* tail = nullptr;
	size_t size = 0;
public:
	List() {

	}

	List(std::initializer_list<T> list) {
		head = new Element<T>(*list.begin());
		size++;
		tail = head;
		Element<T>* temp = head;
		for (T current : list) {
			if (current == *list.begin()) {
				continue;
			}
			temp->pNext = new Element<T>(current, nullptr, temp);
			tail = temp->pNext;
			size++;
			temp = temp->pNext;
		}

	}



	List(const List& other) {
		if (other.head == nullptr) return;
		head = new Element<T>(other.head->data);
		tail = head;
		size++;
		Element<T>* temp = head;
		Element<T>* otherTemp = other.head->pNext;
		while (otherTemp != nullptr) {
			temp->pNext = new Element<T>(otherTemp->data, nullptr, temp);
			tail = temp->pNext;
			temp = temp->pNext;
			otherTemp = otherTemp->pNext;
			size++;

		}
	}


	size_t GetSize() {
		return size;
	}

	T& Back() {
		return tail->data;
	}
	T& Front() {
		return this->head->data;
	 }
	void PushFront(const T data) {
		size++;
		if (head == nullptr) {
			head = new Element<T>(data);
			tail = head;
			return;
		}
		Element<T>* temp = head;
		head = new Element<T>(data, temp);
		temp->pPrev = head;



	}
	void PopFront() {
		if (head == nullptr) return;
		size--;
		if (head->pNext == nullptr) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Element<T>* temp = head->pNext;
			delete head;
			head = temp;
			head->pPrev = nullptr;
		}
	}

	void PushBack(const T data) {
		size++;
		if (tail == nullptr) {
			tail = new Element<T>(data);
			head = tail;
			return;
		}
		Element<T>* temp = tail;
		tail = new Element<T>(data, nullptr, temp);
		temp->pNext = tail;



	}

	void PopBack() {
		if (tail == nullptr) return;
		size--;
		if (tail->pPrev == nullptr) {
			delete tail;
			tail = nullptr;
			head = nullptr;
		}
		else {
			Element<T>* temp = tail->pPrev;
			delete tail;
			tail = temp;
			tail->pNext = nullptr;

		}
	}

	void Insert(const T data, const int index) {
		if (index > size || index < 0) {
			throw std::exception("Doubly Forward List out of range!");
		}

		if (index > size / 2) {
			if (index == size) {
				PushBack(data);
				return;
			}
			Element<T>* temp = tail;
			for (int i = 0; i < size - index - 1; i++) {
				temp = temp->pPrev;
			}
			Element<T>* forAdd = new Element<T>(data, temp, temp->pPrev);
			temp->pPrev = forAdd;
			forAdd->pPrev->pNext = forAdd;

		}
		else {
			if (index == 0) {
				PushFront(data);
				return;
			}
			Element<T>* temp = head;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->pNext;
			}
			Element<T>* forAdd = new Element<T>(data, temp->pNext, temp);
			temp->pNext = forAdd;
			forAdd->pNext->pPrev = forAdd;

		}
		size++;

	}

	void Remove(const int index) {
		if (index >= size || index < 0) {
			throw std::exception("Doubly Forward List out of range!");
		}
		if (index > size / 2) {
			if (index == size - 1) {
				PopBack();
				return;
			}
			Element<T>* temp = tail;
			for (int i = 0; i < size - index - 2; i++) {
				temp = temp->pPrev;
			}
			Element<T>* toDel = temp->pPrev;
			temp->pPrev = toDel->pPrev;
			toDel->pPrev->pNext = temp;
			delete toDel;


		}
		else {
			if (index == 0) {
				PopFront();
				return;
			}
			Element<T>* temp = head;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->pNext;
			}
			Element<T>* toDel = temp->pNext;
			temp->pNext = toDel->pNext;
			toDel->pNext->pPrev = temp;
			delete toDel;
		}
		size--;

	}

	int Search(const T data) const {
		if (head == nullptr) return -1;
		int forwardIndex = 0;
		int reverseIndex = size - 1;
		Element<T>* forwardTemp = head;
		Element<T>* reverseTemp = tail;
		while (forwardTemp != reverseTemp) {
			if (forwardTemp->data == data) {
				return forwardIndex;
			}
			if (reverseTemp->data == data) {
				return reverseIndex;
			}
			forwardTemp = forwardTemp->pNext;
			reverseTemp = reverseTemp->pPrev;
			forwardIndex++;
			reverseIndex--;
		}
		if (forwardTemp->data == data) {
			return forwardIndex;
		}
		return -1;
	}

	void Replace(const T data, const int index) {
		if (index >= size || index < 0) {
			throw std::exception("Doubly Forwars List out of range!");
		}
		if (index > size / 2) {
			Element<T>* temp = tail;
			for (int i = 0; i < size - index - 1; i++) {
				temp = temp->pPrev;
			}
			temp->data = data;
		}
		else {
			Element<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->pNext;
			}
			temp->data = data;
		}

	}

	void Print() const {
		if (head == nullptr) return;
		Element<T>* temp = head;
		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->pNext;
		}
		std::cout << std::endl;
	}

	void ReversePrint() const {
		if (tail == nullptr) return;
		Element<T>* temp = tail;
		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->pPrev;
		}
		std::cout << std::endl;
	}

	void AscendingSort() {
		if (head == nullptr || head->pNext == nullptr) return;
		Element<T>* temp = head;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (temp->data > temp->pNext->data) {
					std::swap(temp->data, temp->pNext->data);
				}
				temp = temp->pNext;
			}
			temp = head;
		}
	}

	void DescendingSort() {
		if (head == nullptr || tail == nullptr) return;
		Element<T>* temp = head;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (temp->data < temp->pNext->data) {
					std::swap(temp->data, temp->pNext->data);
				}
				temp = temp->pNext;
			}
			temp = head;
		}
	}


	void Erase(const int index, const int quantity) {
		if (index >= size || index<0 || quantity <= 0 || quantity > size - index) {
			throw std::exception("Doubly forward list out of range!");
		}

		if (index > size / 2) {
			Element<T>* temp = tail;
			for (int i = 0; i < size - index - 1 - quantity; i++) {
				temp = temp->pPrev;
			}
			for (int i = 0; i < quantity; i++) {
				if (temp == tail) {
					temp = temp->pPrev;
					PopBack();
					continue;
				}
				if (temp == head) {
					PopFront();
					break;
				}
				Element<T>* toDel = temp;
				temp->pPrev->pNext = toDel->pNext;
				temp->pNext->pPrev = toDel->pPrev;
				temp = temp->pPrev;
				delete toDel;
				size--;
			}
		}

		else {
			Element<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->pNext;
			}
			for (int i = 0; i < quantity; i++) {
				if (temp == head) {
					temp = temp->pNext;
					PopFront();

					continue;
				}
				if (temp == tail) {
					PopBack();
					break;
				}
				Element<T>* toDel = temp;
				temp->pNext->pPrev = temp->pPrev;
				temp->pPrev->pNext = temp->pNext;
				temp = temp->pNext;
				delete toDel;
				size--;
			}


		}
	}
	bool Empty() {
		return head == nullptr;
	}


	List SubList(const int index, const int quantity) {
		List<T> result;
		if (index >= size || index<0 || quantity <= 0 || quantity > size - index) {
			throw std::exception("Doubly forward list out of range!");
		}
		if (index > size / 2) {
			Element<T>* temp = tail;
			for (int i = 0; i < size - index - quantity; i++) {
				temp = temp->pPrev;
			}
			result.head = new Element<T>(temp->data);
			result.tail = result.head;
			result.size++;
			temp = temp->pPrev;
			for (int i = 0; i < quantity - 1; i++) {
				result.PushFront(temp->data);
				temp = temp->pPrev;
			}

		}
		else {
			Element<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->pNext;
			}
			result.head = new Element<T>(temp->data);
			result.tail = result.head;
			result.size++;
			temp = temp->pNext;
			for (int i = 0; i < quantity - 1; i++) {
				result.PushBack(temp->data);
				temp = temp->pNext;
			}
		}

		return result;

	}
	List& Merge(const List& other) {
		if (other.head == nullptr) {
			return *this;
		}
		if (this->head == nullptr) {
			this->head = new Element<T>(other.head->data);
			this->size++;
			this->tail = head;
			Element<T>* current = head;
			Element<T>* temp = other.head->pNext;
			while (temp != nullptr) {
				current->pNext = new Element<T>(temp->data, nullptr, current);
				this->tail = current->pNext;
				this->size++;
				current = current->pNext;
				temp = temp->pNext;
			}
			return *this;
		}
		Element<T>* current = this->tail;
		Element<T>* otherCurrent = other.head;
		while (otherCurrent != nullptr) {
			current->pNext = new Element<T>(otherCurrent->data, nullptr, current);
			this->tail = current;
			this->size++;
			current = current->pNext;
			otherCurrent = otherCurrent->pNext;
		}
		return *this;
		
	}
	void Clear() {
		if (head == nullptr) return;
		while (head != nullptr) {
			PopFront();
		}
	}
	void Reverse() {
		if (this->head == nullptr || this->head->pNext==nullptr) return;
		Element<T>* tempHead = head;
		Element<T>* tempTail = tail;
		while (tempHead != tempTail) {
			std::swap(tempHead->data, tempTail->data);
			tempHead = tempHead->pNext;
			if (tempHead == tempTail) {
				return;
			}
			tempTail = tempTail->pPrev;
		}

	
	}
	List& Assign(const List& other) {
		if (head == other.head) return *this;
		if (head != nullptr) {
			Clear();
		}
		head = new Element<T>(other.head->data);
		this->size++;
		Element<T>* temp = this->head;
		Element<T>* otherTemp = other.head->pNext;
		while (otherTemp != nullptr) {
			temp->pNext = new Element<T>(otherTemp->data, nullptr, temp);
			this->tail = temp->pNext;
			this->size++;
			temp = temp->pNext;
			otherTemp = otherTemp->pNext;
		}
		return *this;
	
	}
	void Resize(const int quantity, T& value=T()) {
		if (quantity < 0) {
			throw std::exception("Quantity is incorrect!");
		}
		if (quantity == this->size) return;
		if (quantity > this->size) {
			while (quantity != size) {
				PushBack(value);
			}
		}
		else if (quantity < this->size) {
			while (quantity != size) {
				PopBack();
		}
		}
	}
	T& operator[](const int index) {
		if (index >= size || index < 0) {
			throw std::exception("Doubly Forward List out of range!");
		}
		if (index > size / 2) {
			Element<T>* temp = tail;
			size_t counter = size - 1;
			while (temp != nullptr) {
				if (counter == index) {
					return temp->data;
				}
				temp = temp->pPrev;
				counter--;
			}

		}
		else {
			Element<T>* temp = head;
			size_t counter = 0;
			while (temp != nullptr) {
				if (counter == index) {
					return temp->data;
				}
				temp = temp->pNext;
				counter++;
			}
		}

	}

	List operator +(const List& other) {
		List<T> result;
		if (this->head == nullptr && other.head == nullptr) return result;
		result.head = new Element<T>(this->head->data);
		result.size++;
		Element<T>* temp = result.head;
		Element<T>* thisTemp = this->head->pNext;
		while (thisTemp != nullptr) {
			temp->pNext = new Element<T>(thisTemp->data, nullptr, temp);
			result.tail = temp->pNext;
			result.size++;
			temp = temp->pNext;
			thisTemp = thisTemp->pNext;
		}
		thisTemp = other.head;
		while (thisTemp != nullptr) {
			temp->pNext = new Element<T>(thisTemp->data, nullptr, temp);
			result.tail = temp->pNext;
			result.size++;
			temp = temp->pNext;
			thisTemp = thisTemp->pNext;
		}

		return result;
	}

	List& operator=(const List& other) {
		if (head == other.head) return *this;
		if (head != nullptr) {
			Clear();
		}
		head = new Element<T>(other.head->data);
		size++;
		Element<T>* temp = head;
		Element<T>* otherTemp = other.head->pNext;
		while (otherTemp != nullptr) {
			temp->pNext = new Element<T>(otherTemp->data, nullptr, temp);
			tail = temp->pNext;
			temp = temp->pNext;
			otherTemp = otherTemp->pNext;
			size++;
		}
		return *this;
	}

	bool operator ==(const List& other) {
		if (this->size != other.size) return false;
		Element<T>* forwardTemp = head;
		Element<T>* forwardOtherTemp = other.head;
		Element<T>* reverseTemp = tail;
		Element<T>* reverseOtherTemp = other.tail;
		while (forwardTemp != reverseTemp) {
			if (forwardTemp->data != forwardOtherTemp->data) {
				return false;
			}
			if (reverseTemp->data != reverseOtherTemp->data) {
				return false;
			}
			forwardTemp = forwardTemp->pNext;
			forwardOtherTemp = forwardOtherTemp->pNext;
			reverseTemp = reverseTemp->pPrev;
			reverseOtherTemp = reverseOtherTemp->pPrev;
		}
		if (forwardTemp->data != forwardOtherTemp->data) {
			return false;
		}
		return true;
	}

	bool operator !=(const List& other) {
		if (this->size != other.size) return true;
		Element<T>* forwardTemp = this->head;
		Element<T>* forwardOtherTemp = other.head;
		Element<T>* reverseTemp = this->tail;
		Element<T>* reverseOtherTemp = other.tail;
		while (forwardTemp != reverseTemp) {
			if (forwardTemp->data != forwardOtherTemp->data) {
				return true;
			}
			if (reverseTemp->data != reverseOtherTemp->data) {
				return true;
			}
			forwardTemp = forwardTemp->pNext;
			forwardOtherTemp = forwardOtherTemp->pNext;
			reverseTemp = reverseTemp->pPrev;
			reverseOtherTemp = reverseOtherTemp->pPrev;
		}
		if (forwardTemp->data != forwardOtherTemp->data) {
			return true;
		}
		return false;
	}

	class Iterator {
	private:
		std::unique_ptr<T> _ptr;
	public:
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator_category = std::bidirectional_iterator_tag;
		Iterator() {

		}
		Iterator(pointer ptr): _ptr(ptr){}
		Iterator& operator =(pointer ptr) {
			_ptr = ptr;
			return _ptr;
		}
		Iterator& operator++() {
			++_ptr;
			return *this;
		}
		reference operator *() {
			return *_ptr;
		}
	};
	Element<T>* Begin() {
		return head;
	}



	~List() {
		Clear();
	}
};
