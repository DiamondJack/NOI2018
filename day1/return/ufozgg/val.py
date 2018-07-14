name = 'return'
def getline(in_f,cnt):
	line = in_f.readline()
	obj = line.split(' ')
	assert(len(obj)==cnt)
	return obj

def getintline(in_f,cnt):
	obj = getline(in_f,cnt)
	for i in range(len(obj)):
		obj[i] = int(obj[i])
	return obj

def check_in_file(in_f,out_f):
	T = getintline(in_f,1)
	assert(1<=T and T<=3)
	MAXN = 0
	MAXM = 0
	for tt in range(T)
		[n,m] = getintline(in_f,2)
		assert(1<=n and n<=)
		assert(1<=n and n<=)
		

for i in range(1,21):
	print('Check data %d'%i)
	in_f=open('../data/%d.in'%i,'r')
	out_f=open('../data/%d.ans'%i,'r')
	if i not in []:
		check_in_file(in_f,out_f)
	in_f.close()
	out_f.close()
for i in range(1,5):
	print('Check sample %d'%i)
	in_f=open('../down/%d.in'%i,'r')
	out_f=open('../down/%d.ans'%i,'r')
	check_in_file(in_f,out_f)
	in_f.close()
	out_f.close()