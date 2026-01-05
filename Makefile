bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: Dict.h HashTable.h TableEntry.h testHashTable.cpp
	mkdir -p bin
	g++ -o bin/testHashTable Dict.h HashTable.h TableEntry.h testHashTable.cpp

bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	mkdir -p bin
	g++ -o bin/testBSTree BSTree.h BSNode.h testBSTree.cpp

bin/testBSTreeDict: Dict.h BSTreeDict.h BSNode.h TableEntry.h testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict BSTreeDict.h Dict.h BSNode.h TableEntry.h testBSTreeDict.cpp

clean:
	rm -rf *.o *.gch bin



