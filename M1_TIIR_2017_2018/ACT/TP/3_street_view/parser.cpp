#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

FILE* input_sommets;
FILE* output_sommets;
FILE* output_arcs;

int s1,s2,dir,time,len,i;
double res = 0;
list<int> l_sommets;

int checkDup(int s) {
	for (list<int>::iterator it=l_sommets.begin(); it != l_sommets.end(); it++) {
		if (*it == s)
			return 1;
	}
	
	return 0;
}

int main() {
	
	
	input_sommets  = fopen("input_sommets.ini", "r");
	output_sommets = fopen ("out_sommets.txt","w");
	output_arcs    = fopen ("out_arcs.txt","w");
	
	if ( (input_sommets == NULL) || (output_sommets == NULL) || (output_arcs == NULL))
		exit(EXIT_FAILURE);
	
	i = 0;
	while (i < 17958) {
		fscanf (input_sommets, "%d %d %d %d %d", &s1, &s2, &dir, &time, &len);
		
		if (len < 10)
			res = len / 10;
		else if (len < 100)
			res = len / 100;
		else if (len < 1000)
			res = len / 1000;
		else
			exit(1);
		
		printf("%f\n",res);
		
		res += time;
		
		if (checkDup(s1) != 1) {
			l_sommets.push_back(s1);
			fprintf(output_sommets,"%d ",s1);
		}
		
		if (checkDup(s2) != 1) {
			l_sommets.push_back(s2);
			fprintf(output_sommets,"%d ",s2);
		}
		
		if (dir == 1) {
			fprintf(output_arcs,"%d  %d %d\n",s1,s2,res);
		}
		else {
			fprintf(output_arcs,"%d  %d %d\n",s1,s2,res);
			fprintf(output_arcs,"%d  %d %d\n",s2,s1,res);
		}
		
		i++;
		
		if (i==1000)
			printf("1000 ....\n");
		if (i==5000)
			printf("5000 ....\n");
		if (i==10000)
			printf("10000 ....\n");
		if (i==15000)
			printf("15000 ....\n");
	}

	
	fclose(input_sommets);
	fclose(output_sommets);
	fclose(output_arcs);
	
	exit(EXIT_SUCCESS);
}