#include "TopK.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void Swap(HPDatatype* pLeft, HPDatatype* pRight) {
	HPDatatype tmp = *pLeft;
	*pLeft = *pRight;
	*pRight = tmp;
}

void HeapAdjust(int* array, int size, int parent) {
	int child = parent * 2 + 1;
	while (child < size) {
		if (child + 1 < size&&array[child + 1] < array[child])
			child += 1;
		if (array[parent] > array[child]) {
			Swap(&array[parent], &array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}


void HeapTopk(int*str, int K, int N) {
	int* array = (int*)malloc(sizeof(int)*K);
	if (array == NULL) {
		assert(0);
		return;
	}
	for (int i = 0; i < K; ++i) {
		array[i] = str[i];
	}

	//找倒数第一个非叶子节点
	int root = ((K - 2) >> 1);
	for (; root >= 0; --root)
		HeapAdjust(array, K, root);

	for (int i = 0; i < N - K; ++i) {
		if (array[0] < str[K + i]) {
			array[0] = str[K + i];
			HeapAdjust(array, K, 0);
		}
	}

}

int main() {
	int str[] = { 2,7,9,12,3,6,1,5,4,10 };
	HeapTopk(str, 4, sizeof(str) / sizeof(str[0]));
}