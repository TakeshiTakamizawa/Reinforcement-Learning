#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pairing(int num, int length, int **population, int **pair);

int main()
{
	int **population;//個体集合
	int **pair;//個体集合を並べ替え，上から順にペアにしたもの
	int num;//個体数
	int length;//遺伝子長
	int i,j;
	
	num=10;
	length=5;
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

	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			population[i][j]=rand()%2;
			printf("%d ",population[i][j]);
		}
		printf("\n");
	}

	pairing(num,length,population,pair);
	
	for(i=0;i<num;i++){
		delete[] population[i];
		delete[] pair[i];
	}
	delete[] population;
	delete[] pair;
	
	return 0;
}

void pairing(int num, int length, int **population, int **pair){
	int *shuffle;//個体番号をいれ，シャッフルするための配列
	int r;//乱数
	int i,j;
	int temp;

	shuffle=new int[num];
	//初期化
	for(i=0;i<num;i++){
		shuffle[i]=i;
	}
	//シャッフル
	for(i=0;i<num;i++){
        r=rand()%num;
		temp=shuffle[r];
		shuffle[r]=shuffle[i];
		shuffle[i]=temp;
	}
	//shuffleの確認
	for(i=0;i<num;i++){
		printf("shuffle[%d]=%d\n",i,shuffle[i]);
	}
	//populationからペアをつくりpairにコピー
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			pair[i][j]=population[shuffle[i]][j];
		}
	}
	//確認
	for(i=0;i<num;i++){
		for(j=0;j<length;j++){
			printf("%d ",population[i][j]);
		}
		printf(">>> ");
		for(j=0;j<length;j++){
			printf("%d ",pair[i][j]);
		}
		printf("\n");
	}

}

