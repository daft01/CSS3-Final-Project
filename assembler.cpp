#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(){
    ifstream fin("sum.coria");
    ofstream out("sum.o");
    
    if(fin.fail())
    {
        cout << "File open failed\n";
        exit(0);
    }
    
    string opcode;
    int num;
    string regis;
    
    while(!fin.eof()){
        
        fin >> opcode;
        
        if(opocode == "LOL"){
            out << "0001";
            
            fin >> num;
            out << decToBin(num);
            
            fin >> regins;
            out << regToBin(regis);
            
            out << endl;
        }
        else if(opcode == "JK"){
            out << "0010";
            
            fin >> regis;
            out << regToBin(regis);
            
            out << "000000";
        }
        else if(opcode == )
    }
}
