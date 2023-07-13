HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< https://www.cplusplus.com/ >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |  nlogn   |  n^2     |  nlogn   |   nlogn  |   nlogn  | l^2*n^2  |
| vector   |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |  nlogn   |  n^2     |  nlogn   |  nlogn   |  nlogn   |  l^2*n^2 |
| list     |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |   nlogn  |   nlogn  |   nlogn  |  nlogn   |  nlogn   |n*l^2log(n*l^2)|
| bst      |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |  nlogn   |     X    | nlogn    |   nlogn  | n+flogn  |     X    |
| pq       |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |     X    |      n   |     n    |      X   |    X     |     X    |
| hash     |          |          |          |          |          |          |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >
	Vector 
*Sort:
10000 words w length of 5: 0.1718 sec
100000 words w length of 5: 2.3718 sec
10000 words w length of 50: 0.2018 sec
=> Dominent term is n as expected <=> the number of elements

*Remove Dub:
10000 words w length of 5: 1 sec
100000 words w length of 5: 60.4513 sec
10000 words w length of 50: 1.17 sec
=> Dominent term is n as expected <=> the number of elements

*Mode:
10000 words w length of 5: 0.023 sec
100000 words w length of 5: 0.06 sec
10000 words w length of 50: 0.015 sec
=> Dominent term is n as expected <=> the number of elements

*First f sort:
sort 500 10000 words w length of 5: 0.24 sec
sort 500 100000 words w length of 5: 2.9871 sec
sort 5000 10000 words w length of 5: 0.2879 sec
=> Dominent term is n as expected <=> the number of elements

*longest sub:
1000 words w length of 3-5: 0.125 sec
10000 words w length of 3-5: 12.46 sec
1000 words w length of 30-50: 6.42188 sec
=> Dominent term is n. Im quite suprise with this!

	List
*Sort:
10000 words w length of 3-5: 0.21875 sec
100000 words w length of 3-5: 2.2018 sec
10000 words w length of 30-50: 0.2833 sec
=> Dominent term is n as expected <=> the number of elements

*Remove Dub:
10000 words w length of 5: 1.45 sec
100000 words w length of 5: 121.795 sec
10000 words w length of 50: 1.17188 sec
=> Dominent term is n as expected <=> the number of elements

*Closest Pair:
10000 words w length of 5: 0.0023 sec
100000 words w length of 5: 0.0817 sec
10000 words w length of 50: 0.0035 sec
=> Dominent term is n as expected <=> the number of elements

*First f sort:
sort 500 10000 words w length of 5: 0.264 sec
sort 500 100000 words w length of 5: 3.41 sec
sort 5000 10000 words w length of 5: 0.313 sec
=> Dominent term is n as expected <=> the number of elements

*longest sub:
1000 words w length of 3-5: 0.145 sec
10000 words w length of 3-5: 12.962 sec
1000 words w length of 30-50: 0.15 sec
=> Dominent term is n as expected <=> the number of elements

	BST
*Sort:
10000 words w length of 3-5: 0.17 sec
100000 words w length of 3-5: 2.10938 sec
10000 words w length of 30-50: 0.25 sec
=> Dominent term is n as expected <=> the number of elements

*Remove Dub:
10000 words w length of 5: 2.1788 sec
100000 words w length of 5: 97.795 sec
10000 words w length of 50: 2.23 sec
=> Dominent term is n as expected <=> the number of elements

*Closest Pair:
10000 words w length of 5: 0.0023 sec
100000 words w length of 5: 0.0817 sec
10000 words w length of 50: 0.0035 sec
=> Dominent term is n as expected <=> the number of elements

	Priority Queue
*Sort:
10000 words w length of 3-5: 0.17 sec
100000 words w length of 3-5: 2.10938 sec
10000 words w length of 30-50: 0.25 sec
=> Dominent term is n as expected <=> the number of elements

*Mode:
10000 words w length of 5: 0.0093 sec
100000 words w length of 5: 0.109 sec
10000 words w length of 50: 0.015 sec
=> Dominent term is n as expected <=> the number of elements

*Closest Pair:
10000 int w length of 5: 0.015 sec
100000 int w length of 5: 0.078 sec
10000 int w length of 50: 0.01545 sec
=> Dominent term is n as expected <=> the number of elements

	Hash
*Mode:
10000 words w length of 5: 0.015625 sec
100000 words w length of 5: 0.06 sec
10000 words w length of 50: 0.015 sec
=> Dominent term is n as expected <=> the number of elements

DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


< insert your discussion of the results, including your answers to the
above questions >
	Most of the performance match with my predicted O Notation for the data tpe
and operation. However, there is 1 operation that suprised me which is the longest_sub_string.
I thought that the length of string and the num of elements should be equal. However, based on
the runtime test, the num of elements(n) is the dominent term.
	There are two data types that have the same Big ‘O’ Notation for all of the test operations
which are list and vector. Based on the testing result above, vector perform faster in most of the test cases
compared to list. I have do 2 more test to understand better about the gap between these 2 data structures.
The additional test is that I will test the runtime of the sort operation for 1 million elements of int and string
for both list and vector. Here is the result of the test:
1000000 string 3-5:
	vector: 23.875
	list: 21.2812
1000000 int 3-5:
	vector: 20.63 sec
	list: 20.9688
First, I want to talk about the overall performance for all operation. I strongly believe that the reason vector
perform better than list in these 6 operations is that all of these 6 operations except for remove duplicates does
not remove or add the data contained in the data structure. From this, we can easily understand why vector perform better since
it has the O(1) random access while list does not. For my additional test, we can see that list actually work better with string data
in larger test case. I believe that it is because of the copy constructor in list is a pointer operation so it makes sense that list
can handle string better than vector. Overall, from the tests for these 2 data structures, I have had a deeper understanding for them.
Vector strong point is that it can have a fast O(1) accessing in any order and list have better performance on moving, inserting elements
through the container. These results 100% will impact your data structure choices for future programming projects. I will prefer
vector for functions and algorithms that need alot of accessing and I will use list for functions and algorithms that need alot of editing
inside the container (inserting, removing, moving).


MISC. COMMENTS TO GRADER:  
Thank you so much for grading my hw!
Optional, please be concise!
