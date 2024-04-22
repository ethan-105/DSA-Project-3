#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
//#include "data.h"

using namespace std;

unsigned int hashData(string key) {
	// If key is able to be turned to a number, just stoi it
	try {
		return stoi(key);
	} catch (invalid_argument e) {
		// otherwise, do some fun stuff with bit shifting to mess around
		// Smaller keys are risky, but long ones should work quite well
		// expecting to overflow quite often, but should be alright to drop biggest bit
		unsigned int result;
		for (int i = 0; i < key.size(); i++) {
			int shift = (5*i) % (8 * 3); // int is 4 bits
			int val = int(key[i]);
			result += val << shift;
		}
		return result;
	}
}

template<typename T>
class HashMap {
public:
	struct ItemPair {
		string key;
		T value;
		ItemPair(string key, T value) : key(key), value(value) {};
	};

private:
	float load_factor = 0.75;
	unsigned int capacity = 1;
	unsigned int entryCount = 0;
	// Using lists so appending is O(1) time, and because we don't need random access 
	// (but we do need iterability, which is fine)
	list<ItemPair>* storage = nullptr;

public:
	HashMap() {
		capacity = 1;
		entryCount = 0;
		// Array of lists of data
		storage = new list<ItemPair>[capacity];
	}
	void rehash() {
		unsigned int oldCapacity = capacity;
		capacity *= 2;
		list<ItemPair>* newStorage = new list<ItemPair>[capacity];
		for (int i = 0; i < oldCapacity; i++) {
			list<ItemPair> oldList = storage[i];
			for (ItemPair pair : oldList) {
				newStorage[hashData(pair.key) % capacity].push_back(pair);
			}
		}
		//delete storage; // Complains when I do this
		storage = newStorage;
	}
	void insert(string key, T value) {
		// First insert into the hashmap
		unsigned int newItemIndex = hashData(key) % capacity;
		ItemPair pair(key, value);
		storage[newItemIndex].push_back(pair);
		entryCount++;

		// Check if need to rehash
		if (((float)entryCount / (float)capacity) >= load_factor) {
			rehash();
		}
	}
	// can iterate using any way to iterate over the list now B)
	list<ItemPair> getIterable() {
		list<ItemPair> result;
		for (int i = 0; i < capacity; i++) {
			list<ItemPair> oldList = storage[i];
			for (ItemPair pair : oldList) {
				result.push_back(pair);
			}
		}
		return result;
	}
	unsigned int getSize() { return entryCount; }
};