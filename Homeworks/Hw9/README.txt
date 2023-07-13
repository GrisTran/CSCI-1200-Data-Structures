HOMEWORK 9: IMDB SEARCH


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(Nothing, just the Quadratic probing hash from lecture 20), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >


HASH FUNCTION DESCRIPTION
So for my HASH FUNTION, I choose Quadratic probing from lecture 20 to handle collision.
My Hash funtion will calculate the index by the year value percent the size of the Hash Table.
By doing this, I will be able to have uniform distribution of keys throughout the table. For example,
if size = 100, I will be able to get the index from 0-99. And to handle collision, I use Quadratic Probing
by plus i^2 to the index when insert. The idea of this is pretty much the same with linear probing instead of
using i^2 instead of i. However, If we are dealing with a Hash Table with large number of elements, quadratic probing
will find the collision position faster than the linear probing. And quadratic probing will help me prevent the case that all
of the keys are being putted in a specific area in the hash table (not uniformly distribute).





MISC. COMMENTS TO GRADER:  
Thank you for grading my HW!
(optional, please be concise!)


