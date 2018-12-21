#include <iostream>

using namespace std;

void displayCharArray(char myArray[], short arraySize)
{
  for (int i = 0; i < arraySize; i++)
    cout << myArray[i];
}

void convertCharArrayToLower(char myArray[], short arraySize)
{
  for (int i = 0; i < arraySize; i++)
    myArray[i] = tolower(myArray[i]);
}

void newTeacherId(char teacherId[], char teacherSubject[])
{
  for (int i = 0, j = 48; i < 5; i++)
  {
    if (i < 3)
    {
      teacherId[i] = toupper(teacherSubject[i]);
    }
    else
    {
      teacherId[i] = j;
      j++;
    }
  }
}
