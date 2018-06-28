ret = [["测试点编号","$n$","$m$","特殊性质"]]

for i in range(10):
	if(i<2):
		n="1";
		m=" $\le$ 1000000"
		p="无"
	elif(i<4):
		n=" $\le$ 10"
		m=" $\le$ 1000000"
		p="所有剑攻击力为1，且所有 $p_i$ 的最小公倍数 $\le$ 1000000"
	elif(i<6):
		n="100000"
		m="100000"
		p="所有 $p_i$ 是质数"
	elif(i<8):
		n="100000"
		m="1"
		p="无"
	else:
		n="100000"
		m="100000"
		p="无"
	row = [i+1,n,m,p]
	ret.append(row)
return merge_ver(ret)