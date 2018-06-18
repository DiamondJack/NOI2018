MaxN = tl.hn(50000)
MaxM = tl.hn(100000)
HlfN = tl.hn(10000)
HlfM = tl.hn(30000)

ret = [
	["测试点",	"$n\\le $",		"$m\\le$",		"特殊性质"	],
	[0,			tl.hn(2),		tl.hn(3),		"无"			],
	[0,			tl.hn(10),		tl.hn(30),		"无"			],
	[0,			tl.hn(200),		tl.hn(300),		"S"			],
	[0,			tl.hn(1000),	tl.hn(2000),	"S"			],
	[0,			HlfN,			HlfM,			"SA"			],
	[0,			MaxN,			MaxM,			"SA"			],
	[0,			HlfN,			HlfM,			"SB"			],
	[0,			MaxN,			MaxM,			"SB"			],
	[0,			HlfN,			"$n$",			"SC"		],
	[0,			MaxN,			"$n$",			"C"			],
	[0,			MaxN,			"$n$",			"C"			],
	[0,			HlfN,			HlfM,			"SD"		],
	[0,			HlfN,			HlfM,			"D"			],
	[0,			MaxN,			MaxM,			"D"			],
	[0,			MaxN,			MaxM,			"D"			],
	[0,			HlfN,			HlfM,			"S"			],
	[0,			HlfN,			HlfM,			"S"			],
	[0,			MaxN,			MaxM,			"无"			],
	[0,			MaxN,			MaxM,			"无"			],
	[0,			MaxN,			MaxM,			"无"			],
]

for i in range(1, len(ret)):
	ret[i][0] = str(i)

return merge_ver(ret)