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
            out << "00000000";
            
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
        else if(opcode == "OMG"){
                out << "0101";
                for(int i=0; i<3; i++){
                    fin >> regis;
                    out << regToBin(regis);
                }
                out << endl;
        }
        /*
        else if(opcode == "TMI"){
        }
        else if(opcode == "ILY"){
        }
        else if(opcode == "BRB"){
        }
        else if(opcode == "LOML"){
        }
        else if(opcode == "TY"){
        }
        else{
            cout << "ERROR: INSTRUCTION DOESN'T EXIST\n";
            exit(0);
        }
         */
    }
    
    fin.close();
    out.close();
    
    return 0;
}

string decToBin(int dec)
{
    string bin = "";
    
    if(dec == 0)
        return "00000000";
    
    while(dec / 2 != 0)
    {
        bin = to_string(dec % 2) + bin;
        dec /= 2;
    }
    
    bin = "1" + bin;
    
    while(bin.size() < 8)
        bin = "0" + bin;
    
    return bin;
}

string regToBin(string reg)
{
    int num = 0;
    string bin = "";
    
    for(int i=4; i<reg.size(); i++){
        num *= 10;
        num += reg[i] - '0';
    }
    
    while(num / 2 != 0)
    {
        bin = to_string(num % 2) + bin;
        num /= 2;
    }
    
    bin = "1" + bin;
    
    while(bin.size() < 4)
        bin = "0" + bin;
    
    return bin;
}
