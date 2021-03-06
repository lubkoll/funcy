
## Arithmetic Types

Arithmetic types that can be used in *funcy* have to fulfil the following requirements:

<h3>Requirements</h3>
<ol>
<li><strong>Copyable:</strong><br> T must be <a href="http://en.cppreference.com/w/cpp/concept/CopyConstructible">CopyConstructible</a> and <a href="http://en.cppreference.com/w/cpp/concept/CopyAssignable">CopyAssignable</a>. </li>

<li><strong>Multiplication with arithmetic types:</strong><br> 
Given: 
<ul>
<li>An object t of type T.</li>
<li>An object a of an arithmetic type, such as double or int.</li>
</ul>
At least one of the following expressions must be valid:
<ul>
<li><code>T s = a*t;</code></li>
<li><code> t *= a;</code></li>
</ul></li>

<li><strong>Summation:</strong><br>
Objects t and s of type T must be summable, i.e. at least one of the following expressions must be valid:
<ul>
<li><code>T r = s + t;</code></li>
<li><code>t += s;</code></li>
</ul></li>

<li><strong>Multiplication (for matrix types only):</strong><br>
Compatible matrices t and s must be multipliable, i.e. at least one of the following expressions must be valid:
<ul>
<li><code> auto r = t*s;</code></li>
<li><code> t*=s;</code> (for square matrices)</li>
<li><code> auto r = t.rightmultiplany(s);</code> (for <a href="http://www.dune-project.org">DUNE</a> matrices)</li>
</ul></li>

<li><strong>Access to data:</strong><br>
Access to the entries of a matrix or vector t via at least one of the following expressions:
<ul>
<li><code>auto a = t[1][2];</code> (for matrices) or <code>auto a = t[1];</code> (for vectors).</li>
<li><code>auto a = t(1,2);</code> (for matrices) or <code>auto a = t(1);</code> (for vectors).</li>
</ul></li>

<li><strong>Access to number of rows and columns (matrices and vectors):</strong><br>
<ul>
<li><strong>Fixed size:</strong><br>
A specialization of the template classes <br>
<code>template &lt;class Matrix, class&gt; struct NumberOfRows;</code><br>
and<br>
<code>template &lt;class Matrix, class&gt; struct NumberOfColumns;</code> <br>
must be provided. For the cases that, for some scalar type S and n,m of type unsigned or int, the employed matrix class is of the form
<ul>
<li><code>Matrix&lt;n,m&gt;</code></li>
<li><code>Matrix&lt;S,n,m&gt;</code></li>
</ul>
suitable specializations are available and access to the number of rows and columns is supported without need to do anything. Similar specializations exist for vectors.
</li>

<li><strong>Dynamic size:</strong><br>
Access to the number of rows and columns of an object t must be supported via at least one of the following expressions:
<ul>
<li><code>t.rows()</code> resp. <code>t.cols()</code></li>
<li><code>t.n_rows</code> resp. <code>t.n_cols</code></li>
</ul></li>
</ul>
</li>

</ol>


<h3>Optional</h3>

<ol>
<li><strong>Default-constructible:</strong><br>
If T is <a href="http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a> then functions that take arguments of type T also a default constructor, else the default constructor is deleted.
</li>

<li><strong>Construction of the zero matrix:</strong><br>
If you want to use the functions <code>zero&lt;Matrix&gt;()</code> and <code>unitMatrix&lt;Matrix&gt;()</code>, a specialization of<br>
<code>template &lt;class Matrix,class&gt; struct Zero;</code><br>
must be provided. Suitable implementations exist for the cases that a zero matrix can be created by one of the following expressions:
<ul>
<li><code>auto zeroMatrix = Matrix(0.);</code></li>
<li><code>auto zeroMatrix;</code><br>
    <code>zeroMatrix.zeroes();</code><br></li>
</ul>
</li>
</ol>

[back](README.md)