// This file contains functions required for proper I/O validation
// and often called functions
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

// Verifies teacher subject code, checks if it is between 1 to 5 or not
void teacherSubjectCodeVerifier(short teacherSubjectCode[], short inputAtIndex)
{
  while (teacherSubjectCode[inputAtIndex] < 1 || teacherSubjectCode[inputAtIndex] > 5)
  {
    cout << "Sorry, we received a wrong subject code. Please enter subject code between 1 to 5: ";
    cin >> teacherSubjectCode[inputAtIndex];
  }
}

// Sets teacher's subject by using subject code; 1. Science 2. Maths 3. English 4. Hindi 5. Social Studies
void setTeacherSubjects(short teacherSubjectCode[], char teacherSubjects[])
{
  for (int i = 0; i < 3; ++i)
  {
    if (teacherSubjectCode[i] == 1)
      strcat(teacherSubjects, "Science ");
    else if (teacherSubjectCode[i] == 2)
      strcat(teacherSubjects, "Maths ");
    else if (teacherSubjectCode[i] == 3)
      strcat(teacherSubjects, "English ");
    else if (teacherSubjectCode[i] == 4)
      strcat(teacherSubjects, "Hindi ");
    else if (teacherSubjectCode[i] == 5)
      strcat(teacherSubjects, "Social Studies ");
  }
}
