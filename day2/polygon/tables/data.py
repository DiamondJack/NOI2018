ret = [["$n$","$K$","其他约定"]]
for i in range(4):
	ret.append(["$\leq 20$", "$\leq 3$", "无"])
for i in range(6):
	ret.append(["$\leq 1000$", "$=1$", "无"])
for i in range(6):
	ans = ["$\leq 1000$", "$\leq 2$"]
	if i < 3:
		ans.append("无")
	else:
		ans.append("保证每一个点最多只有两个孩子")
	ret.append(ans)
for i in range(4):
	ans = ["$\leq 1000$", "$\leq 3$"]
	if i < 2:
		ans.append("无")
	else:
		ans.append("保证每一个点最多只有两个孩子")
	ret.append(ans)

return merge_ver(ret)
