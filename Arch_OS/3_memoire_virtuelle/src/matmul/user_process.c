#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/matmul/matrix.h"
#include "../../include/hardware.h"
#include "../../include/1/mmu.h"

#define MATRIX_OP MATRIX_ADD
/*#define MATRIX_OP MATRIX_MUL*/

void user_process() {

	unsigned short timestamp = (unsigned)time(NULL);
	matrix *matrix1 = (matrix*)virtual_memory;
	matrix *matrix2 = ((matrix*)virtual_memory) + 1;
	matrix *matrix3 = ((matrix*)virtual_memory) + 2;

	srand(timestamp);

	printf("[Starting user process]\n");

	 /*print some informations*/
	printf("matrices size: %dx%d\n", MATRIX_SIZE, MATRIX_SIZE);
	printf("vm used: %5d pages\n", 3 * sizeof(matrix) / PAGE_SIZE);
	printf("pm space: %5d pages\n", 1 << 8);
	printf("vm space: %5d pages\n", 1 << 12);
	 /*init matrices*/
	printf("initializing matrices\n");
	matrix_init(matrix1);
	matrix_init(matrix2);
#if MATRIX_OP == MATRIX_ADD
	 /*add matrices*/
	printf("adding VM matrices ");fflush(stdout);
	matrix_add(matrix3, matrix1, matrix2);
#elif MATRIX_OP == MATRIX_MUL
	 /*multiply matrices*/
	printf("multiplying matrices ");fflush(stdout);
	matrix_mult(matrix3, matrix1, matrix2);
#endif
	printf("timestamp: 0x%04x, ", timestamp);
	printf("operation: %d, ", MATRIX_OP);
	printf("checksum: 0x%04x\n", matrix_checksum(matrix3));
}

