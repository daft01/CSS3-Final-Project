#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

string dec_to_binary(int dec);
string reg_to_bin(string reg);

int main()
{   
    ifstream fin("sum.coria");      // the file the assembler will interpret
    ofstream out("sum.o");          // the file generated with 0s and 1s

    if(fin.fail())                  // always make sure the file was opened properly
    {
        cout << "File open failed\n";
        exit(0);
    }

    string opcode;                  // store the instruction in opcode
    int num;                        // if i need to store a number from the instruction
    string regis;                   // if i am reading a register. Note I have 8 registered
                                    // which i call: R1, R2, R3, R4, R5, R6, R7, and R8.

    while(!fin.eof())                   // while not reached end of file
    { 
        fin >> opcode;                  // the first line of every instruction is instruction

        if(opcode == "PUT")             // process the PUT instruction
        {
            out << "0011";              // PUT is 0011 as described in my ISA
            fin >> num;                 // read in the decimal number
            out << dec_to_binary(num);  // convert decimal to binary and place in file
            fin >> regis;               // read in the register (i.e. R1, R2, R3, etc)
            out << reg_to_bin(regis);   // this function will convert to appropriate address
            out << endl;                // line break
        }
        else if(opcode == "SUM")        // process the SUM instruction
        {
            out << "0101";              // SUM is 0101 as described in my ISA
            for(int i = 0; i < 3; i++)  // for loop that loops 3 times
            {   
                fin >> regis;           // read in the register
                out << reg_to_bin(regis); // this function will conver to appropriate address
            }
            out << endl;                // line break
        }
        else if(opcode == "OUT")        // process the OUT instruction
        {
            out << "1111";              // OUT is 111 as described in my ISA
            fin >> regis;               // read in the register
            out << reg_to_bin(regis);   // this function will conver to appropriate address
            out << "000000";            // this is padding, since instruction have to be fixed
        }                               // and use up 13 bits, per my ISA.
        else                            // this catches invalid instructions and kills program
        {
            cout << "ERROR: INSTRUCTION DOESN'T EXIST\n";
            exit(0);
        }
    }

    fin.close();
    out.close();

    return 0;
}

string dec_to_binary(int dec)
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

string reg_to_bin(string reg)
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
