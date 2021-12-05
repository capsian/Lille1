#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;
	
	fp = fopen("input_street_view.ini", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	while ((read = getline(&line, &len, fp)) != -1) {
		if(i >= 11350)
			printf("%s", line);
		i++;
	}
	
	fclose(fp);
	
	if (line)
		free(line);
	
	exit(EXIT_SUCCESS);
}