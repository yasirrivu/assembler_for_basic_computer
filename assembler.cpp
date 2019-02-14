#include <bits/stdc++.h>

using namespace std;

#define checkBit(n,p) (bool)(n&(1<<p))
#define MOD 4096

string symbolicLine[100];
map<string,int> subrutineAddress;
vector<int> subrutinePos;
set<string> MRI,NONMRI,PSUDO,AST;
map<string,string> machineCode;

string decToBin(int n,int length)
{
    int i;
    string s="";
    for(i=length-1;i>=0;i--)
    {
        if(checkBit(n,i))
        {
            s += "1";
        }
        else
        {
            s += "0";
        }
        if(i==4||i==8||i==12)
        {
            s += " ";
        }
    }
    return s;
}

string hexRepresent(int n,int length)
{
    int i;
    stringstream ss;
    ss << hex << n;
    string s,res="";
    ss >> s;
    while(s.size()<length)
    {
        reverse(s.begin(),s.end());
        s += "0";
        reverse(s.begin(),s.end());
    }
        if(length==3)
    {
        return s;
    }
    for(i=0;i<length;i++)
    {
        res += s[i];
        if(i==1)
        {
            res += " ";
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int i,j,k;
    int lineCounter;
    int initialAdderess;
    int psuValue;
    int origin;
    bool orgFound;
    string psuCode;
    string word;
    string code;
    cout << "#Reading the code from FILE'symbolicAssemblyLanguage.txt'\n"<<endl;
    ifstream symbolicAssemblyLanguage("symbolicAssemblyLanguage.txt");
    if(symbolicAssemblyLanguage.is_open())
    {
        for(lineCounter=0;getline(symbolicAssemblyLanguage,symbolicLine[lineCounter]);lineCounter++,initialAdderess++)
        {
            if(symbolicLine[lineCounter].size()==0)
            {
                lineCounter--;
                initialAdderess--;
                continue;
            }
            stringstream ss;
            ss << symbolicLine[lineCounter];
            ss >> psuCode;

            if(lineCounter==0)
            {
                cout <<"ADDRESS"<< "   " << "SYMBOLIC CODE"<< endl;

                cout <<"======="<< "   " << "============="<< endl;
                if(psuCode.compare("ORG")==0)
                {
                    ss >> hex >> initialAdderess;
                    orgFound=true;
                    origin = initialAdderess;
                    cout <<"          "<< psuCode << " " << hex << hexRepresent(initialAdderess,3) << endl;
                    initialAdderess--;

                }
                else
                {
                    cout << "Error: ORG not found! Assigning ORG to '000'"<<endl;

                    int org=0;
                    ss<<org;
                    ss >> hex>> initialAdderess;
                    orgFound=false;
                    origin=initialAdderess;
                    initialAdderess %= MOD;
                    cout << hexRepresent(initialAdderess,3)  <<"       "<<symbolicLine[lineCounter]<< endl;
                }
            }
            else if(psuCode.compare("END")!=0)
            {
                initialAdderess %= MOD;
                cout << hexRepresent(initialAdderess,3)  <<"       "<< symbolicLine[lineCounter]<< endl;
            }
            else
            {
                cout  <<"          "<<  psuCode << endl;
                cout <<"======="<< "   " << "==============="<< endl;
                break;
            }
            if(psuCode[psuCode.size()-1]==',')
            {
                subrutineAddress[psuCode] = initialAdderess;
                subrutinePos.push_back(lineCounter);
                AST.insert(psuCode);
            }
        }
    }
    else
    {
        cout << "Error: Symbolic Assembly language file not found!" << endl;
        return 0;
    }
    symbolicAssemblyLanguage.close();
    cout << endl << endl;
    ofstream addressSymbleTable1("addressSymbleTable1.txt");
    if(addressSymbleTable1.is_open())
    {
        cout << "Primary Address Symbol Table: " << endl;
        cout << "------------------------------ " << endl;
        for(i=0;i<subrutinePos.size();i++)
        {
            stringstream ss;
            ss << symbolicLine[subrutinePos[i]];
            ss >> psuCode;
            cout << psuCode << " " << hexRepresent(subrutineAddress[psuCode],3) << endl;
            addressSymbleTable1 << psuCode << " " << hex << hexRepresent(subrutineAddress[psuCode],3) << endl;
        }
    }
    addressSymbleTable1.close();
    cout << endl << endl;
    ofstream addressSymbleTable2("addressSymbleTable2.txt");
    if(addressSymbleTable2.is_open())
    {
        vector<int> ASCIIValue;
        cout << "ADDRESS SYMBOL TABLE  " << endl;
        addressSymbleTable2<< "ADDRESS SYMBOL TABLE  " << endl;
        cout << "******************** " << endl;
        addressSymbleTable2<< "******************** " << endl;
        cout << "SYMBOL   HEXADECIMAL CODE      BINARY REPRESENTATION" << endl;
        addressSymbleTable2<< "SYMBOL   HEXADECIMAL CODE      BINARY REPRESENTATION" << endl;
        cout << "======" <<"  " << "=================" <<"      " << "=====================" << endl;
        addressSymbleTable2<< "------   ----------------      ---------------------" << endl;

        for(i=0;i<subrutinePos.size();i++)
        {
            stringstream ss,ssNum;
            ss << symbolicLine[subrutinePos[i]];
            ss >> psuCode;
            for(j=0,k=0;j<psuCode.size();j++,k++)
            {
                cout << psuCode[j] << " ";
                addressSymbleTable2 << psuCode[j] << " ";
                ASCIIValue.push_back(psuCode[j]);
                if(k==1)
                {
                    cout << "      " << ASCIIValue[0] << " " << ASCIIValue[1] << "                 " << decToBin(ASCIIValue[0],8) << " " << decToBin(ASCIIValue[1],8) << endl;
                    addressSymbleTable2 << "      " << hex << ASCIIValue[0] << " " << ASCIIValue[1] << "                 " << decToBin(ASCIIValue[0],8) << " " << decToBin(ASCIIValue[1],8) << endl;
                    ASCIIValue.clear();
                    k = -1;
                }
            }
            if(k==1)
            {
                cout << "        " << ASCIIValue[0] << " 20"<<"                 " << decToBin(ASCIIValue[0],8) << " " << decToBin(32,8) << endl;
                addressSymbleTable2 << "        " << ASCIIValue[0] << " 20"<<"                 "  << decToBin(ASCIIValue[0],8) << " " << decToBin(32,8) << endl;
                ASCIIValue.clear();
            }
            cout << "(LC) "<< "     " << hexRepresent(subrutineAddress[psuCode],4) << "                 " << decToBin(subrutineAddress[psuCode],16) << endl;
            addressSymbleTable2 << "(LC) " << "     "<< hexRepresent(subrutineAddress[psuCode],4) << "                 " << decToBin(subrutineAddress[psuCode],16) << endl;
        }
        cout << "------   ----------------      ---------------------" << endl;
        addressSymbleTable2<< "------   ----------------      ---------------------" << endl;
    }
    addressSymbleTable2.close();
    cout << endl << endl<<endl<<endl;
    //Machine code starts

    bool mriFound,nonmriFound,psudoFound;
    ifstream instractionCode("instractionCode.txt");
    if(instractionCode.is_open())
    {
        while(getline(instractionCode,word))
        {
            if(word.compare("MRI")==0)
            {
                mriFound = true;
                nonmriFound = false;
                psudoFound = false;
            }
            else if(word.compare("NON MRI")==0)
            {
                mriFound = false;
                nonmriFound = true;
                psudoFound = false;
            }
            else if(word.compare("PSEUDO INSTRUCTION")==0)
            {
                mriFound = false;
                nonmriFound = false;
                psudoFound = true;
            }
            else if(mriFound)
            {
                stringstream ss;
                ss << word;
                ss >> word;
                MRI.insert(word);
                getline(ss,code);
                code.erase(code.begin());
                machineCode[word] = code;
            }
            else if(nonmriFound)
            {
                stringstream ss;
                ss << word;
                ss >> word;
                NONMRI.insert(word);
                getline(ss,code);
                code.erase(code.begin());
                machineCode[word] = code;
            }
            else if(psudoFound)
            {
                stringstream ss;
                ss << word;
                ss >> word;
                PSUDO.insert(word);
            }
        }
    }
    else
    {
        cout << "Error: Instruction code file not found!" << endl;
        return 0;
    }
    instractionCode.close();
    ofstream machineCodeFile("machineCode.txt");
    if(machineCodeFile.is_open())
    {
        cout << "MACHINE CODE REPRESENTATION " <<endl;
        machineCodeFile << "MACHINE CODE REPRESENTATION " <<endl;
        cout << "*************************** " <<endl;
        machineCodeFile << "*************************** " <<endl;
        cout <<  "    "<<"MACHINE CODE" <<endl;
        cout <<  "    "<<"------------" <<endl;
        machineCodeFile <<  "    "<<"MACHINE CODE" <<endl;
        machineCodeFile << "    "<<"------------" <<endl;

        for(i=0;i<lineCounter;i++)
        {
            stringstream ss;
            ss << symbolicLine[i];
            ss >> psuCode;
            if(MRI.count(psuCode)!=0)
            {
                if(ss>>code)
                {
                    code += ",";
                    if(AST.count(code)==0)
                    {
                        cout << "Error: Symbolic address doesn't match any lable in Address Symbol Table!!" << endl;
                        machineCodeFile << "Error: Symbolic address doesn't any lable in Address Symbol Table!!" << endl;
                    }
                    else
                    {
                        if(ss>>word&&word.compare("I")!=0)
                        {
                            cout << "Error: Indirect bit!" << endl;
                            machineCodeFile << "Error: Indirect bit!" << endl;
                        }
                        else if(ss>>word)
                        {
                            cout << "Error: Unnecessary symble(MRI)!" << endl;
                            machineCodeFile << "Error: Unnecessary symble(MRI)!" << endl;
                        }
                        else
                        {
                            if(symbolicLine[i][symbolicLine[i].size()-1]=='I'&&symbolicLine[i][symbolicLine[i].size()-2]==' ')
                            {
                                cout << "1";
                                machineCodeFile << "1";
                            }
                            else
                            {
                                cout << "0";
                                machineCodeFile << "0";
                            }
                            cout << machineCode[psuCode] << " " << decToBin(subrutineAddress[code],12) << endl;
                            machineCodeFile << machineCode[psuCode] << " " << decToBin(subrutineAddress[code],12) << endl;
                        }
                    }
                }
                else
                {
                    cout << "Error: Subrutine not found!" << endl;
                    machineCodeFile << "Error: Subrutine not found!" << endl;
                }
            }
            else if(NONMRI.count(psuCode)!=0)
            {
                if(ss>>code)
                {
                    cout << "Error: Unnecessary symble(NONMRI)" << endl;
                    machineCodeFile << "Error: Unnecessary symble(NONMRI)" << endl;
                }
                else
                {
                    cout << machineCode[psuCode] << endl;
                    machineCodeFile << machineCode[psuCode] << endl;
                }
            }
            else if(PSUDO.count(psuCode)!=0)
            {
                if(psuCode.compare("HEX")==0)
                {
                    if(ss>>hex>>psuValue)
                    {
                        cout << decToBin(psuValue,16) << endl;
                        machineCodeFile << decToBin(psuValue,16) << endl;
                    }
                    else
                    {
                        cout << "Error: No value assigned!" << endl;
                        machineCodeFile << "Error: No value assigned!" << endl;
                    }
                }
                else if(psuCode.compare("DEC")==0)
                {
                    if(ss>>dec>>psuValue)
                    {
                        cout << decToBin(psuValue,16) << endl;
                        machineCodeFile << decToBin(psuValue,16) << endl;
                    }
                    else
                    {
                        cout << "Error: No value assigned!" << endl;
                        machineCodeFile << "Error: No value assigned!" << endl;
                    }
                }
            }
            else if(psuCode[psuCode.size()-1]==',')
            {
                if(ss>>psuCode)
                {
                    if(psuCode.compare("HEX")==0)
                    {
                        if(ss>>hex>>psuValue)
                        {
                            cout << decToBin(psuValue,16) << endl;
                            machineCodeFile << decToBin(psuValue,16) << endl;
                        }
                        else
                        {
                            cout << "Error: No value assigned!" << endl;
                            machineCodeFile << "Error: No value assigned!" << endl;
                        }
                    }
                    else if(psuCode.compare("DEC")==0)
                    {
                        if(ss>>dec>>psuValue)
                        {
                            cout << decToBin(psuValue,16) << endl;
                            machineCodeFile << decToBin(psuValue,16) << endl;
                        }
                        else
                        {
                            cout << "Error: No value assigned!" << endl;
                            machineCodeFile << "Error: No value assigned!" << endl;
                        }
                    }
                }
                else
                {
                    cout << "Error: No value for subrutine!" << endl;
                    machineCodeFile << "Error: No value for subrutine!" << endl;
                }
            }
            else
            {
                cout << " Error: Invalid input!" << endl;
                machineCodeFile << " Error: Invalid input!" << endl;
            }
        }
        cout << "--------" << "    "<<"-------------------" <<endl;
    }
    machineCodeFile.close();
}
