// Daniel Galarza 

#include <iostream>
#include <string>
#include "linkedset.h"

void displayBag(LinkedSet<std::string>& bag)
{
	std::cout << "The bag contains " << bag.getCurrentSize()
		<< " items:" << std::endl;
	std::vector<std::string> bagItems = bag.toVector();

	int numberOfEntries = (int)bagItems.size();
	for (int i = 0; i < numberOfEntries; i++)
	{
		std::cout << bagItems[i] << " ";
	}  // end for
	std::cout << std::endl << std::endl;
}  // end displayBag


int main(){
	LinkedSet<std::string> bag;
	LinkedSet<std::string> bag2;
	LinkedSet<std::string> bag3;
	LinkedSet<std::string> bag4;
	LinkedSet<std::string> bag5;

	std::string items[] = { "a", "s","d","f" };
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Adding " << items[i] << std::endl;
		bool success = bag.add(items[i]);
		if (!success)
			std::cout << "Failed to add " << items[i] << " to the bag." << std::endl;
	}

	std::string items2[] = { "r", "t", "k", "n" };
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Adding " << items2[i] << std::endl;
		bool success = bag2.add(items2[i]);
		if (!success)
			std::cout << "Failed to add " << items2[i] << " to the bag." << std::endl;
	}
	displayBag(bag);
	displayBag(bag2);

	std::cout << "Union" << std::endl;
	bag3 = bag.setUnion(bag2);
	displayBag(bag3);

	std::cout << "inter" << std::endl;
	bag4 = bag.setIntersection(bag2);
	displayBag(bag4);

	std::cout << "difference" << std::endl;
	bag5 = bag.setDifference(bag2);
	displayBag(bag5);

}// end main

