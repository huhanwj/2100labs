#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <stdlib.h>
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")


/*
NOTE: This is a simplified rainbow table with just one reduction function.
	  Normally, a rainbow table would use multiple reduction functions to
	  decrease the chance of collisions
*/

char* reduce(char* hashed) {
	char sub[1000];
	int position = 1, length = 5, c = 0;

	while (c < length) {
		sub[c] = hashed[position + c - 1];
		c++;
	}
	sub[c] = '\0';

	return sub;
}

char* get_substring(char* hashed) {
	char sub[1000];
	int position = 1, length = 16, c = 0;

	while (c < length) {
		sub[c] = hashed[position + c - 1];
		c++;
	}
	sub[c] = '\0';

	return sub;
}

char* hasha1(char* plain) {
	//char * p;
	//p = plain;
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH];
	char buf[SHA_DIGEST_LENGTH * 2];

	memset(buf, 0x0, SHA_DIGEST_LENGTH * 2);
	memset(temp, 0x0, SHA_DIGEST_LENGTH);

	SHA1((unsigned char*)plain, strlen(plain), temp);

	for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf((char*) & (buf[i * 2]), "%02x", temp[i]);
	}
	//printf("SHA1 of %s is %s\n", plain, buf);
	char* hashed;
	hashed = buf;
	return hashed;
}

void rainbow_table() {
	// create rainbow table
	const char* filepath=NULL;
	const char* data=NULL;
	int i;
	int j;
	int links = 200;
	char* plains_to_hash[] = { "12345678", "password", "testtestest", "passwrd123", "123456789" };

	FILE* fptr;
	fptr = fopen("table.txt", "w");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	for (i = 0; i < 5; ++i) {
		char* plain=NULL;
		char* H = NULL;
		char* R=NULL;
		plain = plains_to_hash[i];
		//printf("\n");
		//printf("Initial Plain: %s\n", plain);
		fprintf(fptr, "%s,", plain);
		R = plain;
		for (j = 0; j <= links; ++j) {
			H = hasha1(R);
			//printf("Hashed %d %s\n", j, H);
			R = reduce(H);
			//printf("Reduced %d %s\n", j, R);
		}
		//printf("Final Hash (after %d cycles): %s\n", links, H);
		//printf("\n");
		fprintf(fptr, "%s\n", H);
	}
	fclose(fptr);
}

