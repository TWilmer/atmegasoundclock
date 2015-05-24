#include <fstream>
#include <iostream>  
#include <string>
using namespace std; 
int main(int argc, char *argv[]) 
{
    cout<<"wav2c Version 1 by Thorsten Wilmer" << endl;
	if(argc!=2)
	{
	   cout << "Please give a u8 file as argument. Got:" << argc << endl;
	   return -1;
	}
	string filename=argv[1];
	string outputFile=filename;
	outputFile.append(".h");
	string dataName=filename.substr(0,filename.size()-3);
	cout << "Processing "<< filename << endl;
	cout << "Writing "<< outputFile << endl;
    std::ifstream is(filename); 
        std::ofstream os(outputFile); 
        os << "#pragma once" << endl;
        os << "#define __PROG_TYPES_COMPAT__" << endl;
        os << "#include <avr/pgmspace.h>" << endl;
        os << "const unsigned char "<<dataName<<"[] PROGMEM ={" << endl;
         char c;
    int count=0;
    cout.flush();
    while (!is.eof()){
    is.get(c) ;          // loop getting single characters
       os << "   0x"<<std::hex << ((unsigned int) c & 0xFF) << "," << endl;
       count++;
     
       cout.flush();
       } 
       os << "};"<<endl;
       os << "enum { "<<dataName<<"_count=0x"<<count<<"};"<<endl;
	return 0;
}
