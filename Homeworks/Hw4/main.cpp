// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert>
#include <iostream>
#include <string>
#include <list>

#include "Order.h"
#include "Food.h"

typedef list<Order> OrderList;
typedef list<Food> KitchenList;
typedef list<Order>::iterator odl;
typedef list<Food>::iterator fdl;
typedef list<Food>::const_iterator cfdl;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;
typedef std::list <KitchenList::iterator> RemoveIterator;
typedef OrderFillList::const_iterator rdl;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);

//This function will help run the time_pass from the Order class on all the Order value in the orders list.
void ordertime(OrderList &orders){
	for(odl oitr = orders.begin(); oitr != orders.end(); oitr++){
		(*oitr).time_pass();
	}
}

//This fuction will help run the ftime_pass from the Food class on all the Food value in the food_cooking list.
void foodtime(KitchenList &food){
	for(fdl fitr = food.begin(); fitr != food.end(); fitr++){
		(*fitr).ftime_pass();
	}
}


//Checkfood funtion
//This function will check if there is a food finish cooking or not
//If yes, this food will be remove from the cooking list and move to the completed list
void checkfood(KitchenList &cookfood, KitchenList &comfood){
	for(fdl fitr = cookfood.begin(); fitr != cookfood.end();){
		if((*fitr).getCtime() == 0){
			comfood.push_back(*fitr);
			std::cout<<"Finished cooking "<<(*fitr).getName()<<std::endl;
			fitr = cookfood.erase(fitr);
		}
		else{
			fitr++;
		}
	}
}

//Checkexpire funtion
//This function will check if there is a order expire or not
//If yes, this order will be remove from the order list 
void checkexpire(OrderList &ord){
	for(odl oitr = ord.begin(); oitr != ord.end(); oitr++){
		if((*oitr).getTime() == 0){
			std::cout<<"Order # "<<(*oitr).getId()<<" expired."<<std::endl;
			oitr = ord.erase(oitr);
		}
	}
}

//Fillorder funtion
//This function will fill the input order &oi and remove the food in the food_completed list
void Fillorder(odl &oi, OrderFillList &food_remove, KitchenList &food_completed, OrderList &orders){
	std::cout<<"Filled order #"<<(*oi).getId()<<std::endl;
    oi = orders.erase(oi);
    for(rdl fi = food_remove.begin(); fi != food_remove.end(); fi++){
      	std::cout<<"Removed a "<<(**fi).getName()<<" from completed items."<<std::endl;
      	food_completed.erase((*fi));
	}
}



