import os
import random

def randchar(w=26):
	return chr(ord('a')+random.randint(0,w-1))

def getC(l,r):
	w=[]
	for i in range(l,r+1):
		w.append(chr(ord('a')+i))
	return w

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
	for i in range(rest//50):
		Q.append(5)
		rest-=Q[-1]
	for i in range(rest//100):
		Q.append(random.randint(5,15))
		rest-=Q[-1]
	for i in range(rest//300):
		Q.append(300)
		rest-=Q[-1]

	assert rest>=0

	pr('%s\n'%(len(Q)))
	for x in Q:
		l=1
		r=lenS
		if ob:
			l=random.randint(1,lenS)
			r=random.randint(l,lenS)
		T=randStr(x)
		pr('%s %s %s\n'%(''.join(T),l,r))

def genStrong(pr,lenS,lenT,ob,limit=True):
	lenC=0
	while (lenC+2)*(lenC+3)<=2*lenS-(lenS//100):
		lenC+=1
	if limit:
		lenC=min(lenC,250)
	else:
		lenC=min(lenC,1000)

	cir=randStr(lenC,s=13)

	rest=lenS-(lenS//200)-((lenC+1)*(lenC+2)//2)
	S=[]
	for i in range(lenC):
		S.append(cir[i])

	for i in range(1,lenC):
		d=random.randint(0,rest//(lenC-i))
		for j in range(d):
			S.append(randchar(13))
		rest-=d
		S.append('o')
		for j in range(i,lenC):
			S.append(cir[j])

	print(len(S),lenS)

	DD=len(S)

	for i in range(lenS-len(S)):
		S.append(random.choice(getC(20,25)))

	assert len(S)==lenS

	pr('%s\n'%(''.join(S)))	
	Q=[lenT//10]
	rest=lenT-Q[-1]
	for i in range(rest//50):
		Q.append(5)
		rest-=Q[-1]

	for i in range(300):
		p=rest//1500
		Q.append(random.randint(p-1,p+1))
		rest-=Q[-1]

	print(rest//(lenC+20),lenC)

	for i in range(rest//(lenC+10)):
		Q.append(lenC+random.randint(5,10))
		rest-=Q[-1]

	assert rest>0

	pr('%s\n'%(len(Q)))
	for x in Q:
		l=1
		r=lenS
		ty=random.randint(1,20)
		if ob:
			l=random.randint(1,lenS)
			r=random.randint(l,lenS)
			if ty==1:
				l=random.randint(DD,lenS)
				r=random.randint(l,lenS)
			else: 
				if ty<=15:
					l=random.randint(1,lenS//10)
					r=random.randint(lenS-lenS//10,lenS)
		
		T=[]
		if ty==1:
			for i in range(x):
				T.append(random.choice(getC(20,25)))
		else:
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
		genStrong(fp.write,10**5,2*10**5,ob=False)

	with open('9.in','w') as fp:
		genRDStr(fp.write,10**5,2*10**5,ob=False)

	with open('10.in','w') as fp:
		genStrong(fp.write,2*10**5,4*10**5,ob=False)

	with open('11.in','w') as fp:
		genRDStr(fp.write,2*10**5,4*10**5,ob=False)

	with open('12.in','w') as fp:
		genStrong(fp.write,3*10**5,6*10**5,ob=False)

	with open('13.in','w') as fp:
		genRDStr(fp.write,3*10**5,6*10**5,ob=False)

	with open('14.in','w') as fp:
		genStrong(fp.write,4*10**5,8*10**5,ob=False)

	with open('15.in','w') as fp:
		genRDStr(fp.write,4*10**5,8*10**5,ob=False)

	with open('16.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=False)

	with open('17.in','w') as fp:
		genRDStr(fp.write,5*10**5,10**6,ob=False)

	with open('18.in','w') as fp:
		genStrong(fp.write,2*10**5,10**6,ob=True)
	with open('19.in','w') as fp:
		genStrong(fp.write,3*10**5,10**6,ob=True)
	with open('20.in','w') as fp:
		genStrong(fp.write,4*10**5,10**6,ob=True)
	with open('21.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=True)

	with open('22.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=True)

	with open('23.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=True)

	with open('24.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=True)

	with open('25.in','w') as fp:
		genStrong(fp.write,5*10**5,10**6,ob=True)


	for i in range(1,26):
		os.system('time ./std <%s.in >%s.ans'%(i,i))

final_data()










