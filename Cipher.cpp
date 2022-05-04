/*
 * Cipher.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Raymond McDaniels
 */

#include "Cipher.h"
#define PI 3.141592653

//Constructor making private variables equal to parameters
Cipher::Cipher(char* text, char* keyI, int countI, int keyS) {
	this->textFile = text;
	this->key = keyI;
	this->count = countI;
	this->keySize = keyS;
}
//Default constructor setting private variables to placeholders
Cipher::Cipher(){
	this->textFile = "";
	this->key = "";
	this->count = 0;
	this->keySize = 0;
}

/*
 * Encrypt method which used algorithm difference = (Index mod keySize) + (TextIndex) to encrypt. If difference >=127 then difference - 95
 */
void Cipher::Encrypt() {
	int j = 0;
	int keyIndex;
	int textIndex;
	int difference = 0;
	for(int i = 0; i < count; i++){
		j = j % keySize;
		keyIndex = (int) key[j];
		textIndex = (int) textFile[i];
		difference = keyIndex + textIndex;
		//This is here so the encryption doesn't touch enter keys
		if(textIndex == 10){
			difference = 10;
		}
		//This is here because our set is size 95 since its from 32-127
		if(difference >= 127) {
			difference = difference - 95;
		}
		//Setting textFile[index] = encrypted char
		textFile[i] = (char) difference;
		j++;
	}
}
/*
 *
 * Decrypt method which used algorithm difference = (TextIndex) - (Index mod keySize) to Decrypt. If difference <32 then difference + 95
 */
void Cipher::Decrypt() {
	int j = 0;
		int keyIndex;
		int textIndex;
		int difference = 0;
		for(int i = 0; i < count; i++){
			j = j % keySize;
			keyIndex = (int) key[j];
			textIndex = (int) textFile[i];
			difference = textIndex - keyIndex;
			//If decryption algorithm goes negative (32 is our 0 index here) then it adds our total set size which is 95 or 32-127.
			if(difference < 32) {
				difference = difference + 95;
			}
			//This is here so decryption doesn't mess with enter keys because the encryption didn't touch them either.
			if(textIndex == 10){
				difference = 10;
			}


			textFile[i] = (char) difference;
			j++;
		}
	}


