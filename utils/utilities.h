// This file contains functions required for proper I/O validation
#include <iostream>
using namespace std;

// Validates char input taken from user
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

// Validate marks
void validateSubjectMarks(short marks[], short index)
{
  while (marks[index] < 0 || marks[index] > 100)
  {
    cout << "Looks like you have entered an invalid response. Please enter marks again (0 - 100): ";
    cin >> marks[index];
  }
}

// Validate number of days
void validateDays(float &days)
{
  while (days > 366 || days < 1)
  {
    cout << "Looks like you have entered an invalid response. Please enter number of days again (1 - 366): ";
    cin >> days;
  }
}
