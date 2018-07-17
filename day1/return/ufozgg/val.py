name = 'return'
def getline(in_f,cnt):
	line = in_f.readline()
	obj = line.split(' ')
	if cnt==0:
		assert(len(obj)==1 and obj[0]=='')
	else:
		assert(len(obj)==cnt)
	return obj

def getintline(in_f,cnt):
	obj = getline(in_f,cnt)
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

c1 = []
c2 = []
fa = []

def findfa(x):
	global fa
	d = [x]
	while fa[d[-1]] != d[-1]:
		d.append(fa[d[-1]])
		#print(fa[d[-1]],d[-1])
	for i in d:
		fa[i] = d[-1]
	return d[-1]
		
def check_g(n):
	global c1,c2,fa
	fa = [i for i in range(n+1)]
	for i in range(len(c1)):
		#assert(findfa(c1[i])!=findfa(c2[i]))
		fa[findfa(c1[i])] = fa[findfa(c2[i])]
	for i in range(1,n+1):
		assert(findfa(i)==findfa(1))

def check_in_file(in_f,out_f):
	global c1,c2
	[T] = getintline(in_f,1)
	assert(1<=T and T<=3)
	MAXN = 0
	MAXM = 0
	Qnum = -1
	MAXG = 2#2=line 1=tree 0=no -1=fail
	ATSAME = True
	Knum = -1
	for tt in range(T):
		c1 = []
		c2 = []
		[n,m] = getintline(in_f,2)
		if m != n - 1:
			MAXG = min(MAXG,0)
		assert(1<=n and n<=200000)
		#assert(1<=m)
		assert(m<=400000)
		MAXN = max(n,MAXN)
		MAXM = max(m,MAXM)
		for i in range(m):
			[u,v,l,a] = getintline(in_f,4)
			assert(1<=u and u<=n)
			assert(1<=v and v<=n)
			assert(1<=l and l<=10000)
			assert(1<=a and a<=1000000000)
			if u + 1 != v:
				MAXG = min(1,MAXG)
			if a != 1:
				ATSAME = False
			c1.append(u)
			c2.append(v)
		check_g(n)
		[Q,K,S] = getintline(in_f,3)
		assert(0<=Q and Q<=400000)
		assert(K == 0 or K == 1)
		assert(1<=S and S<=1000000000)
		if Qnum == -1:
			Qnum = Q
		else:
			assert(Qnum == Q)
		if Knum == -1:
			Knum = K
		else:
			assert(Knum == K)
		for i in range(Q):
			[v0,p0] = getintline(in_f,2)
			assert(1<=v0<=n)
			assert(0<=p0<=S)
	getline(in_f,0)
	print("%d\t%d\t%d\t%d\t%d\t%d"%(MAXN,MAXM,Qnum,MAXG,ATSAME,Knum))
		

for i in range(1,21):
	print('Check data %d'%i)
	in_f=open('../data/%d.in'%i,'r')
	out_f=open('../data/%d.ans'%i,'r')
	if i not in []:
		check_in_file(in_f,out_f)
	in_f.close()
	out_f.close()
for i in range(1,6):
	print('Check sample %d'%i)
	in_f=open('../down/%d.in'%i,'r')
	out_f=open('../down/%d.ans'%i,'r')
	check_in_file(in_f,out_f)
	in_f.close()
	out_f.close()