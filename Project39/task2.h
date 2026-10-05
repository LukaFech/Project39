#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct TranslitPair
{
    char ukr[10];
    char eng[10];
};

const TranslitPair translitTable[] =
{
    { "А", "A" },{ "а", "a" },{ "Б", "B" },{ "б", "b" },{ "В", "V" },{ "в", "v" },
    { "Г", "H" },{ "г", "h" },{ "Ґ", "G" },{ "ґ", "g" },{ "Д", "D" },{ "д", "d" },
    { "Е", "E" },{ "е", "e" },{ "Є", "Ye" },{ "є", "ye" },{ "Ж", "Zh" },{ "ж", "zh" },
    { "З", "Z" },{ "з", "z" },{ "И", "Y" },{ "и", "y" },{ "І", "I" },{ "і", "i" },
    { "Ї", "Yi" },{ "ї", "yi" },{ "Й", "Y" },{ "й", "y" },{ "К", "K" },{ "к", "k" },
    { "Л", "L" },{ "л", "l" },{ "М", "M" },{ "м", "m" },{ "Н", "N" },{ "н", "n" },
    { "О", "O" },{ "о", "o" },{ "П", "P" },{ "п", "p" },{ "Р", "R" },{ "р", "r" },
    { "С", "S" },{ "с", "s" },{ "Т", "T" },{ "т", "t" },{ "У", "U" },{ "у", "u" },
    { "Ф", "F" },{ "ф", "f" },{ "Х", "Kh" },{ "х", "kh" },{ "Ц", "Ts" },{ "ц", "ts" },
    { "Ч", "Ch" },{ "ч", "ch" },{ "Ш", "Sh" },{ "ш", "sh" },{ "Щ", "Shch" },{ "щ", "shch" },
    { "Ю", "Yu" },{ "ю", "yu" },{ "Я", "Ya" },{ "я", "ya" },{ "Ь", "" },{ "ь", "" },
    { "'", "" }
};

const int tableSize = sizeof(translitTable) / sizeof(TranslitPair);

void transliterateUkrToEng(const char* inputFile, const char* outputFile)
{
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in.is_open() || !out.is_open())
    {
        cout << "Error opening files!\n";
        return;
    }

    char ch;
    char buffer[10] = { 0 };

    while (in.get(ch))
    {
        buffer[strlen(buffer)] = ch;
        buffer[strlen(buffer) + 1] = '\0';

        bool matched = false;
        for (int i = 0; i < tableSize; ++i)
        {
            if (strcmp(buffer, translitTable[i].ukr) == 0)
            {
                out << translitTable[i].eng;
                buffer[0] = '\0';
                matched = true;
                break;
            }
        }

        if (!matched && strlen(buffer) >= 4)
        {
            out << buffer[0];
            memmove(buffer, buffer + 1, strlen(buffer));
        }
    }

    if (strlen(buffer) > 0)
    {
        out << buffer;
    }

    in.close();
    out.close();
    cout << "Transliteration Ukrainian -> English completed!\n";
}

void transliterateEngToUkr(const char* inputFile, const char* outputFile)
{
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in.is_open() || !out.is_open())
    {
        cout << "Error opening files!\n";
        return;
    }

    char ch;
    char buffer[10] = { 0 };

    while (in.get(ch))
    {
        buffer[strlen(buffer)] = ch;
        buffer[strlen(buffer) + 1] = '\0';

        int bestIndex = -1;
        int bestLen = 0;

        for (int i = 0; i < tableSize; ++i)
        {
            int len = strlen(translitTable[i].eng);
            if (len > 0 && strncmp(buffer, translitTable[i].eng, len) == 0)
            {
                if (len > bestLen)
                {
                    bestLen = len;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex != -1 && strlen(buffer) == (size_t)bestLen)
        {
            out << translitTable[bestIndex].ukr;
            buffer[0] = '\0';
        }
        else if (strlen(buffer) >= 4 || (bestIndex == -1 && strlen(buffer) > 0))
        {
            out << buffer[0];
            memmove(buffer, buffer + 1, strlen(buffer));
        }
    }

    if (strlen(buffer) > 0)
    {
        out << buffer;
    }

    in.close();
    out.close();
    cout << "Transliteration English -> Ukrainian completed!\n";
}

void runTransliterationMenu(const char* inputFile, const char* outputFile)
{
    int choice = 0;
    cout << "\n=== Transliteration Menu ===\n";
    cout << "1. Ukrainian -> English\n";
    cout << "2. English -> Ukrainian\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    if (choice == 1)
    {
        transliterateUkrToEng(inputFile, outputFile);
    }
    else if (choice == 2)
    {
        transliterateEngToUkr(inputFile, outputFile);
    }
    else
    {
        cout << "Invalid choice!\n";
    }
}