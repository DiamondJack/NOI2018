## 简介

更新到了 0.1.3 版本，新特性见最后。

这个gitlab没有注册的用户似乎是不能提issue的，所以有issue可以给我发邮件 [chen.xm.mu@gmail.com](mailto:chen.xm.mu@gmail.com)，或是到[这个废弃的老工程](http://git.oschina.net/mulab/oi_tools)上面提issue，知道我QQ或微信的小伙伴也可以用这些工具告诉我。

这个轮子打算逐步实现：

* 合作：通过共同使用git和遵循一些约定，降低合作命题者之间版本控制，题面修改，代码、数据交换，bug修复等的成本。
* 题面：通过一些轮子搭建易于转换为多种格式的题面范式，用这套轮子造的题面可以转变到各种比赛格式。
* 适配：尽量支持从现有的各类评测工具导入数据和导出到各类评测工具中。

这个轮子主要是面向出题人和OJ站长，方便大家造题和分享题目。

目前这个轮子还在you开yi发dui中bug。如果希望我们支持其他格式的题面，其他工具的导入导出，对这个轮子有任何建议或意见，发现了任何bug，或是有兴趣加入我们，欢迎随时联系。

## 文档

[文档在这里](https://git.thusaac.org/publish/tuack/wikis/home)

## 更新记录

### v0.1.3

- 添加 `tuack.doc` 可以导入其他格式的题面和进行简单的格式化。这项功能还有一堆 bug，注意备份。
- 添加 `tuack.ren thuoj`，用于输出为 dokuwiki 的数据结构课程 OJ。

### v0.1.2.1

* 修复若干 bug，尝试用此版本推到pypi上。

### v0.1.2

*   添加yaml格式的配置文件；
*   添加 `tuack.ren loj`，`tuack.gen auto`；
*   现在可以设置字体颜色了；
*   现在json里面的中文在gen之后还会变回中文而不会是unicode了；
*   去掉了packed标记，判断是否是打包评测只依赖于score字段是否设置；
*   修复了若干bug，增加了一些小feature。

### v0.1.1

*   添加了 pre-test 类型的数据；
*   题面可以用 `data`、`args`、`samples`、`pre` 等写法代替类似于 `prob['data']` 的写法；
*   添加了用户代码的期望得分标注；
*   添加了一个题解文件；
*   修复了若干bug。
