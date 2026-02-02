#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calc_fitness(int individual, int length, int** population);
void roulette_selection(int num, int length, int** population, int *fitness);


int main()
{
	int **population;//個体集合
	int num;//個体数
	int length;//遺伝子長
	int *fitness;//適応度 

	int i,j,k;
	
	num=10;
	length=5;

	//個体集合
	population=new int*[num];
	for(i=0;i<num;i++){
		population[i]=new int[length];
	}

	//適合度
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
	
	for(k=0;k<10;k++){
		roulette_selection(num,length, population, fitness);

		for(i=0;i<num;i++){
			fitness[i]=calc_fitness(i,length,population);
			for(j=0;j<length;j++){
				printf("%d ",population[i][j]);
			}
			printf("%d \n", fitness[i]);
		}
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
	return fitness;

}

void roulette_selection(int num, int length, int **population, int *fitness){
	int i,j,k;
	int sum_fitness;//適応度の和が入る
	int **new_population;//選ばれた個体が入る
	double *roulette;//選択される確率が入る
	double *ac_roulette;//rouletteの積算値が入る
	double r;//ルーレットで使う乱数

	new_population=new int*[num];
	for(i=0;i<num;i++){
		new_population[i]=new int[length];
	}
	
	roulette=new double[num];
	ac_roulette=new double[num];

	//fitnessの和を求める
	sum_fitness=0;
	for(i=0;i<num;i++){
		sum_fitness=sum_fitness+fitness[i];
	}
	
	//ルーレットを作る
	roulette[0]=(double)fitness[0]/(double)sum_fitness;
	ac_roulette[0]=roulette[0];
	printf("roulette[%d]=%lf ac_roulette[%d]=%lf \n",0,roulette[0],0,ac_roulette[0]);
	for(i=1;i<num;i++){
		roulette[i]=(double)fitness[i]/(double)sum_fitness;
		ac_roulette[i]=ac_roulette[i-1]+roulette[i];
		printf("roulette[%d]=%lf ac_roulette[%d]=%lf \n",i,roulette[i],i,ac_roulette[i]);

	}

	//ルーレットを使って選択する
	for(i=0;i<num;i++){
		r=(double)rand()/(double)RAND_MAX;
		for(j=0;j<num;j++){
			if(r<=ac_roulette[j]){
				printf("r=%lf ac_roulette[%d]=%lf \n",r,j,ac_roulette[j]);
				for(k=0;k<length;k++){
					new_population[i][k]=population[j][k];
				}
				break;
			}
		}
	}

	//new_populationをpopulationにコピー
	for(i=0;i<num;i++){
		for(k=0;k<length;k++){
			population[i][k]=new_population[i][k];
		}
	}

	delete[] roulette;
	delete[] ac_roulette;

	for(i=0;i<num;i++){
		delete[] new_population[i];
	}

	delete[] new_population;

}
