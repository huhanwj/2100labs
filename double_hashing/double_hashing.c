#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE 10
#define _CRT_SECURE_NO_WARNINGS
typedef struct {
	char key[4];     // in this example, key is always 3 characters long!
	int value;     // since we are implementing a set, value is 1 or 0
} KeyValuePair;

void printHashtable(KeyValuePair* table[]) {
	// print out the hash table so that you will see if you have done
	// things correctly!

	int i;
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		if (table[i] == NULL) {
			printf("%2d: -\n", i);
		}
		else {
			printf("%2d: <%s,%d>\n", i, table[i]->key, table[i]->value);
		}
	}
}
int power(int base, int power) {
	int i = 1;
	while (i < power) {
		base *= base;
		i++;
	}
	if (power > 0)
		return base;
	else
		return 1;
}
int hashFunc(char key[]) {
	// we assume key is always 3 characters long and always valid characters!
	int returnValue = 0;
	int n = strlen(key);
	for (int i = 0; i < n; i++) {
		returnValue += key[i] * power(31, n - i - 1);
	}
	returnValue = returnValue % HASHTABLE_SIZE;
	// TODO implement
	return returnValue;
}

int hashFunc2(char key[]) {
	// same assumption as hashFunc
	int returnValue = 0;
	int n = strlen(key);
	for (int i = 0; i < n; i++) {
		returnValue += key[i] * power(37, n - i - 1);
	}
	returnValue = returnValue % 7 + 1;
	// TODO implement
	return returnValue;
}

void insert(KeyValuePair* table[], char key[]) {
	// insert a key and value
	printf("inserting %s to the set...\n", key);
	int hash = hashFunc(key);
	int index = hash;
	if (table[index] != NULL) {
		printf("collision! we should use double hashing this time\n");
		// TODO implement
		for (int i = 1; i < HASHTABLE_SIZE;) {
			int newIndex = (index + hashFunc2(key) * i) % HASHTABLE_SIZE;
			if (table[newIndex] != NULL)
				i++;
			else {
				printf("Entry inserted at position %d\n", newIndex);
				KeyValuePair* newEntry = (KeyValuePair*)malloc(sizeof(KeyValuePair));
				strcpy(newEntry->key, key);
				newEntry->value = 1;
				table[newIndex] = newEntry;
				break;
			}
		}
		// HINT:  int newIndex = (index + hashFunc2(key) * i) % HASHTABLE_SIZE;
		return;
	}
	else {
		// add the new key-value pair to the correct position
		printf("Entry inserted at position %d\n", index);
		KeyValuePair* newEntry = (KeyValuePair*)malloc(sizeof(KeyValuePair));
		strcpy(newEntry->key, key);
		newEntry->value = 1;
		table[index] = newEntry;
	}
}

int lookup(KeyValuePair* table[], int key) {
	// look up a key and return 1 if it is in the set, 0 otherwise
	int hash = hashFunc(key);
	int index = hash;
	if (table[index] != NULL) {
		if (strcmp(table[index]->key, key) == 0)
			return 1;
		else {
			// collision happened? should we do something?
			for (int i = 1; i < HASHTABLE_SIZE;) {
				int newIndex = (index + hashFunc2(key) * i) % HASHTABLE_SIZE;
				if (strcmp(table[newIndex]->key, key) == 0)
					return 1;
				else {
					i++;
				}
			}
		}
			// TODO implement
		return 0;
	}
	else {
		return 0;
	}
}

int main()
{

	KeyValuePair* hashtable[HASHTABLE_SIZE] = { NULL };

	insert(hashtable, "Ted");
	insert(hashtable, "Joe");
	insert(hashtable, "May");
	insert(hashtable, "Ken");
	insert(hashtable, "Bob");

	printHashtable(hashtable);

	printf("Lookup %s - result: %d\n", "Ted", lookup(hashtable, "Ted"));
	printf("Lookup %s - result: %d\n", "Joe", lookup(hashtable, "Joe"));
	printf("Lookup %s - result: %d\n", "Bob", lookup(hashtable, "Bob"));
	printf("Lookup %s - result: %d\n", "Ken", lookup(hashtable, "Ken"));
	return 0;
}

