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

def gen1_5(pr,lenS,sQ,lenT):
	lenS=lenS-random.randint(0,lenS//20)
	sQ=sQ-random.randint(0,sQ//20)
	S=[randchar(4) for i in range(lenS)]
	pr('%s\n'%(''.join(S)))
	pr('%s\n'%(sQ))
	for i in range(sQ):
		L=lenT-random.randint(1,lenT//20)
		T=[randchar(4) for i in range(L)]
		pr('%s %s %s\n'%(''.join(T),1,len(S)))

def genPR(pr,lenS,Q,lenT):

	Ker=[randchar(26) for i in range(1000)]
	S=[Ker[i%1000] for i in range(lenS//2)]
	for i in range(lenS-len(S)):
		S.append(randchar(26))
	for i in range(1000):
		S[random.randint(0,lenS-1)]=randchar(26)
	T=[Ker[i%1000] for i in range(lenT//2)]
	for i in range(lenT-len(T)):
		T.append(randchar(26))
	for i in range(1000):
		T[random.randint(0,lenT-1)]=randchar(26)

	pr('%s\n'%(''.join(S)))
	pr('1\n')
	pr('%s 1 %s\n'%(''.join(T),len(S)))

def randStr(n,s=26):
	return [randchar(s) for i in range(n)]

def genRDStr(pr,lenS,lenT,ob):
	S=randStr(lenS)
	pr('%s\n'%(''.join(S)))
	Q=[lenT//10]
	rest=lenT-Q[0]
	for i in range(lenT//100):
		Q.append(random.randint(5,15))
		rest-=Q[-1]
	d=int(rest**0.5)
	while d*d>rest:
		d-=1

	for i in range(d):
		Q.append(d)
		rest-=Q[-1]

	assert rest>0

	pr('%s\n'%(len(Q)))
	for x in Q:
		l=1
		r=lenS
		if ob:
			l=random.randint(1,lenS)
			r=random.randint(l,lenS)
		T=randStr(x)
		pr('%s %s %s\n'%(''.join(T),l,r))

def genStrong(pr,lenS,lenT,ob):
	lenC=0
	while (lenC+2)*(lenC+3)<=2*lenS-10000:
		lenC+=1
	cir=randStr(lenC,s=25)

	rest=lenS-((lenC+1)*(lenC+2)//2)
	S=[]
	for i in range(lenC):
		S.append(cir[i])

	for i in range(1,lenC):
		d=random.randint(0,rest//(lenC-i))
		for j in range(d):
			S.append(randchar())
		rest-=d
		S.append('z')
		for j in range(i,lenC):
			S.append(cir[j])

	print(len(S),lenS)

	for i in range((lenS-len(S))-(lenS-len(S))//10):
		S.append(randchar())

	for i in range(lenS-len(S)):
		S.append('a')

	assert len(S)==lenS

	pr('%s\n'%(''.join(S)))	
	Q=[]
	rest=lenT
	for i in range(lenT//100):
		Q.append(random.randint(10,15))
		rest-=Q[-1]

	print(rest//(lenC+20),lenC)

	for i in range(rest//(lenC+10)):
		Q.append(lenC+random.randint(6,10))
		rest-=Q[-1]

	assert rest>0

	pr('%s\n'%(len(Q)))
	for x in Q:
		l=1
		r=lenS
		if ob:
			l=random.randint(1,lenS)
			r=random.randint(l,lenS)
			if random.randint(1,10)==1:
				l=random.randint(lenS-1000,lenS)
				r=random.randint(l,lenS)
		
		T=[]
		if x>=lenC:
			rt=x-lenC
			for i in range(rt//2):
				T.append(randchar())
			for i in range(lenC):
				T.append(cir[i])
			for i in range(rt-(rt//2)):
				T.append(randchar())
		else:
			for i in range(x):
				T.append(randchar())
		for i in range(3):
			T[random.randint(0,len(T)-1)]=randchar()
		pr('%s %s %s\n'%(''.join(T),l,r))



def final_data():
	with open('1.in','w') as fp:
		gen1_5(fp.write,200,200,200)
	with open('2.in','w') as fp:
		gen1_5(fp.write,1000,200,200)
	with open('3.in','w') as fp:
		gen1_5(fp.write,1000,200,200)
	with open('4.in','w') as fp:
		gen1_5(fp.write,1000,200,2500)
	with open('5.in','w') as fp:
		gen1_5(fp.write,1000,200,2500)
	with open('6.in','w') as fp:
		genPR(fp.write,5*10**5,1,5*10**5)
	with open('7.in','w') as fp:
		genPR(fp.write,5*10**5,1,5*10**5)

	with open('8.in','w') as fp:
		genStrong(fp.write,10**5,10**5,ob=False)

	with open('9.in','w') as fp:
		genRDStr(fp.write,10**5,10**5,ob=False)

	with open('10.in','w') as fp:
		genStrong(fp.write,2*10**5,2*10**5,ob=False)

	with open('11.in','w') as fp:
		genRDStr(fp.write,2*10**5,2*10**5,ob=False)

	with open('12.in','w') as fp:
		genStrong(fp.write,3*10**5,3*10**5,ob=False)

	with open('13.in','w') as fp:
		genRDStr(fp.write,3*10**5,3*10**5,ob=False)

	with open('14.in','w') as fp:
		genStrong(fp.write,4*10**5,4*10**5,ob=False)

	with open('15.in','w') as fp:
		genRDStr(fp.write,4*10**5,4*10**5,ob=False)

	with open('16.in','w') as fp:
		genStrong(fp.write,5*10**5,5*10**5,ob=False)

	with open('17.in','w') as fp:
		genRDStr(fp.write,5*10**5,5*10**5,ob=False)

	with open('18.in','w') as fp:
		genStrong(fp.write,10**5,10**5,ob=True)
	with open('19.in','w') as fp:
		genStrong(fp.write,10**5,10**5,ob=True)
	with open('20.in','w') as fp:
		genStrong(fp.write,10**5,10**5,ob=True)
	with open('21.in','w') as fp:
		genStrong(fp.write,10**5,10**5,ob=True)

	with open('22.in','w') as fp:
		genStrong(fp.write,2*10**5,2*10**5,ob=True)
	with open('23.in','w') as fp:
		genStrong(fp.write,3*10**5,3*10**5,ob=True)
	with open('24.in','w') as fp:
		genStrong(fp.write,4*10**5,4*10**5,ob=True)
	with open('25.in','w') as fp:
		genStrong(fp.write,5*10**5,5*10**5,ob=True)

	for i in range(1,26):
		os.system('time ./std <%s.in >%s.ans'%(i,i))

final_data()




