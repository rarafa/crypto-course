#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <stdio.h> //rename(), remove() files
using namespace std;

int generateFiles(int padLen, int keys, const char* filename1,  const char* filename2){
  int i,j, val;
  fstream file1, file2;
  try{
	file1.open(filename1, ios::out);
	file2.open(filename2, ios::out);
	srand(time(NULL));
	for(i=0; i<keys; i++){
	  for(j=0; j<padLen; j++){
		/*ASCII printable characters for keys (range 32-126), it
		  actually doesn't matter, but it helps for visualizing the key files*/
		val = rand()%95; 
		val+=32;
		file1<<(char)val;
		file2<<(char)val; 
	  }
	  file1<<"\n";
	  file2<<"\n";
	}
	file1.close();
	file2.close();
  }
  catch(...){
	cerr<<"File I/O error";
	return -1;
  }
}


string oneTimePad(string input, const char* keysFilename){
  //return input string ciphered with first key in keysFilename
  string key, cipher, tmpString;
  fstream keys, tmpFile;
  int inputLen, keyLen;
  const char * tmpFilename = "temporaryFile.key";
  try{
	keys.open(keysFilename, ios::in);
    keys>>key;
	keyLen = key.length();
	inputLen = input.length();
	//xor
	for(int i=0; i<inputLen; i++){
	  cipher += input[i] ^ key[i%keyLen];
	}
	//destroy used key from file:
	tmpFile.open(tmpFilename, ios::out);
	while(getline(keys, tmpString)){
	  tmpFile << tmpString<<"\n";
	}
	tmpFile.close();
	keys.close();
	if( remove(keysFilename) != 0){
	  throw "File I/O error";
	}
	if(	rename(tmpFilename, keysFilename) != 0){
	  throw "File I/O error";
	}
  }
  catch(const char* e){
	cerr<<e;
	exit(0);
  }
  return cipher;
}

int session(int padLen, int keys, const char* filename1, const char* filename2){
  //simulates two users' interaction
  string  plainT, cipherT, decipherT;
  int plainTLen;
  while( (keys--) > 0){
	cout<<"Message for Alice:\t";
	getline(cin, plainT);
	plainTLen = plainT.length();
	for(int i=0; i<plainTLen; i++){
	  if(!isprint(plainT[i])){ 
		cerr<<"Please enter only ASCII printable characters";
		return -1;
	  }
	}
	cipherT = oneTimePad(plainT, filename1);
	cout<<"Alice receives:\t\t"<<cipherT<<"\n";
	decipherT = oneTimePad(cipherT, filename2);
	cout<<"Alice deciphers:\t"<<decipherT<<"\n\n";
  }
  return 0;
}

int main(int argc, char **argv){
  int padLen=0, keys=0;
  istringstream tmp;
  const char* filename1="alice.key";
  const char*  filename2="bob.key";

  if(argc<3){
	cerr<<"Usage:\t"<<argv[0]<<" <number of keys> <length of keys>";
	return -1;
  }
  try{
	tmp.str(argv[1]);
	if( !(tmp>>keys) ) throw "Specify number of keys";
	tmp.clear();
	tmp.str(argv[2]);
	if( !(tmp>>padLen) ) throw "Specify pad length";
	if (keys < 1 || padLen < 1) throw "Specify positive values";
  }
  catch(const char* e){
	cerr<<e<<"\n";
	cerr<<"Usage:\t"<<argv[0]<<" <number of keys> <length of keys>";
	return -1;
  }
  if( !(generateFiles(padLen, keys, filename1, filename2))){
	return -1;
  }
  if( !(session(padLen, keys, filename1, filename2))){
	return -1;
  }
  return 0;
}
