#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
//some of these libraries are legacy and can be removed;


//! NEED TO FIX CHUGGING AND SLOWDOWN ON SOME VARIABLES

using namespace std;

string TrueScrambleCharacterSwap (string Word, int strength, bool OnlyMiddle);
void start(string inputname);
void InputOutput ();
int exit ();

//DEFINE GLOBAL VARIABLES
std::vector <string> Wordlist;//Create a list of words
string filename;

//START THE PROGRAM
int main ()
{
    cout<<"<<<WELCOME>>>"<<endl;
    cout<< "This quiz tests your ability to spot spelling errors and scrambled words. In each round you'll be presented with three choices. Type 1, 2, or 3; you get points for each correct answer;"<<endl;
    cout<< "provide your library for this quiz. Include file extension"<<endl;
    cin>>filename;  //getting the file name

    start (filename);
}


void start(string inputname)
{
    ifstream Input;//declaring the input stream
    Input.open (inputname.c_str()); //iniciating the stream



    if(!Input) //checking for errors
        {
        cout << "No input found" <<endl;
        exit();
        }

    if (Input.is_open()) //filling the lists
    {
        //clears any leftover bits
        Input.clear();
        Input.seekg(0, std::ios::beg);
        Wordlist.clear();

        bool NewWord = false;//bool for splitting into words
        Wordlist.push_back ("");//adding the first variable - more efficient than running an if function;
        char c; //buffer for accessing data from the file

        while (Input.get(c)) //repeated for every character in the file
        {
            if (isalpha(c) == 0)  //if there is a special sign, the next character will be added to a new word
            {
                NewWord = true;;
            }
            else
            {
                if(NewWord == true)
                {
                     Wordlist.push_back ("");
                     Wordlist.back() += c;
                     NewWord = false;
                }
                else
                {
                    Wordlist.back() += c;
                }
            }
        }
        Input.close();
        cout<<"Input loaded"<<endl;
    }
    InputOutput (); //calls the UI function

}

