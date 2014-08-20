#!/usr/bin/python3
import sys 

def rot13(input):
    output=""
    for i in input:
        if i.isalpha():
            if i.islower():
                if (ord(i)+13)%ord('z') < ord('a'):
                    output += chr( ((ord(i)+13)%ord('z'))+ord('a') )
                else:
                    output += chr( (ord(i)+13)%ord('z') )
            else:
                if (ord(i)+13)%ord('Z') < ord('A'):
                    output += chr( ((ord(i)+13)%ord('Z'))+ord('A') )
                else:
                    output += chr( (ord(i)+13)%ord('Z') )
    return output

if len(sys.argv) < 2:
    print("Usage:\t %s \"<input text>\"" % sys.argv[0],  file=sys.stderr) #no can do, amigo
    sys.exit()

print( sys.argv[1], rot13(sys.argv[1]), sep="\n" )
