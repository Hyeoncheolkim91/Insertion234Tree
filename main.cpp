#include <iostream>
#include"entry.h"

using namespace std;

#include"234tree.h"

int main() {
	int values[] = { 1, 12, 8, 2, 25, 6, 14, 28, 17 ,7 ,52, 16, 48, 68, 3, 26, 29,
	53, 55, 45 };
	Tree* tree = new Tree();
	for (int i = 0; i < sizeof(values) / sizeof(int); i++) {
		int key = values[i];
		Entry* entry = new Entry(key, key);
		cout << entry->getKey() << endl;
		tree->insert(entry);
		tree->print();
	}
	tree->print();

	system("pause");

	return 0;
}