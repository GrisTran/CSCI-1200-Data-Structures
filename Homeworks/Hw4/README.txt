HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  < Gris Tran >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(no one ), and all of the resources (lecture pdf 8 and 9 ) you consulted in completing 
this assignment.

< lecture 8 and 9 pdf >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 hours >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order
  t = runtime
  r = num of food remove

Include a short description of your order notation analysis.

add_order:
Best case: O(p) if there is only 1 items in the order and only
1 order in the order list.
Avg case: O(o+2q) <=> O(q) 
o for the sorttime and q for the 2 loop of order_items.

add_item:
Best case: O(1) if there is only 1 food in the cooking list
Avg: O(c) for the sortfood.

print_orders_by_time:
O(2o*q) <=> O(o*q)
o for the sort and the loop
q for the printOrder()

print_orders_by_id:
O(2o*q) <=> O(o*q)
o for the sort and the loop
q for the printOrder()

print_kitchen_is_cooking:
O(c) for the loop
printFood() is only O(1)

print_kitchen_has_completed:
O(d) for the loop
printFood() is only O(1)

run_until_next:
t: count/checktime
o: ordertime() / oi loop
c: foodtime()
o*d: CanFillOrder()
if(!food_cooking.empty()) = t*(o+c)
else if(!orders.empty()) = o*(o*d+r) = o^2*d
else = O(1)
+
if(checkfill == 0) = o + t(o+c) = t(o+c)
=> O(o^2)

run_for_time:
o: ordertime && checkexpire
c: foodtime && checkfood
r: fillorder
t: run_time
o*d: CanFillOrder()
if(run_time> 0) = t*(2o+2c+o*(r+o*d)) <=> t*o^2*d
else if(run_time == 0) = (t*(o+o^2*d)) <=> t*o^2*d
=> O(o^2)




MISC. COMMENTS TO GRADER:  
Thank you for grading my hw!
Optional, please be concise!






