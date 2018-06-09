from random import *
from sys import *
from math import *

def move_pt(E, M):
	for i in xrange(len(E)):
		E[i][0] += M
		E[i][1] += M
	return E

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
			E += move_pt(make(S[i], 2, 0), P[i - 1])
			P[i] = len(E) + 1
	elif t == 6:
		return make(N, 2, 0)

	for e in E:
		assert 1 <= e[0] < e[1]

	return E

def merge_tree(A, B):
	N = len(A) + 1
	M = len(B) + 1
	return A + [[randint(1, N), N + 1]] + move_pt(B, N)

def shuf_tree(E):
	P = range(1, len(E) + 2)
	shuffle(P)
	P = [0] + P
	shuffle(E)
	EE = []
	for e in E:
		shuffle(e)
		EE.append([P[e[0]], P[e[1]]])
	return EE

for x in argv[1:]:
	exec (x)

if K == 0:	K = randint(N * 7 / 8, N)
if B == 0:	B = randint(3, 7)

print N, K, W
print " ".join(map(str, [randint(1, W) for i in xrange(N)]))

S = set([N])
while len(S) < B:
	S.add(randint(2, N))

E = []
L = 1
for R in sorted(list(S)):
	assert R > L
	E = merge_tree(E, make(R - L, P[randint(0, len(P) - 1)]))
	L = R

for e in E:
	assert 1 <= e[0] < e[1]
shuf_tree(E)
for e in E:
	print e[0], e[1]
