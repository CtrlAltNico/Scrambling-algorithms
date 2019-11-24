#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//some of these libraries are legacy and can be removed;

using namespace std;

string ScrambleFromATable (string Word, int strength, bool OnlyMiddle);
void InputOutput ();
void exit ();
void ImportScramblingTable (ifstream& Table);

//DEFINE GLOBAL VARIABLES
std::vector <string> Wordlist;//Create a list of words
std::vector <string> Punctuation; //create a list of symbols - multiple symbols will be grouped into strings
std::vector<string> ScramblingTable;//imported table of characters, with their respective replacements

//START THE PROGRAM

int main ()
{
   //Inputting the file
    string filename; //declaring the file name
    ifstream Input;//declaring the input stream
    cout<< "Type the file name with extension. Make sure the file is in the same directory as the executable"<<endl;
    cin>>filename;  //getting the file name
    Input.open (filename.c_str()); //iniciating the stream

    if(!Input) //checking for errors
        {
        cout << "No input found" <<endl;
        exit();
        return 0;
        }

    if (Input.is_open()) //filling the lists
    {
        int n = 0;//number of an item in the vector
        bool NewWord = false;//bool for splitting into words
        Wordlist.push_back ("");//adding the first variable - more efficient than running an if function;
        char c; //buffer for accessing data from the file

        while (Input.get(c)) //repeated for every character in the file
        {
            if (isalpha(c) == 0)  //if there is a special sign, the next character will be added to a new word
            {
                if(NewWord == true)
                {
                Punctuation.back() += c;
                }
                else{
                Punctuation.push_back("");//save the special character for later as a string
                Punctuation.back() += c;
                }
                NewWord = true;
            }
            else
            {
                if(NewWord == true)
                {
                //creating a new word
                     Wordlist.push_back ("");
                     n++;
                     Wordlist[n] += c;
                     NewWord = false;
                }
                else
                {
                    Wordlist[n] += c;
                }
            }
        }
        Input.close();
        cout<<"Input loaded"<<endl;
    }
    InputOutput (); //calls the UI function
}

//This function and using a global 'ScramblingTable' variable prevents multiple imports of the table
void ImportScramblingTable (ifstream& Table)
{
    ScramblingTable.clear();
//load the table from a file
//Uses an 'A' to 'Z' table, only with capital letters
//the table is used for character distribution. Each string is a row, going from A to z; A lies at [0] (-65), a lies at [32] (-71).
    if (Table.is_open()) //filling the list
    {
        string c;
        while(getline(Table, c))
            {
                c.erase(0,2);//first two characters from each row are skipped while importing
                ScramblingTable.push_back(c);

            }
        Table.close();
    }

    //adding lowercase part to the table
    for(int n = 0;  n < 26; n++)
    {
        ScramblingTable.push_back("");
        for (int i = 0; i < ScramblingTable[n].size(); i++){
                ScramblingTable.back() += tolower(ScramblingTable[n][i]);
        }
    }
}


string Decrypt (string Word)
{
    //decrypts scramble from a table if all characters have only one solution, scramble had 100 strength and only middle was equal to 0
    string ReturnValue{""};//value to return from the fuction - scrambled word
        for(int n = 0; n < Word.size(); n++)//for each character
        {
            for (int a =0; a < 52; a++)
            {
                for(int b = 0; b < ScramblingTable [a].size(); b++)
                {
                    if(ScramblingTable[a][b] == Word[n])
                    {
                        int c = a;
                        if (c < 26){
                        c = c + 65;}
                        else{
                        c = c + 71;}
                        ReturnValue = ReturnValue + (char)c;
                        cout<<c<<" is "<<(char)c;
                        goto Next;

                    }
                }

            }
            Next:;
            cout<<ReturnValue<<endl;
        }


    return ReturnValue;//Return scrambled/encoded word
}

void InputOutput ()
{
        string OutputName;
        string InputName;
        cout<< "File loaded"<<endl;
        cout<< "Name the output file for the decryption. Remember to include file extension"<<endl;
        cin >> OutputName;
        ofstream Output (OutputName, std::ofstream::out);
        if(!Output)
        {
            cout<<"failed to create an output file"<<endl;
            exit();
        }

        cout<< "Name the input table you are using. Include file extension"<<endl;
        cin>> InputName;
        ifstream table;
        table.open(InputName.c_str());
        if(!table)
        {
            cout<<"invalid scrambling table"<<endl;
            exit();
        }
        else
        {
            ImportScramblingTable(table);
            cout<<"table imported successfully"<<endl;
        }

        //generates Output: Evoke scramble for each word, add punctuation, save file
        for(int n = 0; n < Wordlist.size(); n++)
        {
            Output << Decrypt(Wordlist[n]);
            Output << Punctuation[n];
        }
        Output.close();
        table.close();
        exit();
}


void exit()
{
      //Continue or exit
      int choice;
      cout<< "0 to exit, 1 to decrypt another file"<<endl;
      cin >>choice;
      if(choice == 0)
      {
          return;
      }
      else if (choice == 1)
      {
          main();
      }
      else
      {
          cout<< "invalid option, try again"<<endl;
          exit();
      }
}
