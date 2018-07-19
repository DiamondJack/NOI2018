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

def getEOF(in_f):
	getline(in_f,0)
cntt=0
def my_gcd(a,b):
	global cntt
	#print(cntt)
	#print(a)
	a=int(a)
	b=int(b)
	if a<b:
		c=a
		a=b
		b=c
	#print(a,b)
	cntt+=1
	#print(cntt)
	if abs(b-0.0)<0.5:
		return a
	#print(a,b,a%b)
	return my_gcd(b,a%b)

def my_lcm(a,b):
	return a*b/my_gcd(a,b)

def check(in_f,ou_f):
	Maxp=0
	Maxatk=0
	Maxa=0
	AleP=True
	MaxLCM=0
	Maxn=0
	Maxm=0
	[T]=getintline(in_f,1)
	for tt in range(T):
		[ANS]=getintline(ou_f,1)
		[n,m]=getintline(in_f,2)
		if n > Maxn:
			Maxn=n
		if m > Maxm:
			Maxm=m
		a=getintline(in_f,n)
		p=getintline(in_f,n)
		atk=getintline(in_f,n)
		atk2=getintline(in_f,m)
		LCM=1
		for i in range(n):
			assert(a[i]>0)
			assert(p[i]>0)
			assert(atk[i]>0)
			if a[i]>p[i]:
				AleP=False
			if p[i]>Maxp:
				Maxp=p[i]
			if a[i]>Maxa:
				Maxa=a[i]
			#if checkprime(p)
			#LCM=my_lcm(LCM,p[i])
			if atk[i]>Maxatk:
				Maxatk=atk[i]
		if LCM>MaxLCM:
			MaxLCM=LCM
		for i in range(m):
			if atk2[i]>Maxatk:
				Maxatk=atk2[i]
	getEOF(in_f)
	getEOF(ou_f)
	print(Maxn,Maxm,Maxp,Maxa,Maxatk,AleP,MaxLCM)

for i in range(1,21):
	print("data %d:"%i)
	in_f=open("../data/%d.in"%i,"r")
	ou_f=open("../data/%d.ans"%i,"r")
	check(in_f,ou_f)
	in_f.close()
	ou_f.close()

for i in range(1,3):
	print("sample %d:"%i)
	in_f=open("../down/%d.in"%i,"r")
	ou_f=open("../down/%d.ans"%i,"r")
	check(in_f,ou_f)
	in_f.close()
	ou_f.close()