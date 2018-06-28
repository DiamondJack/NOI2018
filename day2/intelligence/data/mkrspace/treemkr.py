from random import *
import sys   
from math import *
sys.setrecursionlimit(10000000)

RI = raw_input()

try:
	N, M, S = RI.split()
except:
	N, M = RI.split()
	S = ""
N = int(N)
M = int(M)
S = set(list(S))

print 1
print N

def move_ptr(E, M):
	return map(lambda e : [e[0] + M, e[1] + M], E)

def make(N, t, K = 3):
	if N == 1:	return []
	E = []
	if t == 1:		#random 
		for i in xrange(1, N):
			E.append([randint(1, i), i + 1])
	elif t == 2:	#chain
		for i in xrange(1, N):
			E.append([randint(max(1, i - K), i), i + 1])
	elif t == 3:	#flower
		for i in xrange(1, N):
			E.append([randint(1, min(i, K)), i + 1])
	elif t == 4:	#heap
		for i in xrange(1, N):
			E.append([(i + 1) / 2, i + 1])
	elif t == 5:	#heapflower
		H = int(ceil(sqrt(N)) + 0.1)
		S = []
		P = [0]
		NN = N
		while NN > 0:
			S.append(min(NN, H))
			P.append(0)
			NN -= H
		assert min(S) > 0
		S = [0] + list(reversed(S))
		E = make(S[1], 2, 0)
		P[1] = len(E) + 1
		for i in xrange(2, len(S)):
			E += [[P[i / 2], P[i - 1] + 1]]
			E += move_ptr(make(S[i], 2, 0), P[i - 1])
			P[i] = len(E) + 1
	elif t == 6:
		return make(N, 2, 0)

	for e in E:
		assert 1 <= e[0] < e[1]

	return E
	
def merge_tree(A, B):
	N = len(A) + 1
	M = len(B) + 1
	return A + [[randint(1, N), N + 1]] + move_ptr(B, N)
	
V = 10**9
if 'B' in S:	V = 0

Ch = []
Cnt = [0] * (N + 1)
for i in xrange(N + 1):	Ch.append([])

def random_split(N, M, Min):
	N -= M * Min
	assert N >= 0
	C = [Min] * M
	for i in xrange(N):
		C[randint(0, M - 1)] += 1
	return C

if 'A' in S:	E = make(N, 6)
else:
	E = []
	for s in random_split(N - 1, randint(7, 15), 0):
		if s > 0:
			E = merge_tree(E, make(s, randint(1, 5)))

for e in E:
	assert e[0] < e[1]
	Ch[e[0]].append(e[1])
	print e[0], e[1], randint(0, V)

if 'C' in S:
	P = range(1, N + 1)
	shuffle(P)
	for i in xrange(M):
		Cnt[P[i]] = 1
elif 'D' in S:
	Cnt[1] = M
else:
	B = []
	for i in xrange(randint(3, 7)):
		B.append(randint(1, N))
	for i in xrange(M):
		if randint(0, 1) == 0:
			Cnt[B[randint(0, len(B) - 1)]] += 1
		else:
			Cnt[randint(1, N)] += 1
	
def merge_list(A, B):
	if len(A) <= len(B):
		for a in A:
			B.append(a)
		return B
	else:
		return merge_list(B, A)		

Q = []
K = []
S = []
for i in xrange(N + 1):
	K.append([])
	S.append([])

def Dfs(p):
	S[p] = [p]
	#print 'DFS', p
	if Cnt[p] > 0 and len(Ch[p]) > 0:
		K[p] = random_split(Cnt[p], len(Ch[p]), 0)
	if len(Ch[p]) == 0 and Cnt[p] > 0:
		for i in xrange(Cnt[p]):
			Q.append([p, p])
			Cnt[p] = 0
	for i in xrange(len(Ch[p])):
		T = Dfs(Ch[p][i])
		#print Ch[p][i], '->', p, len(K[p]), len(Ch[p])
		if Cnt[p] > 0:
			#print "want", K[p][i]
			for _ in xrange(K[p][i]):
				Q.append([S[p][randint(0, len(S[p]) - 1)], T[randint(0, len(T) - 1)]])
		#print "before merge"
		S[p] = merge_list(S[p], T)
	#print p, ':', S[p]
	return S[p]

Dfs(1)
print
shuffle(Q)
print M
for q in Q:
	print q[0], q[1], randint(0, 10**9 * N)
	
