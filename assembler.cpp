#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

string decToBin(int dec);
string regToBin(string reg);

int main(){
    ifstream fin("cool.file");
    ofstream out("out.o");
    
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
        
        
        if(opcode == "LOL"){
            out << "0001";
            fin >> num;
            
            out << decToBin(num);
            fin >> regis;
            
            out << regToBin(regis);
            
            out << endl;
        }
        else if(opcode == "JK"){
            out << "0010";
            fin >> regis;
            
            out << regToBin(regis);
            out << "000000";
            
            out << endl;
        }
        else if(opcode == "BFF"){
                break;
        }
        else if(opcode == "LMAO")
        {
                out << "0100";
            
                for(int i=0; i<3; i++){
                    fin >> regis;
                    out << regToBin(regis);
                }
            
                out << endl;
        }
        else if(opcode == "OML"){
                cout << "0101";
                for(int i=0; i<3; i++){
                    fin >> regis;
                    out << regToBin(regis);
                }
                out << endl;
        }
        else{
            cout << "ERROR: INSTRUCTION DOESN'T EXIST\n";
            exit(0);
        }
    }
    
    fin.close();
    out.close();
    
    return 0;
}

string decToBin(int dec)
{
    string bin = "";
    
    if(dec == 0)
        return "0000000";
    
    while(dec / 2 != 0)
    {
        bin = to_string(dec % 2) + bin;
        dec /= 2;
    }
    
    bin = "1" + bin;
    
    while(bin.size() < 6)   // have to make sure that
        bin = "0" + bin;    // each number uses 6 bits
    
    return bin;
}

string regToBin(string reg)
{
    if(reg == "R1")         // basically a simple if.. else
        return "000";       // that will read in a register and
    else if(reg == "R2")    // return the appropriate address.
        return "001";
    else if(reg == "R3")
        return "010";
    else if(reg == "R4")
        return "011";
    else if(reg == "R5")
        return "100";
    else if(reg == "R6")
        return "101";
    else if(reg == "R7")
        return "110";
    else if(reg == "R8")
        return "111";
    else
    {
        cout << "Error\n";
        exit(2);           // kill the program if invalid register
    }                      // is addressed.
}
