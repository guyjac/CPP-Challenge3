/**
 * ReadWords Interface for Assignment 1
 */

#ifndef READWORDS_H
#define READWORDS_H
/**
 * ReadWords class. Provides mechanisms to read a text file
 */
using namespace std;

#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <iostream>

 class ReadWords
 {
   public:

     ReadWords(string fname);

     void close();

     string getNextWord();

     bool isNextWord();

   private:
     string word;
     ifstream wordfile;
     string nextword;
     bool eoffound;
 };

 #endif

