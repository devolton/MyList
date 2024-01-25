#pragma once

template <typename T>
class Element {
public:
	T data;
	Element<T>* pNext;
	Element<T>* pPrev;

	Element( T data = T(), Element<T>* pNext = nullptr,  Element<T>* pPrev = nullptr) {
		this->data = data;
		this->pNext = pNext;
		this->pPrev = pPrev;
	}
};
