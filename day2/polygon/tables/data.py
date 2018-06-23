res = [["编号","$n$","$K$","特殊性质","","编号","$n$","$K$","特殊性质"]]
ret=[]
for i in range(4):
	ret.append([str(i + 1), "$\leq " + str(i * 5 + 5) + "$", "$\leq 3$", "无"])
for i in range(6):
	ans=[str(5 + i), "$\leq 1000$", "$=1$"]
	if i >= 3:
		ans.append("无")
	else:
		ans.append("A")
	ret.append(ans)
for i in range(6):
	ans = [str(11 + i), "$\leq 1000$", "$\leq 2$"]
	if i >= 3:
		ans.append("无")
	else:
		ans.append("A")
	ret.append(ans)
for i in range(4):
	ans = [str(17 + i), "$\leq 1000$", "$\leq 3$"]
	if i >= 2:
		ans.append("无")
	else:
		ans.append("A")
	ret.append(ans)
for i in range(10):
	ret[i].extend("")
	ret[i].extend(ret[i + 10])
	res.append(ret[i])

return merge_ver(res)
