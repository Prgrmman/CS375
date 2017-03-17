**Name:** Jonathan Terner

**Date:** 9/14/2016

**Class:** CS 375

**Assignment:** Assignment 1 (Part B)

**Package name:** jonathan\_terner\_c\_used.tar.gz

**Package contents:**

-   keys.c

-   makefile

-   readme.rtf

-   input.txt

-   testTwo.txt

**To Run:** make && ./keys &lt;input.txt&gt; &lt;output.txt&gt;

**Results:**

This program will determine if there exists a key in a list such that
that key is the difference of any two other elements in that list. If
such a key is found, then that key is written to the specified output
file. If no such key exists, then a 0 byte file is written.

**Algorithm Overview:**

**\[Extra credit version\]**

This algorithm writes out all keys that are the difference of two other
items in a list. The algorithm will examine each element of the list as
a potential key. We start by sorting all of the elements in the list.
For this task, I used quicksort. For each potential key, the algorithm
considers a “low” index and a “high” index. The high index starts to the
right of the current key’s index while the low index starts one place to
the left of the high index. The difference of the values of the high
index and the low index is then computed. If this difference is less
than the key value, we decrement the index of low and try again. If low
index ever becomes equal to the key index, then it is decremented again.
If the difference is equal to the key, then we will continue to look for
other keys whose difference produces the same key. Then we proceed to
try and find the next key. If we don’t find the current key, we
decrement the low index until the difference computed is greater than
our key or the low index becomes smaller than the start index. For a
given high index, if we don’t find the key, we then increment the high
index. We continue this process until the high index exceeds the maximum
index of the list.
