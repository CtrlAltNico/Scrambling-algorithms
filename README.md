##Welcome to the mind of me in early 2010's 

These are the first real code snippets I ever worked on outside of Unity3D and automating my school math homework.

This a repository of a few scrambling and character Replacement algorithms in C++ I made when I was a wee 13-14 yo teen. 
Below, are details for each file:

###Scramble.cpp 
a demonstration of a very simple scrambling algorithm.
This algorithm randomly switches order of letters in each word in a textfile. Different setting can be used to ignore first and last letters and choose the intensity of scramble.
Scramble.cpp is intended for help in quizes and learning names/foreign words.
It was originally developed for generation of educational resources.

###DemoSramble.cpp 
is a practical demonstration of the scrambling algorithm.
It's a simple quiz game that shows 3 words, two of which are misspelled.


###Replace.cpp -
a demonstration of a replacement algorithm, using a replacement table.
Replacement table is a list of characters in alphabetical order. Each line is a character, followed by a space and possible character(s) that might replace it. Example:
A ZSWQ
B NHGV
C XDFV
[...]

There are two prepared tables
1.txt - common typing errors based on querty keyboard
2.txt - a table for replacement encryption

###Decrypt.cpp
reverses replacement algorithm using the same table. 
It's an extremely weak encryption, not intended to protect the contents of the file;
However, it can be used for puzzles, exercises and demonstrations. This script was created for a small presentation;

More details can be found in comments for each script. Furthermore, read TABLES.txt for documentation on tables
