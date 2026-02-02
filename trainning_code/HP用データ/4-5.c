#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void one_point_crossover(int crossover_rate,int num, int length, int **population, int **pair);

int main()
{
	int **population;//個体集合
	int **pair;//個体集合を並べ替え，上から順にペアにしたもの
	int num;//個体数
	int length;//遺伝子長
	int crossover_rate; //突然変異率[%]
	int i,j;
	
	num=10;
	length=5;
	crossover_rate=50;
	//個体集合
	population=new int*[num];
	for(i=0;i<num;i++){
		population[i]=new int[length];
	}

	pair=new int*[num];
	for(i=0;i<num;i++){
		pair[i]=new int[length];
	}

	
	//乱数の初期化
	srand( (unsigned)time( NULL ) );
	
	//テスト用に初期個体を全て０に設定
	printf("population=\n");
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			population[i][j]=0;
			printf("%d ",population[i][j]);
		}
		printf("\n");
	}
	//テスト用にpairを設定（偶数番目の個体はには全て０を，奇数番目の個体には全て１を設定
	printf("pair=\n");
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			pair[i][j]=i%2;
			printf("%d ",pair[i][j]);
		}
		printf("\n");
	}

	one_point_crossover(crossover_rate,num,length,population, pair);
	
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
		delete[] pair[i];
	}
	delete[] population;
	delete[] pair;
	
	return 0;
}

void one_point_crossover(int crossover_rate,int num, int length, int **population, int **pair){
	int i,j;
	int cross_point;
	
	for(i=0;i<(num-1);i=i+2){
		if(rand()%100 < crossover_rate){
			//交叉実行
			cross_point=rand()%(length-1)+1;
			printf("cross_point=%d \n",cross_point);
			for(j=0;j<cross_point;j++){
				population[i][j]=pair[i+1][j];
				population[i+1][j]=pair[i][j];
			}
			for(j=cross_point;j<length;j++){
				population[i][j]=pair[i][j];
				population[i+1][j]=pair[i+1][j];
			}

		}
		else{
			//交叉を行わず，そのまま，pairをpopulationにコピー
			for(j=0;j<length;j++){
				population[i][j]=pair[i][j];
				population[i+1][j]=pair[i+1][j];
			}
		}
	}
}
