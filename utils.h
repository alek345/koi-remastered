#ifndef KOI_UTILS_H
#define KOI_UTILS_H

#include <stddef.h>

template<typename T>
struct Array {
	T* data = NULL;
	int data_size = 0;

	void Add(T item);
	T Get(int index);
	int Length();

	T operator[](int index) {
		if(index < 0 || index >= data_size) {
			return NULL;
		}
		return data[index];
	}
};

#endif /* KOI_UTILS_H */
