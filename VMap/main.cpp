#include <iostream>
#include "VMap.h"

int main() {
	//Testing all functionality (printTree is a work in progress)
	
	//Create the map
	VMap<int, std::string> testMap;

	//Display properties
	std::cout << "Size: " << testMap.size() << std::endl;
	std::cout << "Is empty: " << testMap.isEmpty() << std::endl;

	//Add elements
	testMap.put(6, "six");
	testMap.put(2, "two");
	testMap.put(9, "nine");

	//BST visualization
	std::cout << "Tree: " << std::endl;
	testMap.printTree();
	std::cout << std::endl;
	
	//Display properties again
	std::cout << "Size: " << testMap.size() << std::endl;
	std::cout << "Is empty: " << testMap.isEmpty() << std::endl;

	//Print out map
	std::cout << "Map contents: " << testMap << std::endl;
	std::cout << std::endl;

	//Retrieving values from key
	std::string* search1 = testMap.get(1);
	std::string* search2 = testMap.get(3);
	std::string* search_fail = testMap.get(4);

	//Display results if found
	if (search1) std::cout << *search1 << std::endl;
	if (search2) std::cout << *search2 << std::endl;
	if (search_fail) {
		std::cout << *search_fail << std::endl;
	}
	else {
		std::cout << "Key 4 not found!" << std::endl;
	};

	std::cout << std::endl;

	//Retrieving keys from value (not efficient)
	int* search_val1 = testMap.getKey("one");
	int* search_val2 = testMap.getKey("three");
	int* search_val_fail = testMap.getKey("four");

	//Display results
	if (search_val1) std::cout << *search_val1 << std::endl;
	if (search_val2) std::cout << *search_val2 << std::endl;
	if (search_val_fail) {
		std::cout << *search_val_fail << std::endl;
	}
	else {
		std::cout << "value 'four' not found!" << std::endl;
	};

	std::cout << std::endl;

	//Display key set
	std::vector<int> testKeySet = testMap.getKeySet();
	for (int i = 0; i < testKeySet.size(); i++) {
		std::cout << "Key " << (i + 1) << ": " << testKeySet[i] << std::endl;
	}
	std::cout << std::endl;

	//Display value set
	std::vector<std::string> testValueSet = testMap.getValueSet();
	for (int i = 0; i < testValueSet.size(); i++) {
		std::cout << "Value " << (i + 1) << ": " << testValueSet[i] << std::endl;
	}
	std::cout << std::endl;

	//Add some more entries and replace
	testMap.put(6, "six_new");
	testMap.put(4, "four");
	testMap.put(7, "seven");

	//Print map
	std::cout << "Map with new: " << testMap << std::endl;
	
	//Remove some values
	testMap.remove(6);
	testMap.remove(4);

	//Display map and properties
	std::cout << "Size: " << testMap.size() << std::endl;
	std::cout << "Map with removed: " << testMap << std::endl;

	//BST visualization
	testMap.printTree();
	std::cout << std::endl;

	//Clear map
	testMap.clear();

	//Display properties
	std::cout << "Is empty: " << testMap.isEmpty() << std::endl;
	std::cout << "Size: " << testMap.size() << std::endl;
	std::cout << "Map final: " << testMap << std::endl;
	
	return 0;
}
