import random
import os


nn=[]
kk=[]
xz=[]

for i in range(1,21):
	with open('polygon%s.in'%(i),'r') as fp:
		x=fp.readline().rstrip()
		n,k=x.split(' ')
		n,k=int(n),int(k)
		nn.append(n)
		kk.append(k)
		d=fp.readline().rstrip()
		fa=list(map(int,d.split(' ')))
		assert len(fa)==n-1
		for j in range(1,n):
			assert (1<=fa[j-1] and fa[j-1]<=j)

		son=[0 for j in range(1,n+5)]
		for x in fa:
			son[x]+=1
		flag=True
		for j in range(1,n+1):
			if son[j]>2:
				flag=False

		if flag:
			xz.append(i)

for i in range(1,21):
	print(nn[i-1],kk[i-1],i in xz)










