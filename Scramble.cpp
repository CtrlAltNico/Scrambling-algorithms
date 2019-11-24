#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//some of these libraries are legacy and can be removed;

using namespace std;

string TrueScrambleCharacterSwap (string Word, int strength, bool OnlyMiddle);
void InputOutput ();
void exit ();

//DEFINE GLOBAL VARIABLES
std::vector <string> Wordlist;//Create a list of words
std::vector <string> Punctuation; //create a list of symbols - multiple symbols will be grouped into strings

//START THE PROGRAM

int main ()
{
   //Inputting the file
    string filename; //declaring the file name
    ifstream Input;//declaring the input stream
    cout<< "Write the file name with extension. Make sure the file is in the same directory as the executable"<<endl;
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

string TrueScrambleCharacterSwap (string Word, int strength, bool OnlyMiddle)
{

    //Word is an string that is being scrambled
    //strength - the chance to scramble a letter in percentages (1-100)
    //OnlyMiddle - yes - only middle characters are scrabled. No - all characters, including first and last are scrambled

    if(Word.size() < 2)//we don't scramble one character words
    {
        return Word;
    }

    //Swaps around characters in a word
    srand(time(NULL) * Word[rand() % Word.size()]);//random number generation, unique for each word
    string ReturnValue;//Scrambled word that will be returned
    vector <char> Characters; //vector for the buffer of characters
    for (int n = 0; n <  Word.size(); n++) //converts the string to a buffer vector
    {
        Characters.push_back(Word[n]);
    }

    if(OnlyMiddle == true)//Determines whether first and last letters get scrambled
    {
        if(Word.size() < 4)//we don't scramble 3 and 2 letter words
        {
        return Word;
        }

        //swapping characters around
        for (int n = 1; n < (Word.size() -2); n++)
        {
            if(rand() % 100 < strength){//checking for strenght to determine whether a character gets swapped
            int random = (rand() % ( Word.size() - 2) +1);//generates a random number between 1 (second character) and length - 2 (one before last character)
            while(random == n) //makes sure the number doesn't scramble with itself - gives more power to strength
            {
                  random = (rand() % ( Word.size() - 2) +1);
            }
            std::swap(Characters[n], Characters[random]);//swaps two values. While it's not a very efficient method, it's convenient and clear to read;
            }
        }
    }
    else //same steps but with the full range
    {
        for (int n = 0; n < Word.size() - 1; n++)
        {
            if(rand() % 100 < strength){
            int random = (rand() % Word.size() );
            while(random == n)
            {
                  random = (rand() % Word.size() );
            }
            std::swap(Characters[n], Characters[random]);
            }
        }
    }

    //Return results
    for (int n = 0; n < Word.size(); n++)
    {
        ReturnValue += Characters[n];
    }
    return ReturnValue;
}

void InputOutput ()
{
        //Settings and output
        string OutputName;
        bool OnlyMiddle;
        int stength;
        cout<< "File loaded"<<endl;
        cout<< "Name the output file for the scrable. Remember to include file extension"<<endl;
        cin >> OutputName;
        ofstream Output (OutputName);
        cout<< "Should first and last characters be left unchanged (0 = no, 1 yes)?"<<endl;
        cin>> OnlyMiddle;
        cout<< "Determine effect strength: 0 - no scramble, 50 - around half of the characters are changed, 100 - all characters are changed"<<endl;
        cin>>stength;


        if(!Output)//checking for errors
        {
            cout<<"failed to create an output file"<<endl;
            exit();
        }
        //generating output
        for(int n = 0; n < Wordlist.size(); n++)
        {
            Output << TrueScrambleCharacterSwap(Wordlist[n], stength, OnlyMiddle);
            Output << Punctuation[n];
        }
        Output.close();
        exit();
}

//exiting the file safely
void exit()
{
      //Continue or exit
      int choice;
      cout<< "0 to exit, 1 to scramble another file, 2 to scramble the same file differently"<<endl;
      cin >>choice;
      if(choice == 0)
      {
          return;
      }
      else if (choice == 1)
      {
          main();
      }
      else if (choice == 2)
      {
         InputOutput();
      }
      else
      {
          cout<< "wrong option, try again"<<endl;
          exit();
      }
}
