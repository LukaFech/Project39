#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void removeBadWords(const char* inputFile, const char* badWordsFile, const char* outputFile)
{
    ifstream badIn(badWordsFile);
    if (!badIn.is_open())
    {
        cout << "Error opening bad words file!\n";
        return;
    }

    int badWordCount = 0;
    char tempBad[256];
    while (badIn >> tempBad)
    {
        badWordCount++;
    }

    if (badWordCount == 0)
    {
        badIn.close();
        return;
    }

    badIn.clear();
    badIn.seekg(0, ios::beg);

    char** badWords = new char* [badWordCount];
    for (int i = 0; i < badWordCount; ++i)
    {
        badIn >> tempBad;
        badWords[i] = new char[strlen(tempBad) + 1];
        strcpy(badWords[i], tempBad);
    }
    badIn.close();

    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in.is_open() || !out.is_open())
    {
        cout << "Error opening input or output file!\n";
        for (int i = 0; i < badWordCount; ++i)
        {
            delete[] badWords[i];
        }
        delete[] badWords;
        return;
    }

    char word[256];
    bool isFirst = true;

    while (in >> word)
    {
        bool isBad = false;
        for (int i = 0; i < badWordCount; ++i)
        {
            if (strcmp(word, badWords[i]) == 0)
            {
                isBad = true;
                break;
            }
        }

        if (!isBad)
        {
            if (!isFirst)
            {
                out << " ";
            }
            out << word;
            isFirst = false;
        }
    }

    in.close();
    out.close();

    for (int i = 0; i < badWordCount; ++i)
    {
        delete[] badWords[i];
    }
    delete[] badWords;

    cout << "Task 1 completed successfully!\n";
}