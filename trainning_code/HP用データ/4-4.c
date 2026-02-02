#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mutation(int mutation_rate, int length, int individual, int **population);

int main()
{
	
	int **population;//個体集合
	int num;//個体数
	int length;//遺伝子長
	int mutation_rate; //突然変異確率[%]
	int i,j;
	
	num=10;
	length=5;
	mutation_rate=50;
	//個体集合
	population=new int*[num];
	for(i=0;i<num;i++){
		population[i]=new int[length];
	}

	//乱数の初期化
	srand( (unsigned)time( NULL ) );
	
	//テスト用に初期個体を設定
	printf("population=\n");
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			population[i][j]=i%2;
			printf("%d ",population[i][j]);
		}
		printf("\n");
	}
	
	//突然変異
	for(i=0;i<num;i++){
		mutation(mutation_rate,length,i,population);
	}
	
	//確認
	printf("population=\n");
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
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


void mutation(int mutation_rate, int length, 
int individual, int **population){
	int i;

	for(i=0;i<length;i++){
		if(mutation_rate > rand()%100){
			population[individual][i]=!population[individual][i];
		}
	}
}
