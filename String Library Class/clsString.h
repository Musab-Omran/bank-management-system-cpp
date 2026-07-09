#pragma once

#include <iostream>
#include "GlobalVariables.h"

using namespace std;

class clsString
{


public:

    static int GetSizeOfString(string S1, string Delim) {

        short pos = 0;
        string sWord; // define a string variable  

        int size = 0;

        // this is to get the number of values
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                size++;
            }

            S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        return size + 1;
    }

    static string* Split(string S1, string Delim, int& size)
    {

        short pos = 0;
        string sWord; // define a string variable  

        size = GetSizeOfString(S1, Delim);
        string* vString = new string[size];

        int i = 0;

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(Delim)) != std::string::npos && i < size)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                vString[i] = sWord;
                i++;
            }

            S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        if (S1 != "" && i < size)
        {
            vString[i] = (S1); // it adds last word of the string.
        }

        return vString;

    }

    static string  UpperAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }
};