char* getfield(char* line, int num) {
	char* tok;
	for (tok = strtok(line, ",");
		tok && *tok;
		tok = strtok(NULL, ",\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}


typedef struct Pass_and_Hash
{
	char* frstpss;
	char* lsthsh;
} Pass_and_Hash_t;

Pass_and_Hash_t read_final_hashes(char* check_hash) {

	int found = 0;
	FILE* myFile = fopen("table.txt", "r");
	char line[512];
	char* placer1=NULL;
	char* placer2=NULL;

	char check_hash_Arr[20];
	char new_placer2_Arr[20];
	while (fgets(line, 512, myFile)) {
		// NOTE strtok clobbers tmp
		char* tmp1 = _strdup(line);
		placer1 = getfield(tmp1, 1);
		free(tmp1);
		char* tmp2 = _strdup(line);
		placer2 = getfield(tmp2, 2);
		free(tmp2);

		strcpy(new_placer2_Arr, placer2);
		while (strlen(new_placer2_Arr) != 16) {
			new_placer2_Arr[strlen(new_placer2_Arr) - 1] = 0; // remove last empty char to allow equality test
		}
		//printf("%lu\n", strlen(new_placer2_Arr));

		strcpy(check_hash_Arr, check_hash);
		while (strlen(check_hash_Arr) != 16) {
			check_hash_Arr[strlen(check_hash_Arr) - 1] = 0; // remove last empty char to allow equality test
		}
		//printf("%lu\n", strlen(check_hash_Arr));

		int r;
		r = strcmp(new_placer2_Arr, check_hash_Arr);
		//printf("R %d\n", r);

		if (strcmp(new_placer2_Arr, check_hash_Arr) == 0) {
			//printf("%s\n", new_placer2_Arr);
			found = 1;
			break;
		}

	}
	fclose(myFile);
	if (found == 1) {
		//printf("%d\n", found);
		//printf("First plain is %s, Match is : %s\n", placer1, check_hash);
		Pass_and_Hash_t Pass_and_Hash;
		Pass_and_Hash.frstpss = placer1;
		Pass_and_Hash.lsthsh = check_hash;
		//printf("%s %lu\n", placer1, strlen(placer1));
		//printf("%s %lu\n", check_hash, strlen(check_hash));
		return Pass_and_Hash;
	}
	else {
		//printf("%s\n", "No Match");
		Pass_and_Hash_t Pass_and_Hash;
		Pass_and_Hash.frstpss = "No Match";
		Pass_and_Hash.lsthsh = "No Match";
		return Pass_and_Hash;
	}
}


char* online_crack(char* attack_hash) {
	int found = 0;
	int i;
	int j=0;
	int k=0;
	char* H=NULL;
	char* R=NULL;
	char* found_first_plain=NULL;
	char* found_end_hash=NULL;
	char* new_place=NULL;
	int attempts = 1000;
	H = attack_hash;
	//printf("Attack hash: %s, len %d\n", H, strlen(H));
	// (repeat 1000 times)check if hash equals last hash, if it
	// does, then stop, if it doesn't then reduce hash and re-hash
	// and check again
	char check_red_Arr[20];
	char check_pass_Arr[20] = {""};
	char check_hash_Arr[20] = { "" };

	for (i = 0; i < attempts; i++) {
		//char * check = read_final_hashes(H);
		Pass_and_Hash_t res;
		res = read_final_hashes(H);
		char* check_pass;
		char* check_hash;
		check_pass = res.frstpss;
		check_hash = res.lsthsh;
		//printf("%s\n", check_hash);
		//printf("%s\n", check_hash);

		if (strcmp(check_hash, "No Match") != 0) {
			found = 1;
			found_first_plain = check_pass;
			//printf("%s\n", "F");
			found_end_hash = check_hash;
			break;
		}
		R = reduce(H);
		//printf("red %s, len %lu\n", R, strlen(R));
		strcpy(check_red_Arr, R);
		//printf("red %s, len %lu\n", check_red_Arr, strlen(check_red_Arr));
		H = hasha1(check_red_Arr);
		printf("");
	}
	//if( found == 1){
	//    printf("Attack Hash: %s (%lu len), First plaintext: %s (%lu len), Last hash in link: %s (%lu len)\n", attack_hash, strlen(attack_hash), found_first_plain, strlen(found_first_plain), found_end_hash, strlen(found_end_hash));
	//}
	//else{
	//    printf("Nothing found after %d attempts", attempts);
	//}
	if (found == 1) {
		//printf("Attack Hash: %s (%lu len), First plaintext: %s (%lu len), Last hash in link: %s (%lu len)\n", attack_hash, strlen(attack_hash), found_first_plain, strlen(found_first_plain), found_end_hash, strlen(found_end_hash));
		char* next_hash=NULL;
		char* next_reduce=NULL;
		next_reduce = found_first_plain;
		found_end_hash[strlen(found_end_hash) - 1] = 0;
		//printf("First plaintext %s\n", found_first_plain);
		//printf("End Hash %s, %lu\n", found_end_hash, strlen(found_end_hash));
		//printf("Attack Hash %s, %lu\n", attack_hash, strlen(attack_hash));
		int ret=0;
		//char attack_plain[20];
		//for( j = 0; j < 20; ++j ){
		while (ret != 40) {
			next_hash = hasha1(next_reduce);
			//printf("Next Redu %s, %lu\n", next_reduce, strlen(next_reduce));
			//printf("Next Hash %s, %lu, Attack Hash %s, %lu\n", next_hash, strlen(next_hash), attack_hash, strlen(attack_hash));
			ret = strcmp(next_hash, attack_hash);

			if (ret == 40) {
				break;
			}
			next_reduce = reduce(next_hash);
		}
		printf("The original password/plaintext is: %s\n", next_reduce);
	}
	else {
		printf("No match found after %d attempts\n", attempts);
	}

	return 0;
}




int main(int argc, char* argv[]) {

	//build rainbow_table
	rainbow_table();
	//crack hash
	if (strlen(argv[1]) != 16) {
		printf("%s\n", "Hash must be of length 16!");
		exit(1);
	}
	online_crack(argv[1]);


	//for (int i=1; i< argc; i++) {
	//    //printf("\nhash_to_crack_%d: %s", i, argv[i]);
	//    printf("\n");
	//    online_crack(argv[i]);
	//    }
	//printf("\n");

	return 0;
}