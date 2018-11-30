//simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>

using namespace std;

int bin_to_dec(string bin);

int main()
{   
    ifstream fin("out.o");                  // the file with binary code (0s and 1s)

    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }

    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    unordered_map<string, int> reg_map;               // a map from strings to keys to rep registers
    reg_map["0000"] = 0;                     //r1                
    reg_map["0001"] = 0;                     //r2
    reg_map["0010"] = 0;                     //r3
    reg_map["0011"] = 0;
    reg_map["0100"] = 0;                     //r4
    reg_map["0101"] = 0;                     //r5
    reg_map["0110"] = 0;                     //r6
    reg_map["0111"] = 0;                       //r7
    reg_map["1000"] = 0;
    reg_map["1001"] = 0;                    //r8
    reg_map["1010"] = 0;                     //r1                
    reg_map["1011"] = 0;                   //r4                    //r5
    reg_map["1100"] = 0;                     //r6
    reg_map["1101"] = 0;                     //r7
    reg_map["1110"] = 0;
    reg_map["1111"] = 0;
    while(!fin.eof())
    { 
        fin >> instruction;                         // read in the entire line of instrcution (13 bits)
        opcode = instruction.substr(0,4);// take the first 4 bits of the instruction
        //int numCode;
        
        //numCode = bin_to_dec(opcode);
        //reg_map[numCode] = numCode;
        if(opcode == "0001") //PUT                 // if the first 4 bits are PUT
        {
            string n = instruction.substr(4,8);     // read the 6 bits related to numberical value
            int val = bin_to_dec(n);                // convert binary to decimal

            string regis = instruction.substr(12,4);    // find the 3 bits related to the register
            reg_map[regis] = val;
            cout << "val " << val << " " << "regis " << regis << endl;
            // use those 3 bits as location to store value
        }
        else if(opcode == "0100") //SUM                 // SUM instruction is followed by three registers
        {   
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register

        }
        else if(opcode == "0010") //OUT                 // print to screen
        {
            string regis = instruction.substr(4,4);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }

        else if(opcode == "0101")//Subtraction
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int sub_result = reg_map[regisA] - reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sub_result;
        }

        else if(opcode == "0110")// Multilplication
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int mul_result = reg_map[regisA] * reg_map[regisB]; // add the first two registers
            reg_map[regisC] = mul_result;
        }

        else if(opcode == "0111") //Division
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int division_result = reg_map[regisA] / reg_map[regisB]; // add the first two registers
            reg_map[regisC] = division_result;
        }

        else if(opcode == "1000") //Modules
        {
            string regisA = instruction.substr(4,4);    // bits 4-6 are the first register
            string regisB = instruction.substr(8,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(12,4);   // bits 10-12 are the last register
            
            int mod_result = reg_map[regisA] % reg_map[regisB]; // add the first two registers
            reg_map[regisC] = mod_result;
        }
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
