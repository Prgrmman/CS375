**Name:** Jonathan Terner

**Assignment:** Assignment 4 Programming parts

**Class:** CS 375

**Date:** 11/4/16

**PART A:**

![](media/image1.wmf){width="5.64375in" height="5.847916666666666in"}

**Algorithm:**

The idea is to conduct a breadth first search starting on the nodes that
have an in-degree of 0. An observation here is that the minimum number
of semesters is equal to the length of longest directed path of the DAG
plus , where To find the length of the longest directed path, we conduct
breadth first traversal on multiple source nodes (cs1, cs2, cs3). Each
semester contains classes that are not ancestors of each other, or in
other words, we don’t support taking a prerequisite for a class at the
same time as that class.

Because of this property, we maximize the number of classes by taking
all classes with the same “distance” from the source node at the same
time. Breadth first search will give us the distance of each node from
the source, so to find the minimum number of semesters, we simply need
to add 1 to the distance of the deepest node from the source.

**Pseudo code:**

int minSemester(int matrix\[SIZE\]\[SIZE\], node nodes\[SIZE\])

finalDistance ← 0

queue ← NULL

for each vertex v with in-degree = 0 do

queue.enqueue(v)

color\[v\] = grey

dist\[v\] = 0

while(queue not empty) do

v ← head(queue)

for u ←0 to SIZE -1 do

if(isEdge(v,u) and color\[u\] = white) then

color\[u\] ← grey

dist\[u\] ← dist\[v\] + 1

finalDistance ← dist\[u\]

queue.enqueue(u)

color\[v\] ← red

queue.dequeue()

return finalDistance + 1

END

**To Run:**

make semest && ./semest

**Results:**

“The minimum number of semesters is 5”

**PART B1:**

**Algorithm:**

To solve this problem, I performed Gaussian elimination on all sets of
equations and then further reduced them to find solutions. For each
solution pair, I checked to see if it satisfied all of the constraints.
From the list of feasible solutions, I selected the solution that
minimized the objective function

The constraints were:

-   60x + 60y &gt;= 300

-   12x + 6y &gt;= 36

-   10x + 30y &gt;= 90

Objective function: z = 0.12x + 0.15y

**To Run:**

make linear && ./linear

**Results:**

“Drink 3 cup(s) of drink X and 2 cup(s) of drink Y for a cost of \$0.66”
