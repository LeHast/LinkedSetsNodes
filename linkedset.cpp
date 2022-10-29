
#include "linkedset.h"
#include "Node.h"
#include <cstddef>

template<class ItemType>
LinkedSet<ItemType>::LinkedSet() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedSet<ItemType>::LinkedSet(const LinkedSet<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else
	{
		// Copy first node
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
		origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer

		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while

		newChainPtr->setNext(nullptr);              // Flag end of chain
	}  // end if
}  // end copy constructor





template<class ItemType>
LinkedSet<ItemType>::~LinkedSet()
{
	clear();
}  // end destructor





template<class ItemType>
bool LinkedSet<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty





template<class ItemType>
int LinkedSet<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize





template<class ItemType>
bool LinkedSet<ItemType>::add(const ItemType& newEntry)
{
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)        
	Node<ItemType>* nextNodePtr = new Node<ItemType>();

	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  // New node points to chain
	//Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code
	headPtr = nextNodePtr;          // New node is now first node
	itemCount++;

	Node<ItemType>* temp = headPtr;
	Node<ItemType>* check = headPtr;

	temp = temp->getNext();
	while (temp != nullptr) {
		while (temp != nullptr) {
			if (temp->getItem() == check->getItem()) {
				std::cout << "No duplicates allow" << std::endl;
				exit(EXIT_FAILURE);
			}
			temp = temp->getNext();
		}
		check = check->getNext();
		temp = check;
		temp = temp->getNext();
	}

	return true;
}  // end add





template<class ItemType>
std::vector<ItemType> LinkedSet<ItemType>::toVector() const
{
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end toVector





template<class ItemType>
bool LinkedSet<ItemType>::remove(const ItemType& anEntry)
{
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem)
	{
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());

		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	} // end if

	return canRemoveItem;
}  // end remove





template<class ItemType>
void LinkedSet<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear





template<class ItemType>
bool LinkedSet<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

/* ALTERNATE 1
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   return getFrequencyOf(anEntry) > 0;
}
*/
/* ALTERNATE 2
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   int i = 0;
   while (!found && (curPtr != nullptr) && (i < itemCount))
   {
	  if (anEntry == curPtr->getItem())
	  {
		 found = true;
	  }
	  else
	  {
		 i++;
		 curPtr = curPtr->getNext();
	  }  // end if
   }  // end while

   return found;
}  // end contains
*/





// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedSet<ItemType>::getPointerTo(const ItemType& anEntry) const
{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} // end while

	return curPtr;
} // end getPointerTo





template<class ItemType>
LinkedSet<ItemType>& LinkedSet<ItemType>:: setUnion(const LinkedSet<ItemType>& link)const {
	LinkedSet<ItemType>* firstLink = new LinkedSet<ItemType>;
	
	Node<ItemType>* linkPtr1 = headPtr;
	Node<ItemType>* linkPtr2 = link.headPtr;

	while (linkPtr1 != nullptr){
		firstLink->add(linkPtr1->getItem());
		linkPtr1 = linkPtr1->getNext();
	}
	while (linkPtr2 != nullptr) {
		firstLink->add(linkPtr2->getItem());
		linkPtr2 = linkPtr2->getNext();
	}

	return*firstLink;
}





template<class ItemType>
LinkedSet<ItemType>& LinkedSet<ItemType>::setIntersection(const LinkedSet<ItemType>& link)const {
	LinkedSet<ItemType>* firstLink = new LinkedSet<ItemType>;

	Node<ItemType>* linkPtr1 = headPtr;
	Node<ItemType>* linkPtr2 = link.headPtr;

	while (linkPtr1 != nullptr) {
		while (linkPtr2 != nullptr){
			if (linkPtr1->getItem() == linkPtr2->getItem()) {
				firstLink->add(linkPtr2->getItem());
			}
			linkPtr2 = linkPtr2->getNext();
		}
		linkPtr1 = linkPtr1->getNext();
		linkPtr2 = link.headPtr;
	}

	return*firstLink;
}






template<class ItemType>
LinkedSet<ItemType>& LinkedSet<ItemType>::setDifference(const LinkedSet<ItemType>& link)const {
	LinkedSet<ItemType>* firstLink = new LinkedSet<ItemType>;
	bool bPass = true;
	Node<ItemType>* linkPtr1 = headPtr;
	Node<ItemType>* linkPtr2 = link.headPtr;

	while (linkPtr1 != nullptr) {
		while (linkPtr2 != nullptr) {
			if (linkPtr1->getItem() == linkPtr2->getItem()){
				bPass = false;
				break;
			}
			linkPtr2 = linkPtr2->getNext();
		}
		if (bPass) {
			firstLink->add(linkPtr1->getItem());
		}
		bPass = true;
		linkPtr1 = linkPtr1->getNext();
		linkPtr2 = link.headPtr;
	}


	return*firstLink;

}




template<class ItemType>
LinkedSet<ItemType>& LinkedSet<ItemType> :: operator=(const LinkedSet<ItemType>& rightHandSide) {
	this->clear();
	headPtr = rightHandSide.headPtr;
	itemCount = rightHandSide.itemCount;

	return *this;
}
