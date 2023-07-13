HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(no one), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

I find out the solution for large window case base on the way
a problem I have solved indexing the variable. I dont know 
if it is counted as a resources since they are not relatable.

https://www.hackerrank.com/challenges/largest-rectangle/problem

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?

It should require w*m*p memory. O(w*m*p).

What is the order notation for performance (running time) of each of
the commands?

Command "load"
	- Window 2:
		For window = 2, the load command will first go through all of the word in the text file 
	to form the data map, in every loop the data map will find the word which is O(logn) and insert if the
	word is not yet in the map.
	=> Average case: O(n*log(n))
	=> Worst Case: O(n*2log(n))
	=> O(n*log(n))

	-Window 3:
		Same idea with window 2 instead of it have to call map find 2 times in average.
		=>Average: O(n*2log(n))
		=>Worst: O(n*4log(n))
		=>O(n*log(n))

Command "print"
	- Window 2:
		In this case we will first call find to check if there is a sentence[0] in it or not.
	After than, if there is, we will print the words out.
	=> O(log(n)+p)
	
	- Window 3:
		In this case, sentence.size will be larger so we will need to consider it in our runtime.
	The logic is the same with window 2 instead that we will have to call find w-1 =<> w times to check.
	=>O(w*log(n) + p)

Command "generate" "most common"
	- Window 2:
		First we call find to check and find the first start point, and then loop x times to find the
	next most_common word, in the end of every loop, we call find again to find the next start point.
	=> O(log(n) + x*log(n)) <=> O(x*log(n))
	
	-Window 3:
		Same idea with window 2, there is a special case where we have to do a initial logn which is
	sentence.size() = 1 but we forget about it since it is small compare to the main runtime.
	=>O(x*log(n))

Command "generate" "random"
	Same for win2 and 3:
		For x times, we will run through the next word and add it into a vector, and then call rand() to 
	find a random word and then use find on that random word to get to the next loop.
	=> O(x*(log(n)+p))


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).

	I have managed to do the implementation support for any window size as long as the window size is 
smaller than the number of words in the text file. Here is my idea:

So basiclly to be considered as the next word of a window phrase, they word in the window all have to stand next to
each others so I have 2 helper funtions that help me solve this extra credit case.
1. getIndicates(vector<string> str, int size )
	This function will go through all of the words in the text and return a map with a vector<string> of size
window - 1 as the key value and a vector<int> to store the index of the first word(*) of the keyvalue vector<string>.
For example, i will use number to save spaces: 
I have a vector<int> to represent the words in the text file {1,2,3,1,2,3}
After calling the getIndicates with window size = 4 I will have a map like this:
({1,2,3},{0,3})
({2,3,1},{1})
({3,1,2},{2})
We can see that I have manage to find all of the phrase contain "window" strings and the start index of it.
The task now is easy, I will use my second helper function which is solve_all_win( map<vector<string>, vector<int> > indicates, int size, vector<string> str).
With this function, I will be able to find the next word for every single window size phrase because the word next to the phrase will
have the index of (head index(*) + window size - 1) which is very easy to find since we already have the head index(*) and window size.
To fullfill the "print" of all sentence.size() < window size, I will just need to have a vector to store all of the return answer from
the solve_all_win funtion from window size = 2 to window size = n(n < total number of words in the textfile).

O notation:
LoadSampleText_LargeWindowCase: O(n)
getIndicates: O((n-w) * w) <=> O(n*w)
solve_all_win: O((n-w) * p) <=> O(n*p)/ worst: O((n-w)*p*log(n))




MISC. COMMENTS TO GRADER:  
Thank you so much for grading my hw. If its possible, if I got in wrong in the O notation part, I hope that you can show me the right runtime
so I can have a review on it since I got like some of my Notation wrong last homeworks and I have no idea what is the wrong part. Thank you so much
for your understanding!
(optional, please be concise!)


