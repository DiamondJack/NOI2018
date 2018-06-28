MaxN = tl.hn(50000)
MaxM = tl.hn(100000)
HlfN = tl.hn(10000)
HlfM = tl.hn(30000)

ret = [
	["测试点",	"$n\\le $",		"$m\\le$",		"$T\\le 50$", "特殊性质"	],
	[0,			tl.hn(2),		tl.hn(3),		"满足",		"无"			],
	[0,			tl.hn(10),		tl.hn(30),		"满足",		"无"			],
	[0,			tl.hn(200),		tl.hn(300),		"满足",		"无"		],
	[0,			tl.hn(1000),	tl.hn(2000),	"满足",		"$a_i = b_i - 1$"			],
	[0,			HlfN,			HlfM,			"满足",		None			],
	[0,			MaxN,			MaxM,			"满足",None			],
	[0,			HlfN,			HlfM,			"满足","$c_i = 0$"			],
	[0,			MaxN,			MaxM,			"满足",None			],
	[0,			MaxN,			MaxM,			"满足",None			],
	[0,			HlfN,			"$n$",			"满足","$S_1$"		],
	[0,			MaxN,			"$n$",			"不满足","$S_1$"			],
	[0,			MaxN,			"$n$",			"不满足","$S_1$"			],
	[0,			HlfN,			HlfM,			"满足","$S_2$"		],
	[0,			HlfN,			HlfM,			"不满足","$S_2$"			],
	[0,			MaxN,			MaxM,			"不满足","$S_2$"			],
	[0,			MaxN,			MaxM,			"不满足","$S_2$"			],
	[0,			HlfN,			HlfM,			"满足","无"			],
	[0,			HlfN,			HlfM,			"满足","无"			],
	[0,			MaxN,			MaxM,			"不满足","无"			],
	[0,			MaxN,			MaxM,			"不满足","无"			],
]

for i in range(1, len(ret)):
	ret[i][0] = str(i)

return merge_ver(ret)
