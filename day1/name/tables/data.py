ret=[["测试点","$|S|\leq$","$Q\leq $","$\sum |T|\leq $","询问限制","其他限制 "]]
lenS=[
	200,
	1000,
	1000,
	1000,
	1000,
	"5*10^5",
	"5*10^5",
	"10^5",
	"10^5",
	"2*10^5",
	"2*10^5",
	"3*10^5",
	"3*10^5",
	"4*10^5",
	"4*10^5",
	"5*10^5",
	"5*10^5",
	"2*10^5",
	"3*10^5",
	"4*10^5",
	"5*10^5",
	"5*10^5",
	"5*10^5",
	"5*10^5",
	"5*10^5",
]
sQ=[
	200,
	200,
	200,
	200,
	200,
	1,
	1,
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
	"10^5",
]
sumT=[
	40000,
	40000,
	40000,
	"5*10^5",
	"5*10^5",
	"5*10^5",
	"5*10^5",
	"2*10^5",
	"2*10^5",
	"4*10^5",
	"4*10^5",
	"6*10^5",
	"6*10^5",
	"8*10^5",
	"8*10^5",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
	"10^6",
]
other=[
	"|T|\leq 200",
	"|T|\leq 200",
	"|T|\leq 200",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{字符串随机}",
	"\\text{无}",
	"\\text{字符串随机}",
	"\\text{无}",
	"\\text{字符串随机}",
	"\\text{无}",
	"\\text{字符串随机}",
	"\\text{无}",
	"\\text{字符串随机}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
	"\\text{无}",
]

for i in range(25):
	st="\\text{无}"
	if i+1<=17:
		st="\\text{对于所有询问有}~l=1,r=|S|"
	row=[
		i+1,
		"$%s$"%lenS[i],
		"$%s$"%sQ[i],
		"$%s$"%sumT[i],
		"$%s$"%(st),
		"$%s$"%other[i]
	]
	ret.append(row)

return merge_ver(ret)




