HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (stackoverflow about print(std::cout)
and the dslist class from lab 6) you consulted in completing this assignment.

< https://stackoverflow.com/questions/27770050/using-stdostream-as-argument-to-a-print-function >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7.5 hours >



TESTING & DEBUGGING STRATEGY:
Debugging:
For debugging, my strategy is I wont move to the next funtion until I make sure that it work
well. I also print out every value in the loop at first in my fuction so I can see how the process
work in every single loop and make sure that it goes right with how I want it to be. For example:
in the erase_fuction, I print every pair of elements_array[i] and elements_array[i+1] along with the
loop so I can make sure that it work exactly like what I have in my prep diagram. I also use gdb and 
valgrind as tools to help me find the memory leak. Sometimes when I could not find where the leak is, I
will just go over some specific function that might cause the leak by set every others to comment. I found
this actually pretty helpful since it save me alot of time finding where the leaks are.

Testing:
Beside from the provided test, my test focuses on making sure that the unrolledll will work on other type of value
and other functions like the copy constructor or the clear function will work well. I use char type value for my test
and test the erase, operator"=" and clear,etc.. on it. I also have some test cases to make sure that the copy constructor 
will make the copy list independent and make sure that the copy list and the original list wont be affected by others changes.

Please be concise!  



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

Order notation:
dict:
num_elements(number of real elements in the array): n
max num elements in arra: N
number of nodes in the list: nd


size(): O(1)

empty(): O(1)

front(): O(1)

back(): O(1)

begin(): O(1)

end(): O(1)

push_front(const T& v): best: O(1) worst: O(n-1) <=> O(n)

pop_front(): best: O(1) worst: O(n-1) <=> O(n)

push_back(const T& v): Best: O(1) Worst: O(n)

pop_back(): Best: O(1) Worst: O(n)

copy_list(const UnrolledLL<T>& old): Best: O(1) Worst: O((n-1)ne) <=> O(n*nd)

destroy_list(): Best: O(1) Worst: O(n-1) <=> O(n)

erase(): O(n-1) <=> O(n)

insert(): O(n + N)

split(): O(n/2) <=> O(n)


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.

The reason this improve the memory usage is bc it will prevent the worst case which is
there is only 1 real elements in a big array which will waste alot of memory.
My initial idea is that if a node is not half filled, it will take the elements from
the node next to it untill it fill. And if the node is not half filled and the node next
to it is not half filled then I will merge both of them into 1 node. However, I was not able
to pull out this idea so I can go only with the split function only which will only move the elements from
the next node to the current node until it is half filled. I was also not able to do this idea in
the erase and insert function since it will mess up the itereator return which
I was not able to resolved. I believe that the only implement that need to use resize() are
push_front, pop_front, insert, erase since the push_back and pop_back only modify the last
node or even if it modify the first node, the resize() is useless since there is only
1 node in the list. I put the

//Uncomment to test the extra credit
	/*
	if(head_->next_ != NULL){
		resize();
	}
	*/

under push_front() and pop_front function. Pls uncomment it to test this resize()
function. Im really sorry for this inconvenience but I have to do that to prevent 
failing the summity gradable since the output of this is different from the output file
I hope that you can give me a hint in the comment of my grading.
Tysm!


MISC. COMMENTS TO GRADER:  
Thank you for grading my Hw!
Optional, please be concise!


