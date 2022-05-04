/*
 * mcdaniels_raymond_hw4.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Raymond McDaniels
 */
#include<stdio.h>
#include <iostream>
#include <fstream>
#include "Cipher.h"
using namespace std;

int main(int argc, char** argv) {

	char userChoice;
	int exitCase = 0;
	int keySize = 0;
	int count = 0;
	int counter = 0;
	char* key = new char[128];
	char* fileNameE = new char[50];
	char* fileNameD = new char[50];
	char* fileNameI = new char[50];
	char* fileNameO = new char[50];

	char* buffer = new char[1024]; // Buffer, needs to be large for large text documents
	char* buffer2 = new char[1024]; // Another buffer for decryption and writing to new document
	FILE * stream; // File pointer for reading from first document
	FILE * stream2; // File pointer for writing to first encrypted document
	FILE * write; // File pointer for reading from first encrypted document
	FILE * write2; // File pointer for writing to 2nd document after decryption

	// While loop for executing menu
	while(exitCase != 1) {
	printf("Pick an option:\ne. Encrypt\nd. Decrypt\nf. Exit\n");
	fflush(stdout);
	scanf("%c", &userChoice);
	fflush(stdin);
	switch(userChoice) {
	//First case for encrypting a text file
	case 'e':
	{
		//Resetting key size to 0
		keySize = 0;
		//Questions for file input name, key, and file output name.
		printf("What is the name of the file to encrypt? (Example.txt)\n");
		fflush(stdout);
		scanf("%s", fileNameE);
		printf("What is your Cipher key? (Max 128 chars)\n");
		fflush(stdout);
		scanf("%s", key);
		printf("What is the name of the file to output? (Example.txt)\n");
		fflush(stdout);
		scanf("%s", fileNameD);

		//Simple for loop for getting key size without having to ask user
		for(int i = 0; key[i] != '\0'; i++){
			keySize++;
		}

		/*
		 * Stream used for opening up and reading ("r") file and then using a count to find how many variables are in document, storing in buffer
		 */
		stream = fopen(fileNameE, "r");
		count = fread(buffer, sizeof(char), 100000, stream);
		fclose(stream);
		//Setting last element in text document to \0 so garbage doesnt get printed out at end.
		buffer[count] = '\0';

		//Calling Cipher object with buffer, key, and document size and key size
		Cipher* cipher = new Cipher(buffer, key, count, keySize);
		//Encrypting the buffer
		cipher->Encrypt();

		/*
		 * write used for openining document for writing, using the buffer  to write.
		 */
		write = fopen(fileNameD, "w");
		fwrite(buffer, sizeof(char), count, write);
		fclose(write);
		printf("Encryption Successful\n");
		fflush(stdout);
		fflush(stdin);

	}
		break;
		//Case for decrypting
	case 'd':
	{
		//Resetting key size to 0
		keySize = 0;

		//Menu for file input name, key, and file output name
		printf("What is the name of the file to Decrypt? (Example.txt)\n");
		fflush(stdout);
		scanf("%s", fileNameE);
		printf("What is your Cipher key?\n");
		fflush(stdout);
		scanf("%s", key);
		printf("What is the name of the file to output? (Example.txt)\n");
		fflush(stdout);
		scanf("%s", fileNameD);

		//For loop for finding size of key without asking user
		for(int i = 0; key[i] != '\0'; i++){
					keySize++;
		}

		/*
		 * stream 2 used for opening file, storing contents in buffer and counter keeps track of total characters.
		 */
		stream2 = fopen(fileNameE, "r");
		counter = fread(buffer2, sizeof(char), 100000, stream2);
		fclose(stream2);
		//Setting last char to \0 so garbage isn't printed out in the end.
		buffer2[counter] = '\0';

		//printf("\n%s\n", buffer2);

		//Creating a second instance of Cipher object with new parameters used for decrypting.
		Cipher* cipher2 = new Cipher(buffer2, key, counter, keySize);
		cipher2->Decrypt();

		/*
		 * write2 used to open up output file and write successfully to it with contents of decrypted buffer
		 */
		write2 = fopen(fileNameD, "w");
		fwrite(buffer2, sizeof(char), counter, write2);
		fclose(write2);
		printf("Decrypted Successful\n");
		fflush(stdout);
		fflush(stdin);

	}
		break;
	case 'f':
		//Exit case
		printf("Goodbye\n");
		fflush(stdout);
		exitCase++;
		break;
	case '\n':
		printf("Not a valid case\n");
		fflush(stdout);
		break;
	default:
		printf("Not a valid case\n");
		fflush(stdout);
		break;
	}
	}
	//Cleaning up pointers
		delete[] buffer;
		delete[] buffer2;
		delete[] fileNameE;
		delete[] fileNameD;
		delete[] fileNameI;
		delete[] fileNameO;
		delete[] key;

  return 0;
}
