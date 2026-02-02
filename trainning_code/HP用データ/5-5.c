#include <stdio.h>
#include <time.h>

double vending_machine(int s, int a, int &sd);
double max_Qval(int s, int num_a, double** Qtable);
int select_action(int s, int num_a, double** Qtable);
int epsilon_greedy(int epsilon,int s, int num_a, double** Qtable);


int main()
{
	double **Qtable; //Qtable
	double Q_max=0;//Ｑ値の最大値
	double reward=0; //報酬
	double alpha=0.5;//学習係数
	double gamma=0.9;//減衰係数
	int epsilon=10;//行動を無作為に選ぶ確率[%]
	int trial_max=100;//試行回数
	//int step_max=10;//一試行において行動を選択する回数
	int num_a=2;//行動の数
	int num_s=2;//状態の数
	int a=0;//行動
	int s=0;//状態
	int sd=0;//行動の実行によって遷移する状態
	int i,j;
	
	
	//乱数の初期化
	srand( (unsigned)time( NULL ) );


	//メモリー空間の確保
	Qtable=new double*[num_s];
	for(i=0;i<num_s;i++){
		Qtable[i]=new double[num_a];
	}

	//Q値の初期化
	for(i=0;i<num_s;i++){
		for(j=0;j<num_a;j++){
			Qtable[i][j]=0;
			printf("Q[%d][%d]=%lf\n",i,j,Qtable[i][j]);
		}
	}

	
	//試行開始
	for(i=0;i<trial_max;i++){
	
		//行動の選択
		a=epsilon_greedy(epsilon,s,num_a,Qtable);
		//行動の実行
		reward=vending_machine(s,a,sd);
		//sdにおけるＱ値の最大値を求める
		Q_max=max_Qval(sd,num_a,Qtable);
		//Ｑ値の更新
		Qtable[s][a]=(1 - alpha) * Qtable[s][a] + alpha * (reward + gamma * Q_max);
		s=sd;

		printf("i=%d\n",i);
		if(reward>0){
           		 printf("成功\n",a);
		}
	
	}
	
	//Qtableの表示
	for(i=0;i<num_s;i++){
		for(j=0;j<num_a;j++){
			printf("%lf ",Qtable[i][j]);
		}
		printf("\n");
	}
	


	//メモリー空間の開放
	for(i=0;i<num_s;i++){
		delete[] Qtable[i];
	}
	delete[] Qtable;

	return 0;
}

double vending_machine(int s, int a, int &sd){
	double reward;

	if(a==0){
		sd=!s;
		reward=0;
	}
	else{
		if(s==1){
			sd=s;
			reward=10;
		}
		else{
			sd=s;
			reward=0;
		}
	}

	return reward;
}


double max_Qval(int s, int num_a, double** Qtable){
	double max;
	int i=0;
	
	max=Qtable[s][0];
	for(i=1;i<num_a;i++){
		if (Qtable[s][i]>max){
			max=Qtable[s][i];
		}
	}
	return max;
}

int select_action(int s, int num_a, double** Qtable){
	double max;
	int i=0;
	int* i_max = new int[num_a];
	int num_i_max=1;
	int a;

	i_max[0]=0;
	max=Qtable[s][0];

	for(i=1;i<num_a;i++){
		if (Qtable[s][i]>max){
			max=Qtable[s][i];
			num_i_max=1;
			i_max[0]=i;
		}
		else if(Qtable[s][i]==max){
			num_i_max++;
			i_max[num_i_max-1]=i;
		}
	}
	
	//for(i=0;i<num_i_max;i++){
	//	printf("i_max[%d]=%d\n",i,i_max[i]);
	//}
	
	a= i_max[rand()%num_i_max];
	return a;
}


int epsilon_greedy(int epsilon, int s, int num_a, double** Qtable){
	int a;
	if(epsilon > rand()%100){
		//無作為に行動を選択
		a=rand()%num_a;
		//printf("無作為に選択\n");
	}
	else{
		//最大のＱ値を持つ行動を選択
		a=select_action(s,num_a,Qtable);
		//printf("最大値をとる行動を選択\n");
	}
	return a;
}
		
