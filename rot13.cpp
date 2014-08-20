#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
using namespace std;

string rot13(char *input){
  //using ASCII decimal values
  string output;
  int len = strlen(input);
  for(int i=0; i<len; i++){
	if(isalpha(input[i]) ){
	  if(islower(input[i]) ){
		output += (input[i]+13)%('z'+1) < 'a' ? (input[i]+13)%('z'+1)+'a' : (input[i]+13)%('z'+1) ;
	  }
	  else {
		output += (input[i]+13)%('Z'+1) < 'A' ? (input[i]+13)%('Z'+1)+'A' : (input[i]+13)%('Z'+1);
	  }
	} else{
	  output+=input[i];
	}
  }
  return output;
}

int main(int argc, char** argv){
  if(argc<2){
	cerr<<"Usage:\t"<<argv[0]<<" \"<input text>\"";
	return 1;
  }
  cout<<argv[1]<<"\n"<<rot13(argv[1])<<"\n";
}
