#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//block size in sets of 4 bits (chars)
#define BLOCK_SIZE 4
#define BIT(x) (( 1 << x))
#define LEFT(x) ((x & 0xf0)>>4)
#define RIGHT(x) ((x & 0xf))

uint32_t sbox[16]={
	7, 8, 6, 12, 14, 1, 2, 13,
	0, 11, 15, 4, 10, 9, 3, 5,
};

uint32_t unsbox[16]={
	8, 5, 6, 14, 11, 15, 2, 0,
	1, 13, 12, 9, 3, 7, 4, 10

};


size_t readBlock(FILE *fp, char buffer[BLOCK_SIZE]);
void writeBlock(FILE *fp, char buffer[BLOCK_SIZE], int size);
int encrypt(uint32_t key, FILE *input_file, FILE *output_file);
int decrypt(uint32_t key, FILE *input_file, FILE *output_file);

int main(int argc, char ** argv){
	if(argc != 5 ){
		printf("Invalid Arguments\n\
				Usage: ./crypto <c/d> <key> <input_file> <output_file>\n\
				c = encrypt, d = decrypt\n");
	}

	//initialize arguments
	int bytes_written;
	uint32_t key = (uint32_t)strtol(argv[2], NULL, 16);
	FILE *input_file = fopen(argv[3], "rb");
	FILE *output_file = fopen(argv[4], "w+b");

	if(argv[1][0] == 'c'){
		bytes_written = encrypt(key, input_file, output_file);
	} else if(argv[1][0] == 'd'){
		bytes_written = decrypt(key, input_file, output_file);
	} else {
		printf("Invalid argument for crypt/decrypt:\n\
				%s given, c or d expected\n", argv[1]);
		return -1;
	}

	printf("Operation Completed!\n\
			%d bytes written\n", bytes_written);

	return 0;
}

size_t readBlock(FILE *fp, char buffer[BLOCK_SIZE]){
	return fread(buffer, sizeof(char), BLOCK_SIZE, fp);
}

void writeBlock(FILE *fp, char buffer[BLOCK_SIZE], int size){
	fwrite(buffer, sizeof(char), size, fp);
}


void encrypt_sbox(char buffer[BLOCK_SIZE]){
	for(int i = 0; i < BLOCK_SIZE; i++){
		buffer[i] = (sbox[LEFT(buffer[i])] << 4) | sbox[RIGHT(buffer[i])];
	}

}

void decrypt_sbox(char buffer[BLOCK_SIZE]){
	for(int i = 0; i < BLOCK_SIZE; i++){
		buffer[i] = (unsbox[LEFT(buffer[i])] << 4) | unsbox[RIGHT(buffer[i])];
	}

}

int encrypt(uint32_t key, FILE *input_file, FILE *output_file){
	int bytes_written = 0;
	char buffer[BLOCK_SIZE];
	int size;
	while((size = readBlock(input_file, buffer))){
		
		encrypt_sbox(buffer);
		(*(uint32_t*)buffer) ^= key;
		//write new block
		writeBlock(output_file, buffer, size);
		bytes_written += size;
	}

	return bytes_written;
}


int decrypt(uint32_t key, FILE *input_file, FILE *output_file){
	int bytes_written = 0;
	char buffer[BLOCK_SIZE];
	int size;
	while((size = readBlock(input_file, buffer))){
		
		(*(uint32_t*)buffer) ^= key;
		decrypt_sbox(buffer);

		//write new block
		writeBlock(output_file, buffer, size);
		bytes_written += size;
	}
	return bytes_written;
}
