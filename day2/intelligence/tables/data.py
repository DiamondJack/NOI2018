MaxN = tl.hn(50000)
MaxM = tl.hn(100000)
HlfN = tl.hn(10000)
HlfM = tl.hn(30000)

ret = [
	["测试点",	"$n\\le $",		"$m\\le$",		"$T\\le 50$", "特殊性质"	],
	[0,			tl.hn(2),		tl.hn(3),		"保证",		"无"			],
	[0,			tl.hn(10),		tl.hn(30),		"保证",		"无"			],
	[0,			tl.hn(200),		tl.hn(300),		"保证",		"无"		],
	[0,			tl.hn(1000),	tl.hn(2000),	"保证",		"$a_i = b_i - 1$"			],
	[0,			HlfN,			HlfM,			"保证",		None			],
	[0,			MaxN,			MaxM,			"保证",None			],
	[0,			HlfN,			HlfM,			"保证","$c_i = 0$"			],
	[0,			MaxN,			MaxM,			"保证",None			],
	[0,			MaxN,			MaxM,			"保证",None			],
	[0,			HlfN,			"$n$",			"保证","$S_1$"		],
	[0,			MaxN,			"$n$",			"不保证","$S_1$"			],
	[0,			MaxN,			"$n$",			"不保证","$S_1$"			],
	[0,			HlfN,			HlfM,			"保证","$S_2$"		],
	[0,			HlfN,			HlfM,			"保证","$S_2$"			],
	[0,			MaxN,			MaxM,			"不保证","$S_2$"			],
	[0,			MaxN,			MaxM,			"不保证","$S_2$"			],
	[0,			HlfN,			HlfM,			"保证","无"			],
	[0,			MaxN,			MaxM,			"保证","无"			],
	[0,			MaxN,			MaxM,			"不保证","无"			],
	[0,			MaxN,			MaxM,			"不保证","无"			],
]

for i in range(1, len(ret)):
	ret[i][0] = str(i)

return merge_ver(ret)
