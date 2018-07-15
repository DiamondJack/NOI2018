ret = [["$n$","$m$","$Q=$","测试点","图形态","海拔","强制在线"]]
N=[1,6,50,100]
M=[0,10,150,300]
Q=[0,10,100,200]

for i in range(20):
	if (i<4):
		n=N[i]
		m=M[i]
		q=Q[i]
		t1="不保证"
		t2="一种"
		t3="否"
	else:
		n=200000
		m=400000
		q=400000
		if (i<18):
			q=100000
		t1=t2="不保证"
		t3="是"
		if (i<11):
			t3="否"
			if (i==4 or i==6):
				n=1500
				m=4000
				q=2000
			if (i==10):
				t3="是"
			if (i<6):
				t2="一种"

			else:
				if (i>=9):
					t1="一棵树"
				else:
					t1="一条链"
				m=n-1;
		if (i in range(11,14)):
			t3="否"
		if (i in range(14,16)):
			n=1500
			m=4000
			q=2000
	_m="$\\leq %s$" % m
	if (t1!="不保证"):
		_m="$=n-1$"
	row = [
		"$\\leq %s$" % n,
		_m,
		"$%s$" % q,
		i+1,
		t1,
		t2,
		t3
		]
	ret.append(row)
return merge_ver(ret)
