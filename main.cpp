/**
 * Header files 
 */
#include <iostream>  // for basic input and output operations e.g. cin, cout, etc.
#include <fstream>   // for data file handling
using namespace std; // declares std namespace. so, we don't need to add 'std::' before cout, cin and other standard library methods

/**
 * Student class has all the data members and required member functions for students
 */
class Student
{
private:
  int rollNumber, studentClass;
  char studentName[29], studentSection;
  string motherName, fatherName;

public:
  Student() // constructor
  {
    rollNumber = 1;
  }
  void inputStudentDetails();
  int generateRollNumber();
};

/**
 * Generate and return student roll number in format - 12252 which is equivalent to 12th 'B' 52
 * We generate roll number alphabetically by using the first three characters of name.
 */
int Student::generateRollNumber()
{
  Student schoolStudentTemp;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  short flag = 0;

  while (studentFile.read((char *)&schoolStudentTemp, sizeof(schoolStudentTemp)))
  {
    if (studentClass == schoolStudentTemp.studentClass && tolower(studentSection) == tolower(schoolStudentTemp.studentSection))
    {
      flag++;
      for (short i = 0; i < 3; ++i)
      {
        if (tolower(schoolStudentTemp.studentName[i]) > tolower(studentName[i]))
        {
          schoolStudentTemp.rollNumber++;
          rollNumber = schoolStudentTemp.rollNumber - 1;
          break;
        }
        else if (tolower(schoolStudentTemp.studentName[i]) < tolower(studentName[i]))
        {
          rollNumber = schoolStudentTemp.rollNumber + 1;
          break;
        }
        else
        {
          continue;
        }
      }
    }
  }
  if (flag == 0)
  {
    rollNumber = (studentClass * 1000) + (tolower(studentSection) - 96) * 100 + rollNumber;
  }
  return rollNumber;
}

void Student::inputStudentDetails()
{
  system("cls");
  cin.ignore(); // fixes skipping of input; this will be used throughout the code
  cout << "\nEnter student name(max. 28 characters): ";
  gets(studentName);
  cout << "Enter the class(1 to 12): ";
  cin >> studentClass;
  cout << "Enter the section('A' to 'D'): ";
  cin.ignore();
  cin.get(studentSection);
  cout << "Enter student father's name: ";
  cin.ignore();
  getline(cin, fatherName);
  cout << "Enter student mother's name: ";
  getline(cin, motherName);
  cout << "\nGenerated roll number is " << generateRollNumber() << ". Please note it in a safe place for future reference.";
}

void addStudent()
{
  Student schoolStudent;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolStudent.inputStudentDetails();
  studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
  studentFile.close();
}

/**
 * Displays home screen only if the administrator has entered the correct credentials
 * Note: Administrator is anyone using our school management system app
*/
void HomeScreen()
{
  system("cls");
  cout << "1. ADD OR REMOVE DATA RECORDS\t\t\t\t\t\t\t2. VIEW DATA RECORDS";
  cout << "\nA. Add or remove a student\t\t\t\t\t\t\tD. View student database";
  cout << "\nB. Add or remove a teacher\t\t\t\t\t\t\tE. View teacher database";
  cout << "\nC. Add or remove a school staff\t\t\t\t\t\t\tF. View staff database";
  cout << "\n\n3. ACCOUNTING AND FINANCE\t\t\t\t\t\t\t4. UPDATE OR MODIFY DATA RECORDS";
  cout << "\nG. Receive student fee\t\t\t\t\t\t\t\tJ. Update student data";
  cout << "\nH. Pay salaray to school staff or teacher\t\t\t\t\tK. Update class data";
  cout << "\nI. View last five transactions and account balance\t\t\t\tL. Update staff data";
  cout << "\n\n=> Enter the displayed menu option of your choice to proceed. For e.g. Press 'A' to 'Add or remove a student': ";
  char menuOption;
  cin.get(menuOption);
  switch (tolower(menuOption))
  {
  case 'a':
    addStudent();
    break;
  case 'b':
    cout << "\nWork under progress...";
    break;
  case 'c':
    cout << "\nWork under progress...";
    break;
  case 'd':
    cout << "\nWork under progress...";
    break;
  case 'e':
    cout << "\nWork under progress...";
    break;
  case 'f':
    cout << "\nWork under progress...";
    break;
  case 'g':
    cout << "\nWork under progress...";
    break;
  case 'h':
    cout << "\nWork under progress...";
    break;
  case 'i':
    cout << "\nWork under progress...";
    break;
  default:
    cout << "\nWrong Input Received.";
  }
}

/**
 * main() starts here
*/
int main()
{
  HomeScreen();
  return 0;
}
