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
	  throw;
	}
	if(	rename(tmpFilename, keysFilename) != 0){
	  throw;
	}
  }
  catch(...){
	cerr<<"File I/O error";
	exit(0);
  }
  return cipher;
}
