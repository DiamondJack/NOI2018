name='faceless'
def get_line(in_f,num=1):
	line = in_f.readline()
	obj = line.split(' ')
	if len(obj) != num and -1 != num:
		print('ERROR')
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

def check_in_file(in_f):
	[n] = get_line(in_f)
	m = get_line(in_f,n)
	[Q] = get_line(in_f)
	C = 0
	UVEQ = True
	PEQ = True
	M1 = True
	u0 = -1
	v0 = -1
	for i in range(n):
		if m[i]!=1:
			M1 = False
		assert(0<m[i] and m[i]<=100)
	for i in range(Q):
		L = get_line(in_f,-1)
		assert(len(L)>0)
		if L[0] == 0:
			assert(len(L)==4)
			[t0,id,u,v]=L
			if u!=v:
				UVEQ = False
			assert(1 <= id and id <= n)
			assert(0<u and u<=v and v <= 998244353)
			if u0 == -1:
				u0 = u
				v0 = v
			if u0!=u or v0!=v:
				PEQ = False
		else:
			assert(L[0]==1)
			assert(len(L)>2)
			assert(len(L)==2+L[1])
			app = [0 for s in range(n+1)]
			for j in range(2,len(L)):
				assert(1<=L[j] and L[j] <= n)
				assert(app[L[j]] == 0)
				app[L[j]]=1
			C += 1
	print([n,Q,C,UVEQ,PEQ,M1])
for i in range(1,11):
	print("data%d:\n"%i)
	in_f=open('../data/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()
for i in range(1,5):
	in_f=open('../down/%d.in'%(i),'r')
	check_in_file(in_f)
	in_f.close()