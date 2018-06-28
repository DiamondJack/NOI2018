MaxN = 50000
MaxM = 100000
HlfN = 10000
HlfM = 30000

from os import *

ret = [
	[" ",	"$n\\le $",		"$m\\le$",		" "	],
	[0,			2,			3,		"S"			],
	[0,			10,			30,		"S"			],
	[0,			200,			300,		"S"			],
	[0,			1000,			2000,	"SA"			],
	[0,			HlfN,			HlfM,			"SA"			],
	[0,			MaxN,			MaxM,			"SA"			],
	[0,			HlfN,			HlfM,			"SB"			],
	[0,			MaxN,			MaxM,			"SB"			],
	[0,			MaxN,			MaxM,			"SB"			],
	[0,			HlfN,			"$n$",			"SC"		],
	[0,			MaxN,			"$n$",			"C"			],
	[0,			MaxN,			"$n$",			"C"			],
	[0,			HlfN,			HlfM,			"SD"		],
	[0,			HlfN,			HlfM,			"SD"			],
	[0,			MaxN,			MaxM,			"D"			],
	[0,			MaxN,			MaxM,			"D"			],
	[0,			HlfN,			HlfM,			"S"			],
	[0,			HlfN,			HlfM,			"S"			],
	[0,			MaxN,			MaxM,			"N"			],
	[0,			MaxN,			MaxM,			"N"			],
]

system("g++ std.cpp -o std -O2")

for i in xrange(14, 17):
	R = ret[i]
	if R[2] == "$n$":	R[2] = R[1]
	system("echo %d.in %d %d %s | python casemkr.py" % (i, R[1], R[2], R[3]))
	system("/usr/bin/time ./std < %d.in > %d.ans" % (i, i))
