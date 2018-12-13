//simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <unordered_map>

using namespace std;

int bin_to_dec(string bin);
void clear(unordered_map<string, int> &reg_map);
string regToBin(string reg);

int main()
{
    ifstream fin("out.o");                  // the file with binary code (0s and 1s)
    int lineNumber = 0;
    unordered_map<string, int> reg_map;
    int arrStart = INT_MAX;
    
    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }
    
    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    
    while(!fin.eof())
    {
        fin >> instruction;                         // read in the entire line of instrcution (13 bits)
        opcode = instruction.substr(0,4);// take the first 4 bits of the instruction
        //int numCode;
        
        //numCode = bin_to_dec(opcode);
        //reg_map[numCode] = numCode;
		if(opcode == "0000"){
			;
		}
        if(opcode == "1001"){
            clear(reg_map);
        }
        else if(opcode == "0001") //PUT                 // if the first 4 bits are PUT
        {
            string n = instruction.substr(4,8);     // read the 6 bits related to numberical value
            int val = bin_to_dec(n);                // convert binary to decimal
            
            string regis = instruction.substr(12,4);    // find the 3 bits related to the register
            reg_map[regis] = val;
            // use those 3 bits as location to store value
        }
        else if(opcode == "0011"){//Halt
            break;
        }
        else if(opcode == "0010") //OUT                 // print to screen
        {
            string regis = instruction.substr(4,4);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "0100") //SUM                 // SUM instruction is followed by three registers
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register
            
        }
        
        
        else if(opcode == "0101")//Subtraction
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int sub_result = reg_map[regisA] - reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sub_result;
        }
        else if(opcode == "0110"){//Jump
            int jump = bin_to_dec(instruction.substr(4,12));

           	int count = 0;
            
            if(jump < lineNumber){
                fin.close();
                fin = ifstream("out.o");                  // the file with binary code (0s and 1s)
                
                
                while(count != jump-1){
                    fin >> instruction;
                    
                    ++count;
                }

				lineNumber = count;
            }
            else{
                while(lineNumber < jump-1){
                    fin >> instruction;
                    lineNumber++;
				}

            }
        }
        else if(opcode == "0111"){//SKIPCOND
            string regisA = instruction.substr(4,4);
            string regisB = instruction.substr(12,4);
            string skipcond = instruction.substr(8,4);
            if(skipcond == "0001"){//Less
                if(!(reg_map[regisA] <= reg_map[regisB])){
                    fin >> instruction;
                }
            }
            else if(skipcond == "0010"){//greater
                if(!(reg_map[regisA] >= reg_map[regisB])){
                    fin >> instruction;
                }
            }
            else{//equal
                if(!(reg_map[regisA] == reg_map[regisB])){
                    fin >> instruction;
                }
            }
        }
        else if(opcode == "1000"){//Array
            if(arrStart == INT_MAX){
                arrStart = bin_to_dec(instruction.substr(12,4));
            }
            else{
                int regisA = reg_map[instruction.substr(4,4)];
                string regisB = instruction.substr(8,4);
                string regisC = instruction.substr(12,4);
                
                if(regisB == "0100"){
                    reg_map[regToBin(to_string(regisA+arrStart))] += reg_map[regisC];
                }
                else if(regisB == "0101"){
                    reg_map[regToBin(to_string(regisA+arrStart))] -= reg_map[regisC];
                }
                else if(regisB == "1011"){
                    reg_map[regToBin(to_string(regisA+arrStart))] = reg_map[regisC];
                }
            }
        }
        else if(opcode == "1010"){//Register
            string regisA = instruction.substr(4,4);
            string regisB = instruction.substr(8,4);
            string regisC = instruction.substr(12,4);
            
            if(regisB == "1011"){
                reg_map[regisA] = reg_map[regisC];
            }
            else if(regisB == "0100"){
                reg_map[regisA] += reg_map[regisC];
            }
            else if(regisB == "0011"){
                reg_map[regisA] -= reg_map[regisC];
            }
        }
        
        ++lineNumber;
    }
    
    fin.close();
    
    return 0;
}

int bin_to_dec(string bin)
{
    int num = 0;
    
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    
    return num;
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

void clear(unordered_map<string, int> &reg_map){
    // a map from strings to keys to rep registers
    reg_map["0000"] = 0;                     //r1
    reg_map["0001"] = 0;                     //r2
    reg_map["0010"] = 0;                     //r3
    reg_map["0011"] = 0;                     //r4
    reg_map["0100"] = 0;                     //r5
    reg_map["0101"] = 0;                     //r6
    reg_map["0110"] = 0;                     //r7
    reg_map["0111"] = 0;                     //r8
    reg_map["1000"] = 0;                     //r9
    reg_map["1001"] = 0;                     //r10
    reg_map["1010"] = 0;                     //r11
    reg_map["1011"] = 0;                     //r12
    reg_map["1100"] = 0;                     //r13
    reg_map["1101"] = 0;                     //r14
    reg_map["1110"] = 0;                     //r15
    reg_map["1111"] = 0;                     //r16
}
