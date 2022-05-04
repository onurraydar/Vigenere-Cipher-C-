/*
 * Cipher.h
 *
 *  Created on: Apr 2, 2020
 *      Author: Raymond McDaniels
 */
#pragma once
class Cipher
{
	private:
		char* textFile; //String with all contents of text document in it
		char* key; // String with key in it
		int count; // int with size text document
		int keySize; // int with size of the key
	public:
		Cipher(); // Normal constructor
		Cipher(char*, char*, int, int); // Constructor with optimal parameters
		void Encrypt(); // Encrypt method
		void Decrypt(); // Decrypt method

};
