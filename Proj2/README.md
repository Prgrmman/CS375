**Name**: Jonathan Terner

**Date:** 10/4/2016

**Assignment:** Assignment 2 (Part B)

**Package name:** jonathan\_terner\_cpp\_used.tar.gz

**Package contents:**

-   dist.cpp

-   point.cpp

-   point,h

-   timer.cpp

-   timer.h

-   makefile

-   readme.doc

**To Run:** make && ./dist &lt;input file&gt; &lt;output file&gt;

**Algorithm Description:**

*Brute force:* The brute force algorithm works by comparing the
distances between all points. The distance formula establishes a
symmetric relation between all pairs of points, such that to the
distances between n points needs n choose 2 operations.

*Divide and conquer:* This algorithm is much more efficient for larger
data sets when compared to Brute force. This algorithm starts by sorting
the points by x coordinate so as to draw a vertical line between the
points. This algorithm divides the set into two roughly equal sections,
finds the shortest distance in each section, and returns the points that
produce the min distance from each side. After the algorithm takes the
shortest distance “d” from the left and the right and uses it to from a
bounding box around the center line. The code finds all points that have
an x distance strictly less than d. We then compare the distance of
those points. While this would ordinarily seem like a n\^2 comparison,
this comparison is actually linear. This is because we also consider the
y distance in terms of the bounding length d, which means that at most,
we need to consider a max of 6 points within the bounding box. The y
coordinates are sorted so as to improve the efficiency of this step. If
we find a distance d’ within the bounding box such that d’ &lt; d, then
we return the points with distance d’. Otherwise, we return the points
with distance d. As a side note, my code uses DBL\_MAX to refer to
infinite distance.

**Major code:**

In dist.cpp

Ln 126-190 divideAndConquer: function using divide and conquer approach

Ln 103-124 bruteForce: function using brute force to finds points with
min distance

Ln 211-229 clostInStrip: utility function used by divideAndConquer.

**Results:**

This program determines that shortest distance between a pair of points
amongst a set of points using a brute force and divide and conquer
approach. The code will not run if the input file contains 1 or less
points. My code will take the run the brute force and then the divide
and conquer approach, displaying the time taken for each operation. It
will then print the indexes of the shortest distance and that distance
to the specified output file.

**Analysis:**

The time complexity for brute force is (n choose 2) which gives it
quadratic time complexity. O(n\^2)

The time complexity for divide and conquer is O(nlogn).

**Notes:** My code is designed to read in 3 dimensional points. However,
I only consider the 2 dimensional case. So my code will only work if it
is fed 3 dimensional points.