string TrueScrambleCharacterSwap (string Word, int strength, bool OnlyMiddle, int seed)
{

    //Word is an string that is being scrambled
    //strength - the chance to scramble a letter in percentages (1-100)
    //OnlyMiddle - yes - only middle characters are scrabled. No - all characters, including first and last are scrambled

    if(Word.size() < 2)//we don't scramble one character words
    {
        return Word;
    }

    //Swaps around characters in a word
    srand(time(NULL) +  Word.size() - seed);//random number generation, unique for each word
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
        else if (Word.size() == 4 && Word[1] == Word[2])
        {
        return Word;
        }


        //swapping characters around
        for (int n = 1; n < (Word.size() -2); n++)
        {
            if(rand() % 100 < strength){//checking for strenght to determine whether a character gets swapped
            int random = (rand() % ( Word.size() - 2) +1);//generates a random number between 1 (second character) and length - 2 (one before last character)
            int exitAlert = 0;
            while(random == n || Characters[n] == Characters[random]) //makes sure the number doesn't scramble with itself - gives more power to strength
            {
                  random = (rand() % ( Word.size() - 2) +1);
                  exitAlert++;//a simple way to prevent fake strings like tooop, mooot, loook or peeek from crashing the program
                  if (exitAlert > 5)
                  {
                      break;
                  }
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
            int exitAlert = 0;
            while(random == n || Characters[n] == Characters[random]) //makes sure the number doesn't scramble with itself - gives more power to strength
            {
                  random = (rand() % Word.size());
                  exitAlert++;//a simple way to prevent fake strings like ooo, aaa, or bbbb from crashing the program
                  if (exitAlert > 5)
                  {
                      break;
                  }
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

        bool OnlyMiddle;
        cout<< "File loaded"<<endl;
        cout<< "Should first and last characters be left unchanged (0 = no, 1 yes)?"<<endl;
        cin>> OnlyMiddle;
        cout<<"The game starts. You'll be presented with "<<Wordlist.size()<<"words in total. "<<endl<<"For each word, type 1, 2 or 3 to choose the correct spelling"<<endl;
        cout<<"Time matters - the faster you finish, the more bonus points you get! But be warned, while you gain a point for every correct answer, you loose a point for every wrong answer!"<<endl;


        float strenght = 80/Wordlist.size();
        int maxpoints = Wordlist.size();
        int points = 0;
        int timepoints = 0;
        time_t start_time;
        start_time = time(NULL);

        while (Wordlist.size() > 0)
        {
            int UserAnsw;
            srand(time(NULL) - UserAnsw + Wordlist.size());
            int random = (rand() % Wordlist.size());
            int CorAnsw = (rand() % 3);
            string Answ [3];


            //formatting
            int SecondHalf = Wordlist[random].size();
            if(SecondHalf % 2 == 1)
            {
            int FirstHalf = (int)SecondHalf/2;
            SecondHalf = SecondHalf - FirstHalf;
            cout<<' '<<std::setw(FirstHalf)<<"1"<<std::setw(SecondHalf)<<' ';
            cout<<' '<<std::setw(FirstHalf)<<"2"<<std::setw(SecondHalf)<<' ';
            cout<<' '<<std::setw(FirstHalf)<<"3"<<std::setw(SecondHalf)<<' '<<endl;;
            }
            else
            {
            int FirstHalf = (int)SecondHalf/2;
            SecondHalf = SecondHalf - FirstHalf;
            cout<<std::setw(FirstHalf)<<"1"<<std::setw(SecondHalf)<<' ';
            cout<<' '<<std::setw(FirstHalf)<<"2"<<std::setw(SecondHalf)<<' ';
            cout<<' '<<std::setw(FirstHalf)<<"3"<<std::setw(SecondHalf)<<' '<<endl;;
            }

            for (int n = 0; n < 3; n++)
            {

                if(n == CorAnsw)
                {
                    Answ [n] = Wordlist[random];
                    cout<<Answ [n] <<" ";
                }
                else
                {
                    Answ [n] = TrueScrambleCharacterSwap (Wordlist[random], (int)strenght*Wordlist.size(), OnlyMiddle, n);
                    int a = n-1;
                    //making sure all the answers are unique
                    while(a > -1)
                    {
                        if(Answ [n] == Answ [a] || Answ [n] == Wordlist[random])
                        {
                            Answ [n] = TrueScrambleCharacterSwap(Wordlist[random], (int)strenght*Wordlist.size(), OnlyMiddle, rand() + a);
                            a = n-1;
                        }
                        else
                        {
                            a--;
                        }
                    }
                    cout<<Answ [n] <<" ";
                }
            }
            cin>>UserAnsw;
            if (UserAnsw -1 == CorAnsw)
            {
                points ++;
                cout<<"correct, score: "<<points<<endl;
            }
            else
            {
                points --;
                cout<<"incorrect, score: "<<points<<endl;
            }
            cout<<endl;
            Wordlist.erase(Wordlist.begin () + random );
        }
        timepoints =  ((maxpoints*2) - (time(NULL) - start_time)) * 0.25;
        if (timepoints < 0)
        {
            timepoints = 0;
        }
        cout<<"YOU HAVE FINISHED! FINIAL SCORE: "<<points<<" + time bonus("<<timepoints<<") ="<<timepoints + points<< " out of "<<maxpoints<<" questions!"<<endl<<endl<<endl;
        cout<<"if you wish to add your name to the scoreboard, type your name. Otherwise, type any single character and press enter"<<endl;
        string scoreboardname;
        cin>>scoreboardname;
        if(scoreboardname.size() < 2)
        {
             exit();
        }
        else
        {
            //!ADD TO SCOREBOARD
            ofstream Scoreboard ("scoreboard.txt", std::ofstream::out);
            Scoreboard<<scoreboardname;
            Scoreboard<<'/n';
            cout<<"added to scoreboard"<<endl<<endl;

            exit();
        }

}



//exiting the file safely
int exit()
{
      //Continue or exit
      int choice;
      cout<< "0 to exit, 1 to play the same quiz, 2 to play a different quiz"<<endl;
      cin >>choice;
      if(choice == 0)
      {
          return 0;
      }
      else if (choice == 1)
      {
          start(filename);
      }
      else if (choice == 2)
      {
         main();
      }
      else
      {
          cout<< "wrong option, try again"<<endl;
          exit();
      }
}
