
/** ADT bag: Link-based implementation.
	@file LinkedBag.h
	Listing 4-3 */
#ifndef LINKED_SET_
#define LINKED_SET_

#include "setinterface.h"
#include "Node.h"

template<class ItemType>
class LinkedSet : public SetInteface<ItemType>
{
private:
	Node<ItemType>* headPtr; // Pointer to first node
	int itemCount;           // Current count of bag items

	// Returns either a pointer to the node containing a given entry
	// or the null pointer if the entry is not in the bag.
	Node<ItemType>* getPointerTo(const ItemType& target) const;

public:
	LinkedSet();
	LinkedSet(const LinkedSet<ItemType>& aBag); // Copy constructor
	virtual ~LinkedSet();                       // Destructor should be virtual
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	std::vector<ItemType> toVector() const;
	LinkedSet& setUnion(const LinkedSet<ItemType>&)const;
	LinkedSet& setIntersection(const LinkedSet<ItemType>&)const;
	LinkedSet& setDifference(const LinkedSet<ItemType>&)const;
	LinkedSet& operator=(const LinkedSet<ItemType>& set);
}; // end LinkedBag

#include "linkedset.cpp"
#endif