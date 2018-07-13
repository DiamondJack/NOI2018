#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
int T=5,NUM;
int HP[100100];
int RE[100100];
int Pr[100100];
int ATK[100100];
int N,M;
void print()
{
	printf()
}
void gen2()
{
	N=1;
	M=100000;
	if(rand()%5==0)
	{
		
	}
	else
	{
		
	}
}
int main()
{
	int i,j;
	scanf("%d",&NUM);
	srand(675432+NUM);
	printf("%d",&T);
	for(i=1;i<=T;++i)
	{
		if(NUM<=2)
		{
			gen2();
			continue;
		}
		if(NUM<=4)
		{
			gen4();
			continue;
		}
		if(NUM<=6)
		{
			gen6();
			continue;
		}
		if(NUM<=8)
		{
			gen8();
			continue;
		}
		if(NUM<=10)
		{
			gent();
			continue;
		}
	}
	return 0;
} 
