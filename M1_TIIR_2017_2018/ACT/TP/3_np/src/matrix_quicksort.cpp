#include "matrix_quicksort.h"

void quickSort(int arr[NB_MAX_TACHES][2], int left, int right) {
	
	int i = left, j = right;
	int tmp[NB_DIMENSION];
	int pivot = arr[(left + right) / 2][0];
	
	/* partition */
	while (i <= j) {
	      while (arr[i][0] < pivot)
	            i++;
	      while (arr[j][0] > pivot)
	            j--;
	      if (i <= j) {
	            tmp[0] = arr[i][0];
	            tmp[1] = arr[i][1];
	            arr[i][0] = arr[j][0];
	            arr[i][1] = arr[j][1];
	            arr[j][0] = tmp[0];
	            arr[j][1] = tmp[1];
	            i++;
	            j--;
	      }
	};
	
	/* recursion */
	if (left < j)
	      quickSort(arr, left, j);
	if (i < right)
	      quickSort(arr, i, right);
}
