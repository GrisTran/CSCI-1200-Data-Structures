HOMEWORK 8: ROPES


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(Only hw pdf and sample dslist from lecture 18/19.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
N = number of nodes in the rope
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
avg(p) = The average path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
Balanced Rope:
Unbalanced Rope:
Both of balanced rope and unbalanced rope will have the same run time
as O(n) since both case will have to copy the whole string
	Best case will be O(1) if copy a empty rope
	=>O(n) for both

Construct from Node*:
For this case we will have to calculate the size after we steal the node. To find this,
we go right until we cant. For unbalanced tree, it will take longer or shorter since the right side 
could be super long or super short compare to the left side.
Balanced Rope:
	O(p)
Unbalanced Rope:
	maybe O(p) or O(avg(p)) or O(1)

Index:
We will subtract the variable i on our way until we reach a leaf node
so I think the runtime should be the same with "Construct from Node*"
Balanced Rope:
	O(p)
Unbalanced Rope
	maybe O(p) or O(avg(p)) or O(1)

Report:
In my index funtion, I call index j-i times to find the string and then return it.
So the runtimes should be j-i times * index runtime. This funtion pass in a string and
the return string will have length j-i so I think I can call j-i as m.
Balanced Rope:
	O(m*p)
Unbalanced Rope
	maybe O(m*p) or O(avg(p)*m) or O(m)

iterator operator++:
Balanced Rope:
Unbalanced Rope:
Should be O(1) for both case since it only move to the next direction
	=>O(1) for both

Split:
First I call find_node_in_index to get the path of cut which will be O(p)
Then I call the Rope(Node* p) which will be O(p) too.
Then I run the loop for p-1 times and call concat at every loop which should be O(p*N)
Then I reconstruct 2 rope which will be O(2N*p).
Balanced Rope:
	=> O(p + p + p*N + 2p*N) <=> O(p*N)
Unbalanced Rope
	Same logic with Balanced instead that the runtime of each funtion maybe different.
	=> O(p*N) or maybe O(avg(p)*N)

Concat:
For this function, I just pass left and right pointer of the new node which
is O(1), the only runtime which is big should be when I calculate the weight of 
the new rope which is the total value of all the leaf in the left side of it. Which
should be O(N/2) for balanced rope and O(N) for unbalanced rope
Balanced Rope:
	O(N/2) <=> O(N)
Unbalanced Rope:
	O(N) or maybe O(1) or maybe O(N/2)


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
I just use funtion print and print_string directly in my cpp file so I can see
how the function are working and fix them to make them work the way I want. For memory
bugs, I use valgrind, gdb, and DrMemory as a help functions to find the bugs.



MISC. COMMENTS TO GRADER:  
Thank you for grading my HW!
(optional, please be concise!)

