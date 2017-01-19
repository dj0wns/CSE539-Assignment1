#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//block size in sets of 4 bits (chars)
#define BLOCK_SIZE 4

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

int encrypt(uint32_t key, FILE *input_file, FILE *output_file){
	int bytes_written = 0;
	char buffer[BLOCK_SIZE];
	int size;
	while((size = readBlock(input_file, buffer))){
		
		//TODO: implement real encryption
		//increment by 1
		for(int i = 0 ; i < size; i++){
			buffer[i] += 1;
		}

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
		
		//TODO: implement real encryption
		//increment by 1
		for(int i = 0 ; i < size; i++){
			buffer[i] -= 1;
		}

		//write new block
		writeBlock(output_file, buffer, size);
		bytes_written += size;
	}
	return bytes_written;
}