int main() {
	//Main Variables
  OrderList orders;                //List of orders
  KitchenList food_cooking;        //List of cooking food
  KitchenList food_completed;      //List of food completed
  OrderFillList food_remove;       //List of food to remove
 
  std::string token;
  //While cin order
  while (std::cin >> token) {
  	
    if (token == "add_order") {
      //Id , time , num of item
      int id, promised_time, n_items = 0;
      //item names
      std::string next_item;
      //list to store item name (next_item)
      std::list <std::string> order_items;
	  //Read in the id, time, and num of items	
      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);
	  //Read in the orders	
      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
      }
      //Push back the order into the Order list - orders
      orders.push_back(Order(id, promised_time, n_items, order_items));
      orders.sort(sorttime);
      //Print out the order that just being received
      std::cout<<"Received new order #"<<id<<" due in "<<promised_time<<" minute(s):"<<std::endl;
      for(ls itr = order_items.begin(); itr != order_items.end(); itr++){
      	std::cout<<"  "<<*itr<<endl;
	  }
    } 
    
	else if (token == "add_item") {
	  //Creating variable cooktime && foodname
      int cook_time = -1;
      std::string name;
      //Read in cooktime and foodname
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);
      //Push back the food into the cooking list
      food_cooking.push_back(Food(cook_time, name));
      food_cooking.sort(sortfood);
      std::cout<<"Cooking new "<<name<<" with "<<cook_time<<" minute(s) left."<<std::endl;
    } 
    
    //Print out the order in the order by the smallest time. Tie break by name.
	else if (token == "print_orders_by_time") {
		//Resort the order list incase the print id was called right before it.
	  orders.sort(sorttime);
      std::cout<<"Printing "<<orders.size()<<" order(s) by promised time remaining:"<<std::endl;
      for(odl itr = orders.begin(); itr != orders.end(); itr++){
      	(*itr).printOrder();
	  }
    } 
    
    //Print out the order in the order by the smallest id.
	else if (token == "print_orders_by_id") {
	  orders.sort(sortid);
      std::cout<<"Printing "<<orders.size()<<" order(s) by ID:"<<std::endl;
      for(odl itr = orders.begin(); itr != orders.end(); itr++){
      	(*itr).printOrder();
	  }
    } 
	
	//Print out the food that is being cooked.
	else if (token == "print_kitchen_is_cooking") {
      std::cout<<"Printing "<<food_cooking.size()<<" items being cooked:"<<std::endl;
      for(fdl itr = food_cooking.begin(); itr != food_cooking.end(); itr++){
      	(*itr).printFood();
	  }
    } 
	
	//Print out the food that is completely cooked.
	else if (token == "print_kitchen_has_completed") {
      std::cout<<"Printing "<<food_completed.size()<<" completely cooked items:"<<std::endl;
      for(fdl itr = food_completed.begin(); itr != food_completed.end(); itr++){
      	(*itr).printCfood();
	  }
    } 
	
	//Run for a specific time
	else if (token == "run_for_time") {
	//Resort the order list incase the print id was called right before it.
	  orders.sort(sorttime);
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);
      std::cout<<"===Starting run of "<<run_time<<" minute(s)==="<<std::endl;
      //If runtime not 0
      if(run_time > 0){
	      for(int i = 0; i<run_time; i++){
	      	//Decrease time in orders and food
	      	ordertime(orders);
	      	foodtime(food_cooking);
	      	//Check if any food completed
	      	checkfood(food_cooking, food_completed);
	      	//Check if any order can be filled
	      	for(odl oi = orders.begin(); oi != orders.end(); ){
	      		bool check = CanFillOrder((*oi), food_completed, food_remove);
	      		if(check){
	      			Fillorder(oi, food_remove, food_completed, orders);	
				}
				else{
					oi++;
				}
			}
			//Check if any order expires
			checkexpire(orders);
		  }
		}
		//If runtime == 0, do every check once to see if there is any food or order have value 0
		else if(run_time == 0){
			//Check if any food completed
			checkfood(food_cooking, food_completed);
			//Check if any order can be filled
	      	for(odl oi = orders.begin(); oi != orders.end(); ){
	      		bool check = CanFillOrder((*oi), food_completed, food_remove);
	      		if(check){
	      			Fillorder(oi, food_remove, food_completed, orders);	
				}
				else{
					oi++;
				}
			}
			//Check if any order expires
			checkexpire(orders);
		}
		
	  std::cout<<"===Run for specified time is complete==="<<std::endl;
    } 
	
	//Run until next event in order
	//1. food cooking can be finished
	//2. at least 1 order can be filled
	//3. no food cooking no order can be filled => exxpire the order w the smallest time left
	//4. if no order no food cooking => no event to do => skip 
	else if (token == "run_until_next") {
	//Check value to see if we need case 3
	  int checkfill = 0;
      std::cout << "Running until next event." << std::endl;
      //If the food_cooking not  empty => at least 1 food can be finished => case 1
      if(!food_cooking.empty()){
      	checkfill += 1;
      	//The food with the smallest cooking time
      	fdl first = food_cooking.begin();
      	int count = (*first).getCtime();
      	for(int i = 0; i<count; i++){
      		//Run the food and the order through the time it takes to cook first
      		ordertime(orders);
      		foodtime(food_cooking);
		}
		std::cout<<"Finished cooking "<<(*first).getName()<<std::endl;
		//Take first into the completed list and delete it from the cooking list
		food_completed.push_back(*first);
		food_cooking.erase(first);
		std::cout<<count<<" minute(s) have passed."<<std::endl;
   		}
   	  //If there is no food can be finished, we check if there is any order can be fill if there is at least 1 order in the list => case 2
   	  else if(!orders.empty()){
   	  	for(odl oi = orders.begin(); oi != orders.end();){
   	  		//Check if any order can be fill
   	  		bool check = CanFillOrder((*oi), food_completed, food_remove);
   	  		if(check){
      			Fillorder(oi, food_remove, food_completed, orders);	
      			std::cout<<"0 minute(s) have passed."<<std::endl;
      			//If there is one, fill it and break the loop bc we only run to 1 next event
      			//If there is no order that can be filled, checkfill += 1 which will lead us to case 3
      			checkfill += 1;
      			break;
			}
			else{
				oi++;
			}
		}
	  }
	  //If there is no food or order => there is no events to process => case 4
	  else{
	  	checkfill += 1;
	   	std::cout<<"No events waiting to process."<<std::endl;
	   }
	   //If there are orders in the list but none of them can be filled, we expire the one with lowest waiting time => case 3
	  if(checkfill == 0){
	  	orders.sort(sorttime);
	  	odl first = orders.begin();
	  	int checktime = (*first).getTime();
	  	for(int i = 0; i<checktime; i++){
      		ordertime(orders);
      		foodtime(food_cooking);
		}
		std::cout<<"Order # "<<(*first).getId()<<" expired."<<std::endl;
		orders.erase(first);
		std::cout<<checktime<<" minute(s) have passed."<<std::endl;
	  }
  	}
}		

  return 0;
}


bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

