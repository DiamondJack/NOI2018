res = [["编号","$n$","$K$","约定","编号","$n$","K","约定"]]
ret=[]
for i in range(4):
	ret.append([str(i + 1), "$\leq 20$", "$\leq 3$", "无"])
for i in range(6):
	ret.append([str(5 + i), "$\leq 1000$", "$=1$", "无"])
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
	ret[i].extend(ret[i + 10])
	res.append(ret)

return merge_ver(res)
