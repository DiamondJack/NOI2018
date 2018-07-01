import os
import random

def randchar(w=26):
	return chr(ord('a')+random.randint(0,w-1))

def gen_simple(pr,maxN,ojbk=False):
	n=maxN-random.randint(1,maxN//10)
	S=[randchar() for i in range(n)]
	pr('%s\n'%(''.join(S)))
	Qlen=[1]
	for i in range(maxN-1):
		x=random.randint(0,len(Qlen))
		if x==len(Qlen):
			Qlen.append(1)
		else:
			Qlen[x]+=1
	print(len(Qlen))
	print(Qlen)
	pr('%s\n'%(len(Qlen)))
	for x in Qlen:
		l=random.randint(1,n)
		r=random.randint(1,n)
		if l>r:
			l,r=r,l
		if ojbk:
			l,r=1,n
		T=[randchar() for i in range(x)]
		pr('%s %s %s\n'%(''.join(T),l,r))

def gen_period_full(pr,maxN,ojbk=False):
	n=maxN-random.randint(1,maxN//10)
	per=random.randint(1000,2000)
	base=[randchar(w=4) for i in range(per)]
	S=[]
	for i in range(n):
		S.append(base[i%per])

	for i in range(n//3000):
		x=random.choice(range(n))
		S[x]=randchar()

	QS=[]
	for i in range(50):
		l=random.randint(0,n-(maxN//50))
		for j in range(maxN//50):
			QS.append(S[l+j])

	assert(len(QS)<=maxN)

	Q=random.randint(450,550)
	pre=0
	every=len(QS)//Q
	pr('%s\n'%(''.join(S)))
	pr('%s\n'%(Q))
	for i in range(Q):
		dl=pre
		dr=pre+random.randint(every-10,every-5)
		T=[]
		for j in range(dl,dr):
			T.append(QS[j])
		pre=dr
		for j in range(len(T)//20):
			x=random.choice(range(len(T)))
			T[x]=randchar()
		l=random.randint(1,n)
		r=random.randint(l,n)
		if ojbk:
			l,r=1,n
		pr('%s %s %s\n'%(''.join(T),l,r))

def naive_data():
	for i in range(1,3):
		with open('%s.in'%(i),'w') as fp:
			gen_simple(fp.write,100)
		os.system('time ./std <%s.in >%s.out'%(i,i))

	for i in range(3,7):
		with open('%s.in'%(i),'w') as fp:
			gen_simple(fp.write,2000)
		os.system('time ./std <%s.in >%s.out'%(i,i))

	for i in range(7,18):
		with open('%s.in'%(i),'w') as fp:
			gen_period_full(fp.write,10**5,ojbk=True)
		os.system('time ./std <%s.in >%s.out'%(i,i))
	for i in range(18,20):
		with open('%s.in'%(i),'w') as fp:
			gen_period_full(fp.write,10**5)
		os.system('time ./std <%s.in >%s.out'%(i,i))

	for i in range(20,22):
		with open('%s.in'%(i),'w') as fp:
			gen_period_full(fp.write,2*10**5)
		os.system('time ./std <%s.in >%s.out'%(i,i))

	for i in range(22,26):
		w=500000
		if i<24:
			w-=(24-i)*(10**5)

		with open('%s.in'%(i),'w') as fp:
			gen_period_full(fp.write,w)
		os.system('time ./std <%s.in >%s.out'%(i,i))


naive_data()