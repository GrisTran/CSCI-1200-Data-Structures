HOMEWORK 6: STAR BATTLE


NAME:  < Gris Tran >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(Nia in Lab 9), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< https://study.com/academy/lesson/how-to-solve-5-choose-2.html >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # 22 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:

	My algorith is build on the idea that for each zone, pick the most valid s points from each zone,
if s>1 then each group of s point should not have any point stand next to each other. So basicly
the getIndicateByZone() will return C s t(s up, t down) group of point which equivilant to
s!/t!(s-t)!. However, after zone by zone, this runtime get improve since there are cases get remove
in the middle of the function so the runtime for this one should be log(s!/t!(s-t)!) because it get better 
after zone by zone. After that,I run my loop which will check log(s!/t!(s-t)!) group to see if they are valid
for the puzzle, the IndicateIsValid() funtion in the loop runtime will be O(s * (w+h+8)) which <=> O(s*(w+h)). The 
recursion recur for z zones and call the check_all_board() with run time O(w*h) function at every successful cases.
So totaly I beleive the run time of my Algorithm should be 
O(z*s!/t!(s-t)!*log(s!/t!(s-t)!)*w*h).

(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone ( t) 
The number of stars per zone(s)? 
etc.


DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
I have prepare 3 different puzzle for three intersting test cases that I have prepare in my fuction

Case 1:If there is a zone have less or equal blocks than the num of required star and star > 1 => no solution 
(equal is wrong 2 since no block can be next to each other).
In this puzzle the number of star rq for each zone is 2 and A only have 1 blocks. 
3 2
A 1
0 0
B 5
1 0
0 1
1 1
0 2
1 2

Case 2: If the area of the puzzle is less than or equal to the num of required star => no solution
since the number of blocks should always be > star.
In this puzzle the number of star rq for each zone is 6 and the area of the puzzle is 2*3 = 6 => no solution
because even if we can fit them in the puzzle, no star can be next to each other.
3 2
A 2
0 0
1 0
B 4
0 1
1 1
0 2
1 2

Case 3: If the number of columns or row < star and the number of zone >= star => no solution.
It is because if a puzzle with row or column < star, it can only fit "row" or "column" zone no matter
how big it is.
In this puzzle the required star for each zone is 3. Even though the number of col are massive, there is
no way to fit 3 star in each zone since the number of zone is 3 which >= star =>no solution.
2 13
X 8
0 0
1 0
2 0
3 0
4 0
5 0
6 0
0 1
K 6
1 1
2 1
3 1
4 1
5 1
6 1
Y 12
7 0
8 0
9 0
10 0
11 0
12 0
7 1
8 1
9 1
10 1
11 1
12 1
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
Less than or slightly above 1 second:
custom1.txt
custom2.txt
custom3.txt
sporcle1.txt

More than 1 minutes:
twonot1.txt

More than 10 minutes:
twonot2.txt

For my additional puzzle, the performance is great since I dont have to run the 
recursion function to get the solution. Beside from the read data from input file and 
set up the vectors, the run time for my interesting_case() is just O(1) to get the solution
which make my the performance of my additional puzzle less than 0.1 second.

# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.



MISC. COMMENTS TO GRADER:  
First I want to apologise since I dont really sure if I have finished this Readme file in the best way
or not. And I personally can not find a solution to solve for all of the test case in less than 10 seconds.
I hope that you can give me some advices about a way that I can solve this Homework better. Thank you so much
for your time and understanding!
(optional, please be concise!)


