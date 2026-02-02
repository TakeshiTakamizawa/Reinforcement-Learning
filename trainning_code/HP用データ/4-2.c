#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calc_fitness(int individual, int length, int** population);

int main()
{
	
	int **population;//個体集合
	int num;//個体数
	int length;//遺伝子長
	int *fitness;//適合度 

	int i,j;
	

	num=10;
	length=5;
	//個体集合
	population=new int*[num];
	for(i=0;i<num;i++){
		population[i]=new int[length];
	}
	//適応度
	fitness=new int[num];

	//乱数の初期化
	srand( (unsigned)time( NULL ) );
	
	//初期個体の生成
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			population[i][j]=rand()%2;
			printf("%d ",population[i][j]);
		}
		
		fitness[i]=calc_fitness(i,length,population);
		printf(" fitness = %d\n",fitness[i]);
	}
	
	
	for(i=0;i<num;i++){
		delete[] population[i];
	}
	delete[] population;
	delete[] fitness;
	
	return 0;
}

int calc_fitness(int individual, int length, int** population){
	int i;
	int fitness =0;
	for(i=0;i<length;i++){
		fitness=fitness+population[individual][i];
	}
	return 10*fitness;

}
