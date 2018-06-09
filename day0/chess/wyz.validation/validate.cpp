#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

void readEOLN(){
	char ch=inf.readChar();
	if (ch=='\n') return;
	ensuref(ch=='\r',"Expected EOLN!!!");
	inf.readEoln();
}

int main(int argc,char** argv){
	registerValidation();

	int index((argc>=3)?atoi(argv[2]):0);
	int mxn((argc>=4)?atoi(argv[3]):10);
	int mxm((argc>=5)?atoi(argv[4]):10);
	const int mxa(1e5);
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testcase#%d (%s)...",index,argv[1]);
	}
	
	int n=inf.readInt(1,mxn,"n");
	inf.readSpace();
	int m=inf.readInt(1,mxm,"m");
	readEOLN();

	for (int k=0;k<2;++k)for (int i=1;i<=n;++i)for (int j=1;j<=m;++j){
		inf.readInt(0,(k==1&&index%2==1)?0:mxa,format("%c[%d][%d]",'a'+k,i,j));
		if (j==m) readEOLN();
		else inf.readSpace();
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
