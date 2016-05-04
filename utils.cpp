#include "utils.h"
#include <stdlib.h>

void Array::Add(T item) {
	data_size++;
	data = (T*) realloc(data, sizeof(T) * data_size);
	date[data_size-1] = item;
}

T Array::Get(int index) {
	if(index < 0 || index >= data_size) {
		return NULL;
	}
	return data[index];
}

int Array::Length() {
	return data_size;
}
