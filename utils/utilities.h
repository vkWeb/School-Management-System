// This file contains functions required for proper I/O validation
#include <iostream>
using namespace std;

// Declaring HomeScreen() for use in basicNavigation()
void HomeScreen();

// Sanitize character array input
void sanitizeCharArray(char memberName[], short arraySize)
{
  for (short i = 0; i < arraySize; ++i)
  {
    if (memberName[i] > 64)
      memberName[i] = tolower(memberName[i]);
  }
}

// Displays character array (C-like string) in uppercase
void displayNameInUpper(const char memberName[], short arraySize)
{
  cout << "\nName: ";
  for (short i = 0; i < arraySize; ++i)
    cout << char(toupper(memberName[i]));
}

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

// Basic navigation system
// Press 'H' to go back to home screen or 'Q' to quit
void basicNavigation()
{
  char userChoice;
  cout << "\n\n=> Press 'H' to go back to home screen or 'Q' to quit: ";
  cin >> userChoice;
  while (tolower(userChoice) != 'h' && tolower(userChoice) != 'q')
  {
    cout << "Sorry, we received a wrong input. Please re-enter (H' -> Home Screen or 'Q' -> Quit): ";
    cin >> userChoice;
  }
  switch (tolower(userChoice))
  {
  case 'h':
    HomeScreen();
    break;

  case 'q':
    exit(0);
    break;
  }
}
