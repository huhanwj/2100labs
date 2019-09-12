#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/md5.h>
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
// Get some ideas from https://github.com/jhayes14/RainbowTable/blob/master/rainbow_table.c
char* reduce(char* hash, int no) {
	// This is a kind of simple reduce function, which cuts the continuous 6 words of the hashed value.
	// parameter i indicates the starting postion of the substring cutted.
	static char sub[7];
	int position = 0, length = 6, c = 0;
	while (c < length) {
		sub[c] = hash[(position + c + no) % 32]; //modulus for connect the tail and the head.
		c++;
	}
	sub[c] = '\0';
	return sub;
}
char* HashFunction(char pass[]) {
	// Using OpenSSL MD5
	unsigned char hash[MD5_DIGEST_LENGTH];
	char tmp[3] = { '\0' };
	char *buf = (char*)calloc(33,sizeof(char*));
	MD5((unsigned char*)pass, strlen(pass), hash);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {//convert the original MD5 function output to 32bit readable words
		sprintf(tmp, "%2.2x", hash[i]);
		strcat(buf, tmp);
	}
	return buf;
}
void rainbowtable() {
	//this function generates the rainbow. For simple implementation, I just use limited numbers of starting text.
	int chain = 32;
	//below is the starting text.
	unsigned char* store[] = { "hapezmj","soljisolji","password","test123123","passwrd123","123456789","abcdabcd123","abcd1234","testtesttest" };
	FILE* fptr;
	fptr = fopen("table.txt", "w");
	if (!fptr) {
		printf("Error!\n");
		exit(1);
	}
	char* text = { '\0' };
		char* H = { '\0' };
		char* R = { '\0' };
	for (int i = 0; i < 9; i++) {
		text = store[i];
		fprintf(fptr, "%s,", text);
		R = text;
		for (int j = 0; j < chain; j++) {
			H = HashFunction(R);
			R = reduce(H, j);
			free(H);
		}
		fprintf(fptr, "%s\n", R);
	}
	fclose(fptr);
}
char* spilt(char* line, int num) { //split the starting text and the ending text
	static char* sp=NULL;
	for (sp = strtok(line, ","); sp; sp = strtok(NULL, ",\n")) {
		if (!--num)
			return sp;
	}
	return NULL;
}
typedef struct pass_and_reduced {
	char* first;
	char* last;
}F_L;
F_L find(char* check) { //check whether the text is in the rainbow table
	int found = 0;
	FILE* list = fopen("table.txt", "r");
	if (!list) {
		printf("Can't open the table!\n");
		return;
	}
	char line[1000];
	char* head = NULL;
	char* tail = NULL;
	char store_head[20];
	char store_tail[20];
	F_L Pass_and_tail;
	while (fgets(line,100,list)){
		char* temp1 = _strdup(line);
		head = spilt(temp1, 1);
		strcpy(store_head, head);
		free(temp1);
		char* temp2 = _strdup(line);
		tail = spilt(temp2, 2);
		strcpy(store_tail, tail);
		free(temp2);
		if (strcmp(check, store_tail) == 0) {
			found = 1;
			break;
		}
	}
	
	fclose(list);
	if (found == 1) {
		Pass_and_tail.first = store_head;
		Pass_and_tail.last = store_tail;
		return Pass_and_tail;
	}
	else {
		Pass_and_tail.first = "NoMatch";
		Pass_and_tail.last = "NoMatch";
		return Pass_and_tail;
	}
}
void hack(char* attack_hash){//this function does the attack
	if (strlen(attack_hash) < 32) {
		printf("Wrong Input!\n");
		return;
	}
	int found = 0;
	int position = 0;
	char* H = { '\0' };
	char* R = { '\0' };
	char* found_first = { '\0' };
	char* found_last = { '\0' };
	H = attack_hash;
	R = reduce(H, 31);
	F_L check;
	char store[20];
	for (int i = 1; i <= 32; i++) {
		check = find(R);
		H = attack_hash;
		if (strcmp(check.last, "NoMatch") != 0) {
			found = 1;
			found_first = check.first;
			found_last = check.last;
			position = i;
			break;
		}
		for (int j = 31 - i; j < 32; j++) {
			if (j == 31 - i){
				R = reduce(H, j);
			}
			else {
				char temp[10] = { "\0" };
				strcpy(temp, R);
				H = HashFunction(temp);
				R = reduce(H, j);
				free(H);
			}
		}
	}
	if (found) {
		strcpy(store, found_first);
		char* next_hash = { '\0' };
		char* next_text = { '\0' };
		next_text = store;
		for (int i = 0; i < 32 - position; i++) {
			next_hash = HashFunction(next_text);
			next_text = reduce(next_hash, i);
			free(next_hash);
		}
		printf("The original password is: %s\n", next_text);
	}
	else {
		printf("Attack unsuccessful!\n");
	}
}
int main() {
	rainbowtable();
	hack("0c6fb8d3ed2829c9c1b1c382f6782a0d");
	/*simple implementation, I just cut some MD5 values from the generating function 
	and put it to test whether it can find the corresponding password properly.*/
	hack("5f7e5e959010b44be0b97a3eac0899e0");

	return 0;
}