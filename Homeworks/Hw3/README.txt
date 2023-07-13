HOMEWORK 3: CONNECT FOUR


NAME:  	Gris Tran


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(no one), and all of the resources (lecture note 6,7,8 + vec.h file on the course material) you 
consulted in completing this assignment.

<lecture note 6,7,8 + vec.h file on the course material>

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7-8 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
Worst case: O(n*m)
Best case: O(1) (if no new row or column were added)

insert (including checking for connected four)
O(n*m)

numTokensInColum
O(n)

numTokensInRow
O(n)

numColumns
O(1)

numRows
O(1)

print
O(n*m)
n = col
m = row

clear
O(n*m + 2*n) or O(n*m) (bc when n is larger +(2*n) is not important anymore)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  
Ans: Valgrind
How did you test the 
"corner cases" of your Matrix class design & implementation?
Ans: I just went through the valid position and check if its vertically 
or horizontally win.


MISC. COMMENTS TO GRADER:  

This is the hw that help me learn the most so far. Can you give me extra credit
if RPI win in the student test case. Tysm!
(optional, please be concise!)

