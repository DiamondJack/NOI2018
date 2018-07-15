import random

n=100
w=[chr(random.randint(0,25)+ord('a')) for i in range(n)]
print(''.join(w))
print(n)
for i in range(n):
	m=random.randint(1,n)
	w=[chr(random.randint(0,25)+ord('a')) for i in range(m)]
	l=random.randint(1,n)
	r=random.randint(1,n)
	if l>r:
		l,r=r,l
	print(''.join(w),l,r)











