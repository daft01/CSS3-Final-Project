#include <iostream>
#include <cctype>
#include <fstream>
#include <cstdlib>
using namespace std;

string decToBin(int dec);
string regToBin(string reg);
string lineToBin(string line);

int main(){
    ifstream fin("cool.file");
    ofstream out("out.o");
    
    if(fin.fail())
    {
        cout << "File open failed\n";
        exit(0);
    }
    
    string opcode;
    int num, count=0;
    string regis;
    
    while(!fin.eof()){
        
        fin >> opcode;

       	count++;
		out << count << " "; 
        if(opcode == "LOL"){ // In
            out << "0001";
            fin >> num;
            
            out << decToBin(num);
            fin >> regis;
            
            out << regToBin(regis);
            
            out << endl;
        }
        else if(opcode == "JK"){ // Out
            out << "0010";
            fin >> regis;
            
            out << regToBin(regis);
            out << "00000000";
            
            out << endl;//only for testing purpose
        }
        else if(opcode == "BFF"){ // Halt
			out << "0011000000000000" << endl;
        }
        else if(opcode == "LMAO") // Sum
        {
			out << "0100";
		
			for(int i=0; i<3; i++){
				fin >> regis;
				out << regToBin(regis);
			}
		
			out << endl;
        }
        else if(opcode == "OMG"){ // Sub
			out << "0101";

			for(int i=0; i<3; i++){
				fin >> regis;
				out << regToBin(regis);
			}

			out << endl;
        }
        else if(opcode == "TMI"){
			out << "0110";
			fin >> regis;
			
			out << lineToBin(regis) << endl;
        }
        else if(opcode == "ILY"){
			out << "0111";

			fin >> regis;
			out << regToBin(regis);

			fin >> regis;
			if(regis == "TFTI")
				out << "0001";
			else if(regis == "ATM")
				out << "0010";
			else if(regis == "MYOB")
				out << "0011";

			fin >> regis;
			out << regToBin(regis) << endl;
        }
        else if(opcode == "BRB"){
			out << "1000";

			fin >> regis;
            
            if(isdigit(regis[0])){
                if(regis.length() == 1)
                    out << decToBin(regis[0] - '0');
                else
                    out << decToBin((regis[0] - '0' * 10) + (regis[1] - '0'));
                
                fin >> regis;
                out << regToBin(regis);
            }else{
                out << regToBin(regis);
                
                fin >> regis;
                
                if(regis == "IDK")
                    cout << "1011";
                else if(regis == "LMAO")
                    cout << "0100";
                else if(regis == "SUB")
                    cout << "0101";
                
                fin >> regis;
                out << regToBin(regis);
            }
            out << endl;
        }
		else if(opcode == "LOML"){
            out << "1001000000000000" << endl;
		}
        else if(opcode[0] == 'T' && opcode[0] == 'Y'){
            out << "1010";
            
            fin >> regis;
            
            fin >> regis;
            out << regToBin(regis);
            
            fin >> regis;
            
            if(regis == "IDK")
                out << "1011";
            else if(regis == "LMAO")
                out << "0100";
            else
                out << "0101";
            
            fin >> regis;
            out << regToBin(regis);
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
    
    for(int i=2; i<reg.size(); i++){
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

string lineToBin(string line){
	int temp = stoi(line);
	string bin = "";

	while(temp){
		bin = to_string(temp%2) + bin;
		temp /= 2;
	}

	while(bin.length() != 12)
		bin = "0" + bin;
		
	return bin;
}

int regToInt(string str){
	int num = 0;
	
	for(int i=0; i < str[i]; i++){
		num *= 10;
		num += str[i] - '0';
	}

	return num;
}
