#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "data.h"

using namespace std;

int hashData(Data datapoint) {
	// It's pseudo-hashing.
	// This could be valid, since it is unique to each data point
	// and it should be evenly distributed among a large range
	// (there will be gaps due to the system of formatting, but
	// it should still keep bucket counts and collisions low)
	return stoi(datapoint.caseNum);
}

class HashMap {
	float load_factor = 0.75;
	int capacity = 1;
	int entryCount = 0;
	// Using lists so appending is O(1) time, and because we don't need random access 
	// (but we do need iterability, which is fine)
	list<Data>* storage = nullptr;

public:
	HashMap() {
		capacity = 1;
		entryCount = 0;
		// Array of lists of data
		storage = new list<Data>[capacity];
	}
	HashMap(vector<Data> given_datapoints) {
		capacity = 1;
		entryCount = 0;
		storage = new list<Data>[capacity];
		for (Data datapoint : given_datapoints) {
			insert(datapoint);
		}
	}
	void rehash() {
		int oldCapacity = capacity;
		capacity *= 2;
		list<Data>* newStorage = new list<Data>[capacity];
		for (int i = 0; i < oldCapacity; i++) {
			list<Data> oldList = storage[i];
			for (Data datapoint : oldList) {
				newStorage[hashData(datapoint) % capacity].push_back(datapoint);
			}
		}
		delete storage;
		storage = newStorage;
	}
	void insert(Data datapoint) {
		// First insert into the hashmap
		int newItemIndex = hashData(datapoint) % capacity;
		storage[newItemIndex].push_back(datapoint);
		entryCount++;

		// Check if need to rehash
		if (((float)entryCount / (float)capacity) >= load_factor) {
			rehash();
		}
	}
	// can iterate using any way to iterate over the list now B)
	list<Data>& getIterable() {
		list<Data> result;
		for (int i = 0; i < capacity; i++) {
			list<Data> oldList = storage[i];
			for (Data datapoint : oldList) {
				result.push_back(datapoint);
			}
		}
		return result;
	}
};