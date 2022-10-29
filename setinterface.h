#ifndef SETINTERFACE_H_
#define SETINTERFACE_H_

#include <vector>

template<class ItemType>
class SetInteface
{
public:
	/** Gets the current number of entries in this array.
	 @return  The integer number of entries currently in the array. */
	virtual int getCurrentSize() const = 0;

	/** Sees whether this array is empty.
	 @return  True if the array is empty, or false if not. */
	virtual bool isEmpty() const = 0;

	/** Adds a new entry to this array.
	 @post  If successful, newEntry is stored in the array and
		the count of items in the array has increased by 1.
	 @param newEntry  The object to be added as a new entry.
	 @return  True if addition was successful, or false if not. */
	virtual bool add(const ItemType& newEntry) = 0;

	/** Removes one occurrence of a given entry from this array,
		if possible.
	 @post  If successful, anEntry has been removed from the array
		and the count of items in the array has decreased by 1.
	 @param anEntry  The entry to be removed.
	 @return  True if removal was successful, or false if not. */
	virtual bool remove(const ItemType& anEntry) = 0;

	/** Removes all entries from this array.
	 @post  array contains no items, and the count of items is 0. */
	virtual void clear() = 0;

	/** Tests whether this array contains a given entry.
	 @param anEntry  The entry to locate.
	 @return  True if array contains anEntry, or false otherwise. */
	virtual bool contains(const ItemType& anEntry) const = 0;

	/** Empties and then fills a given vector with all entries that
		are in this array.
	 @return  A vector containing all the entries in the array. */
	virtual std::vector<ItemType> toVector() const = 0;

	/** Destroys this array and frees its assigned memory. (See C++ Interlude 2.) */
	virtual ~SetInteface() { }
}; // end arrayInterface

#endif