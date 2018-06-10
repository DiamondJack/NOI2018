ret = [["$n=$","$m=$","$Q=$","测试点","图形态","海拔","强制在线"]]
N=[1,6,60,100]
M=[0,10,200,300]
Q=[0,10,100,200]

for i in range(20):
	if (i<4):
		n=N[i]
		m=M[i]
		q=Q[i]
		t1="不保证"
		t2="两种"
		t3="否"
	else:
		n=200000
		m=400000
		q=300000
		t1=t2="不保证"
		t3="是"
		if (i<12):
			if (i%4==0):
				n=2000
				m=5000
			if (i%4<=1):
				t3="否"
			if (i//4==1):
				if (i%4==3):
					t1="一棵树"
				else:
					t1="一条链"
				m=n-1;
			if (i//4==2):
				if (i%4==3):
					t2="两种"
				else:
					t2="一种"
		if (i in range(12,16)):
			t3="否"
	row = [
		"$%s$" % n,
		"$%s$" % m,
		"$%s$" % q,
		i,
		t1,
		t2,
		t3
		]
	ret.append(row)
return merge_ver(ret)
