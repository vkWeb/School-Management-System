/**
 * Header files 
 */
#include <iostream> //For basic input and output operations e.g. cin, cout, etc.
#include <string>   //For string objects
#include <fstream>  //For data file handling

using namespace std; //Declares std namespace as per latest C++ standard
int generateRollNumber();

/**
 * Student class has all the data members and required functions for students
 */
class Student
{
private:
  int rollNumber = 0, studentGroup = 0; //studentGroup is the class or standard of student (for e.g. class 12th)
  string studentName, motherName, fatherName;
  char studentSection;

public:
  void inputStudentDetails();
  //int generateRollNumber();
};

void Student::inputStudentDetails()
{
  char ch;
  cin.get(ch); //fixes error of skipping input
  cout << "\nEnter student name: ";
  getline(cin, studentName);
  cout << "Enter the class(1 to 12): ";
  cin >> studentGroup;
  cout << "Enter the section('A' to 'D'): ";
  cin.get(ch);
  cin.get(studentSection);
  cout << "Enter student father's name: ";
  cin.get(ch);
  getline(cin, fatherName);
  cout << "Enter student mother's name: ";
  getline(cin, motherName);
  /*
  rollNumber = generateRollNumber();
  cout << "Generated roll number = " << rollNumber;
  */
}

/**
 * Generate and return student roll number in format - 12252 which is equivalent to 12th 'B' 52
 */
/* ROLL NUMBER SYSTEM IS UNDER PROGRESS!
int generateRollNumber()
{
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  studentFile.seekg(0); //places cursor to the beginning of file
  int standard = schoolStudent.studentGroup;
  int section = tolower(schoolStudent.studentSection) - 96;
  int flag = 1;
  long roll = 0;
  while (!studentFile.eof())
  {
    studentFile.read((char *)&schoolStudent, sizeof(schoolStudent));
    if (standard == schoolStudent.studentGroup && section == schoolStudent.studentSection)
      flag++;
    //RESUME HERE! WORK NEEDS TO BE DONE!
  }
  roll = ((standard * 1000) + (section * 100) + flag);
  studentFile.close();
  return roll;
}
*/

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
  cout << "\na. Add or remove student\t\t\t\t\t\t\td. View student database";
  cout << "\nb. Add or remove class\t\t\t\t\t\t\t\te. View staff database";
  cout << "\nc. Add or remove school staff\t\t\t\t\t\t\tf. View class database";
  cout << "\n\n3. ACCOUNTING AND FINANCE\t\t\t\t\t\t\t4. UPDATE OR MODIFY DATA RECORDS";
  cout << "\ng. Receive student fee\t\t\t\t\t\t\t\tj. Update student data";
  cout << "\nh. Pay salaray to school staff\t\t\t\t\t\t\tk. Update class data";
  cout << "\ni. View last five transactions\t\t\t\t\t\t\tl. Update staff data";
  cout << "\n\nEnter appropiate menu option to access that functionality. For e.g. press 'A' to Add or remove a student: ";
  char menuOption;
  cin.get(menuOption);
  switch (menuOption)
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
