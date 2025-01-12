
# Table of Contents

1.  [标题](#orgfb010a8)
    1.  [代码实例](#orgb8de880)
    2.  [大纲相关的快捷键](#org602e606)
        1.  [折叠](#orgd8cba85)
        2.  [大纲间移动](#org2aff35f)
        3.  [基于大纲的编辑](#orgb45e5cd)
        4.  [关于大纲显示](#org684c6f3)
    3.  [轻量级标记语言](#orgad7dc1c)
        1.  [段落](#org16abeab)
        2.  [字体](#orga4cf2c1)
        3.  [列表](#org51db1d4)
2.  [Organize Party <code>[100%]</code>](#org764bbe6)
    1.  [Call people <code>[2/2]</code>](#org2f21188)
        1.  [Peter](#orgaed0b09)
        2.  [Sarah](#org4e1d8dd)
    2.  [Buy products](#orgc77330c)
    3.  [表格](#org5d06274)
        1.  [表格语法](#org535090d)
        2.  [表格快捷键](#org21675a1)
        3.  [分隔线](#orge0023a9)
        4.  [链接](#org6743af8)
        5.  [标记](#orgf368778)
        6.  [代码块](#orgc145b8a)
        7.  [脚注](#org50dd6ce)
        8.  [anchor](#orgf054250)
        9.  [todo](#org4d15587)
        10. [导出](#orgd8d082c)
        11. [math](#orgeae4310)



<a id="orgfb010a8"></a>

# 标题

文章中的标题可以通过 `#+TITLE` 来设置；正文中的标题可以通过 `*` 来设置，
一个 \* 代表一级。


<a id="orgb8de880"></a>

## 代码实例

    * 这是一个一级标题
    ** 这是一个二级标题
    *** 这是一个三级标题


<a id="org602e606"></a>

## 大纲相关的快捷键


<a id="orgd8cba85"></a>

### 折叠

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">快捷键</th>
<th scope="col" class="org-left">说明</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">S-Tab</td>
<td class="org-left">循环 <b><b>整个文档的</b></b> 的大纲状态</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">TAB</td>
<td class="org-left">循环切换 <b><b>光标所在</b></b> 大纲的状态</td>
</tr>
</tbody>
</table>


<a id="org2aff35f"></a>

### 大纲间移动

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">快捷键</th>
<th scope="col" class="org-left">说明</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">C-c C-n/p</td>
<td class="org-left">下/上一级标题</td>
</tr>


<tr>
<td class="org-left">C-c C-f/b</td>
<td class="org-left">下/上一级标题 (仅限同级标题)</td>
</tr>


<tr>
<td class="org-left">C-c C-u</td>
<td class="org-left">跳转到上一级标题</td>
</tr>
</tbody>
</table>


<a id="orgb45e5cd"></a>

### 基于大纲的编辑

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">快捷键</th>
<th scope="col" class="org-left">说明</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">M-Return</td>
<td class="org-left">插入一个同级标题</td>
</tr>


<tr>
<td class="org-left">M-S-Return</td>
<td class="org-left">插入一个同级TODO标题</td>
</tr>


<tr>
<td class="org-left">M-Left/Right</td>
<td class="org-left">将当前标题升级/降级</td>
</tr>


<tr>
<td class="org-left">M-S-Left/Right</td>
<td class="org-left">将当前标题(和子标题一起)升级/降级</td>
</tr>


<tr>
<td class="org-left">M-S-UP/DOWN</td>
<td class="org-left">将标题上/下移动</td>
</tr>


<tr>
<td class="org-left">C-c C-t / S-L/R</td>
<td class="org-left">todo done 切换</td>
</tr>


<tr>
<td class="org-left">S-U/D</td>
<td class="org-left">任务优先级 切换</td>
</tr>


<tr>
<td class="org-left">C-c /</td>
<td class="org-left">只保留大纲</td>
</tr>
</tbody>
</table>


<a id="org684c6f3"></a>

### 关于大纲显示

-   当前文档显示缩进 `M-x: org-indent-mode`
-   默认显示缩进 `#+STARTUP: indent`


<a id="orgad7dc1c"></a>

## 轻量级标记语言


<a id="org16abeab"></a>

### 段落

org Mode 中，需要回车两行开始新的段落。
这是一段文字
这还是第一个段文字

这是第二段文字。


<a id="orga4cf2c1"></a>

### 字体

-   bold ****bold****
-   italic *italic*
-   underline <span class="underline">underline</span>
-   H<sub>2</sub> O;  e=mc<sup>2</sup>
-   `git`


<a id="org51db1d4"></a>

### 列表

1.  ordered list

    1.  first item
        1.  sub task 1
        2.  sub task 2
    2.  second item

2.  unordered list

    可使用 `-, +, *` 开头
    
    -   List
        -   sublist
            -   subsub list

3.  添加列表完成进度


<a id="org764bbe6"></a>

# Organize Party <code>[100%]</code>


<a id="org2f21188"></a>

## Call people <code>[2/2]</code>


<a id="orgaed0b09"></a>

### DONE Peter


<a id="org4e1d8dd"></a>

### DONE Sarah


<a id="orgc77330c"></a>

## DONE Buy products

1.  添加时间戳

    C-c C-s/d schedule/deadline
    
    C-c > 日历

2.  任务一

3.  有关列表的快捷键

    <table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">
    
    
    <colgroup>
    <col  class="org-left" />
    
    <col  class="org-left" />
    </colgroup>
    <tbody>
    <tr>
    <td class="org-left">快捷键</td>
    <td class="org-left">说明</td>
    </tr>
    
    
    <tr>
    <td class="org-left">M-Return</td>
    <td class="org-left">插入一个同级项</td>
    </tr>
    
    
    <tr>
    <td class="org-left">M-S-Return</td>
    <td class="org-left">插入一个带有复选框的项</td>
    </tr>
    
    
    <tr>
    <td class="org-left">M-Left/Right</td>
    <td class="org-left">升级/降级</td>
    </tr>
    
    
    <tr>
    <td class="org-left">M-S-Left/Right</td>
    <td class="org-left">将当前项(和项一起)升级/降级</td>
    </tr>
    
    
    <tr>
    <td class="org-left">M-S-UP/DOWN</td>
    <td class="org-left">上/下移动</td>
    </tr>
    
    
    <tr>
    <td class="org-left">C-c C-c</td>
    <td class="org-left">改变复选框状态</td>
    </tr>
    
    
    <tr>
    <td class="org-left">C-c -</td>
    <td class="org-left">循环切换列表标记</td>
    </tr>
    </tbody>
    </table>


<a id="org5d06274"></a>

## 表格


<a id="org535090d"></a>

### 表格语法

    | Name     | Height | Weight | Age |
    |----------+--------+--------+-----|
    | Abcdefgh |    178 |    123 |  18 |


<a id="org21675a1"></a>

### 表格快捷键

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">
<caption class="t-above"><span class="table-number">Table 1:</span> 表格标题</caption>

<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">快捷键</th>
<th scope="col" class="org-left">说明</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">C-c 竖线</td>
<td class="org-left">创建表格</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">C-c C-c</td>
<td class="org-left">调整表格</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Tab/S-Tab</td>
<td class="org-left">移动</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">M-Left/Right</td>
<td class="org-left">移动列</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">M-Up/Down</td>
<td class="org-left">移动行</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">M-S-L/R</td>
<td class="org-left">删除/插入列</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">M-S-U/D</td>
<td class="org-left">删除/插入行</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">C-c -</td>
<td class="org-left">添加水平分割线</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">C-c ^</td>
<td class="org-left">排序</td>
</tr>
</tbody>
</table>

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />

<col  class="org-right" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">一级部门</th>
<th scope="col" class="org-left">二级部门</th>
<th scope="col" class="org-right">人数</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">A</td>
<td class="org-left">A.1</td>
<td class="org-right">5</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">A.2</td>
<td class="org-right">6</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">B</td>
<td class="org-left">B.1</td>
<td class="org-right">7</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">B.2</td>
<td class="org-right">3</td>
</tr>
</tbody>
</table>


<a id="orge0023a9"></a>

### 分隔线

<span class="underline">\_</span>

&#x2014;


<a id="org6743af8"></a>

### 链接

1.  链接语法

    -   `C-c C-i` 插入链接
    -   `C-c C-o` 点击链接
    
    [The Missing Semester of your CS education NCU local version](file:///home/trace/Documents/ouline.pdf)
    
    [docx 文件](file:///home/trace/Documents/go-转学指南1.2.docx)
    
    [视频](file:///home/trace/Videos/cut.mp4)


<a id="orgf368778"></a>

### 标记

在标题后 `:tag1:tag2:tag3...`


<a id="orgc145b8a"></a>

### 代码块

-   `C-c C-,` 生成模板
-   `C-c '`  在小窗编辑代码块

```verilog
    module tb;
        reg clk;
        initial begin
            clk = 1'b0;
        end
        always #5 clk = ~clk;
    endmodule
```
```cpp
    #include <stdio.h>
    int main ()
      {printf("hello emacs\n"); return 0;}
```

<table id="org974f0e4" border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-right" />

<col  class="org-right" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Sede</th>
<th scope="col" class="org-right">Max cites</th>
<th scope="col" class="org-right">H-index</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Chile</td>
<td class="org-right">257.72</td>
<td class="org-right">21.39</td>
</tr>


<tr>
<td class="org-left">Leeds</td>
<td class="org-right">165.77</td>
<td class="org-right">19.68</td>
</tr>


<tr>
<td class="org-left">Sao Paolo</td>
<td class="org-right">71.00</td>
<td class="org-right">11.50</td>
</tr>


<tr>
<td class="org-left">Stockholm</td>
<td class="org-right">134.19</td>
<td class="org-right">14.33</td>
</tr>


<tr>
<td class="org-left">Morelia</td>
<td class="org-right">257.56</td>
<td class="org-right">17.67</td>
</tr>
</tbody>
</table>

```python
    cities = [d[0] for d in data];
    for _ in cities:
        print(_)
```
```python
    import matplotlib
    import matplotlib.pyplot as plt
    matplotlib.use('Agg')
    fig=plt.figure(figsize=(3,2))
    plt.plot([1,3,2])
    fig.tight_layout()
    plt.savefig('myfig.png')
    return './myfig.png' # return this to org-mode
```

```cpp
    #include "Foo.cpp"
    #include <utility>
    // 模板参数的推导还不是很熟
    
    template <typename T>
    class Container {
        int capacity = 512;
        int size = 0;
        T* data;
    public:
        // using 可以支持泛型吗
        class containerIterator;
        using iterator=containerIterator;
        // 无参构造器
        explicit Container ()
            : size(0), data(static_cast<T*>(malloc(capacity * sizeof(T)))) {}
    
        // 有参构造器
        explicit Container (int capacity)
```


<a id="org50dd6ce"></a>

### 脚注

Latex is the best engine<sup><a id="fnr.1" class="footref" href="#fn.1" role="doc-backlink">1</a></sup>, It is a great tool.


<a id="orgf054250"></a>

### anchor

[go to p1](#orgaee8827)

`C-c %/&` 记忆/回溯位置


<a id="org4d15587"></a>

### todo

-   [X] execute code in org, using babel?
-   [X] export and preview org
-   [X] Latex support


<a id="orgd8d082c"></a>

### 导出

-   `C-c C-e` 导出,可以看 menu bar 里的快捷键
-   `M-x:org-md-export-as-markdown` 导出 markdown file


<a id="orgeae4310"></a>

### math

-   `C-c C-x C-l` 预览latex
-   `C-c C-x C-v` 预览图片

\begin{equation}
x = \sqrt{2}
\end{equation}


# Footnotes

<sup><a id="fn.1" href="#fnr.1">1</a></sup> <http://www.latexlive.com>
