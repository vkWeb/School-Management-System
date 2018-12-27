// This file contains functions required for proper I/O validation
// and often called functions
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

void convertCharArrayToUpper(char myArray[], short arraySize)
{
  for (int i = 0; i < arraySize; i++)
    myArray[i] = toupper(myArray[i]);
}

void validateCharInput(char &userInput, char expectedInput[], short expectedInputSize)
{
  short flag;
  userInput = tolower(userInput);
  do
  {
    flag = 0;
    for (short i = 0; i < expectedInputSize; i++)
    {
      if (userInput == expectedInput[i])
      {
        flag++;
        break;
      }
    }
    if (flag == 0)
    {
      cout << "\nSorry, We received a wrong input. Please enter a valid choice: \n=> ";
      cin >> userInput;
    }
  } while (flag == 0);
}

void teacherSubjectCodeVerifier(short teacherSubjectCode[], short inputAtIndex)
{
  while (teacherSubjectCode[inputAtIndex] < 1 || teacherSubjectCode[inputAtIndex] > 5)
  {
    cout << "Sorry, we received a wrong subject code. Please enter subject code between 1 to 5: ";
    cin >> teacherSubjectCode[inputAtIndex];
  }
}
