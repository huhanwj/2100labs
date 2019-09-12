#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASHTABLE_SIZE 10
int collision = 0;
typedef struct {
	int key;         // in this example, key is some long id
	char* value;     // value is a string
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
			printf("%2d: <%d,%s>\n", i, table[i]->key, table[i]->value);
		}
	}
}

int gePrime(int n) {
	int prob = rand() % n;
	if (prob < 2)
		return gePrime(n);
	for (int i = 2; i < n; i++) {
		if (prob % i == 0 && prob != i)
			return gePrime(n);
	}
	return prob;
}
int randomize(int a) {
	int ran = rand() % a;
	return ran+1;
}
int hashFunc(int key, int pa, int pb, int prime) {
	// turns the key into hash and returns it
	return ((pa * key + pb) % prime) % HASHTABLE_SIZE;   // modified hash function
}
void insert(KeyValuePair* table[], int key, int pa, int pb, int prime, char value[]) {
	// insert a key and value
	printf("inserting %d,%s to the table...\n", key, value);
	int hash = hashFunc(key, pa, pb, prime);
	int index = hash;
	int count = 1;
	int times = 1;
	while (times<=HASHTABLE_SIZE) {
		if (table[index] != NULL) {
			collision++;
			printf("collision with position %d! I refuse to do anything!\n",index);
			index++;
			if (index >= HASHTABLE_SIZE)
				index = 0;
			times++;
/*			index = hash;
			index+=(count*count);
			index = index % HASHTABLE_SIZE;
			count++; */
			continue;
		}
		else{
			// add the new key-value pair to the correct position
			printf("Entry inserted at position %d\n", index);
			KeyValuePair* newEntry = (KeyValuePair*)malloc(sizeof(KeyValuePair));
			newEntry->key = key;
			newEntry->value = value;
			table[index] = newEntry;
			break;
		}
	}
}

char* lookup(KeyValuePair* table[], int key,int pa,int pb,int prime) {
	// look up a key and return the value
	int hash = hashFunc(key,pa,pb,prime);
	int index = hash;
	int times = 1;
	if (table[index] != NULL) {
		if (table[index]->key == key)
			return table[index]->value;
		else{
			index++;
			while (times<=HASHTABLE_SIZE+1) {
				
				if (index >= HASHTABLE_SIZE)
					index = 0;
				if (table[index] == NULL)
					return NULL;
				if (table[index]->key == key)
					return table[index]->value;
				else
					index++;
				times++;
				/*index +=count * count;
				index = index % HASHTABLE_SIZE;
				if (count > HASHTABLE_SIZE * 3)
					return NULL;
				if (table[index] == NULL)
					return NULL;
				if (table[index]->key == key)
					return table[index]->value;
				else {
					count++;
					index = hash;
				}*/
			}// collision happened? should we do something?
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

int main()
{
	int pa, pb, prime = 0;
	int times = 1;
	srand(time(NULL));
	while (times <= 100) {
		pa = randomize(100);
		pb = randomize(100);
		prime = gePrime(100);
		KeyValuePair* hashtable[HASHTABLE_SIZE] = { NULL };
		insert(hashtable, 1450017,pa,pb,prime, "Ted");
		insert(hashtable, 1450345,pa,pb,prime, "Jerry");
		insert(hashtable, 1450191,pa,pb,prime, "Bill");
		insert(hashtable, 1450677,pa,pb,prime, "Perry");
		insert(hashtable, 1450922,pa,pb,prime, "Claire");
		insert(hashtable, 1450957,pa,pb,prime, "Arthur");

		printHashtable(hashtable);

		printf("Lookup %d - result: %s\n", 1450017, lookup(hashtable, 1450017,pa,pb,prime));
		printf("Lookup %d - result: %s\n", 9999999, lookup(hashtable, 9999999,pa,pb,prime));
		printf("Lookup %d - result: %s\n", 1450677, lookup(hashtable, 1450677,pa,pb,prime));
		printf("Lookup %d - result: %s\n", 1450957, lookup(hashtable, 1450957,pa,pb,prime));
		times++;
	}
	printf("\n \n \n");
	printf("%d\n", collision);
	return 0;
}

