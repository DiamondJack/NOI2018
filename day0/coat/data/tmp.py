from sys import *
setrecursionlimit(1000000)


N, K, W = map(int, raw_input().split())
assert(N == len(raw_input().split()))



E = []
for i in xrange(N):	E.append([])

for i in xrange(1, N):
	x, y = map(int, raw_input().split())
	x -= 1
	y -= 1
	E[x].append(y)
	E[y].append(x)

def merge(A, B):
	C = [0] * (len(A) + len(B) - 1)
	for i in xrange(len(A)):
		for j in xrange(len(B)):
			C[i + j] += A[i] * B[j]
	return C

global Ans
Ans = 0
def dp(i, f):
	global Ans
	F = [0, 1]
	for k in E[i]:
		if k == f:	continue
		F = merge(F, dp(k, i))
	F[0] += 1
	Ans += sum(F[K:])
	return F

dp(0, -1)
print Ans
