ret = [["测试点编号","$n$","$m$","$p_i","a_i","攻击力","其他限制"]]

for i in range(20):
	if(i<2):
		n="$\le 10^5$";
		m="$= 1$"
		p="$= 1$"
		a="$\le 10^5$"
		ATK="$= 1$"
		etc="无"
		#Ans = Max(a)
	elif(i<4):
		n="$\le 10^5$";
		m="$= 1$"
		p="$= 1$"
		a="$\le 10^5$"
		ATK="$\le 10^5$"
		etc="无"
		#Ans = Max(a/ATK)
	elif(i<7):
		n="$\le 10^3$";
		m="$\le 10^3$"
		p="$\le 10^5$"
		a="$\le 10^5$"
		ATK="$\le 10^5$"
		etc="特性1、特性2"
		#for
	elif(i<10):
		n="$= 1$"
		m="$= 1$"
		p="$\le 10^8$"
		a="$\le 10^8"
		ATK="$\le 10^6$"
		etc="特性1"
		#exgcd
	elif(i<13):
		n="$= 1$"
		m="$= 1$"
		p="$\le 10^8$"
		a="$\le 10^8"
		ATK="$\le 10^6$"
		etc="特性1"
		#exgcd quick add
	elif(i<15):
		n="$= 10^5$"
		m="$= 10^5$"
		p="$= 1$"
		a="$\le 10^8"
		ATK="$\le 10^6$"
		etc="无特殊限制"
		#multiset
	elif(i<17):
		n=" $\le$ 10^5"
		m=" $\le$ 10^5"
		p="所有 $p_i$ 是质数"
		a="$\le 10^{12}$"
		ATK="$\le 10^6$"
		etc="特性1"
	else:
		n=" $\le$ 10^5"
		m=" $\le$ 10^5"
		p="无特殊限制"
		a="$\le 10^{12}$"
		ATK="$\le 10^6$"
		etc="特性1"
	row = [i+1,n,m,p,a,ATK,etc]
	ret.append(row)
return merge_ver(ret)