#ifndef __ENTRY__
#define __ENTRY__

class Entry {
	int key;
	int value;

public:
	Entry(int key, int value) {			//constructor of entry
		this->key = key;				//set key and value
		this->value = value;
	}
	bool equals(Entry* other) {
		if (other == NULL) {			//check duplicated or not
			return false;
		}
		return key == other->key;
	}
	int getKey() {
		return key;				//get key
	}
};
#endif