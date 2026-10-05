#include <iostream>
#include "task1.h"
#include "task2.h"
using namespace std;

int main()
{
    removeBadWords("input1.txt", "badwords.txt", "output1.txt");
    runTransliterationMenu("input2.txt", "output2.txt");
}