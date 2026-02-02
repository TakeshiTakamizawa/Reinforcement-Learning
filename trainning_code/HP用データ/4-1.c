#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int **population;//ŒÂ‘ÌW‡
	int num;//ŒÂ‘Ì”
	int length;//ˆâ“`q’·
	int i,j;
	
	num = 10;
	length = 5;
	//ŒÂ‘ÌW‡
	population = new int*[num];
	for(i=0;i<num;i++){
		population[i] = new int[length];
	}

	//—”‚Ì‰Šú‰»
	srand( (unsigned)time( NULL ) );

	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			population[i][j] = rand()%2;
			printf("%d ",population[i][j]);
		}
		printf("\n");
	}

	
	for(i=0;i<num;i++){
		delete[] population[i];
	}
	delete[] population;

	return 0;
}
