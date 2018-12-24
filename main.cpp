#include <iostream>          // for basic I/O operations e.g. cin, cout, etc.
#include <fstream>           // for data file handling
#include <string.h>          // for strcmp()
#include <stdio.h>           // for remove() and rename()
#include "utils/utilities.h" // contains utils required for proper I/O

using namespace std; // we don't need to add 'std::' before standard library methods

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
  void generateRollNumber();
  int getRollNumber() { return rollNumber; }
};

/**
 * Generate and return student roll number in format - 12252 which is equivalent to 12th 'B' 52
 * We generate roll number alphabetically by using the first four characters of name.
 */
void Student::generateRollNumber()
{
  Student schoolStudentTemp;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  short flag = 0;

  while (studentFile.read((char *)&schoolStudentTemp, sizeof(schoolStudentTemp)))
  {
    if (studentClass == schoolStudentTemp.studentClass && tolower(studentSection) == tolower(schoolStudentTemp.studentSection))
    {
      flag++;
      for (short i = 0; i < 4; ++i)
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
  generateRollNumber();
  cout << "\nGenerated roll number is " << getRollNumber() << ". Please, note it safely as it'll be asked during data modification.";
}

void removeStudent()
{
  Student studentRead;
  int userRollNumber;
  short flag = 0;
  ifstream fileToRead("data/student.dat", ios::binary);
  ofstream fileToWrite("data/temp_student.dat", ios::binary | ios::app);
  cout << "Enter roll number of student whose data has to be removed: ";
  cin >> userRollNumber;

  while (fileToRead.read((char *)&studentRead, sizeof(studentRead)))
  {
    if (userRollNumber == studentRead.getRollNumber())
    {
      flag++;
      continue;
    }
    else
    {
      fileToWrite.write((char *)&studentRead, sizeof(studentRead));
    }
  }

  if (flag == 0)
    cout << "Sorry, No Match found.";
  else
    cout << "Data of roll number " << userRollNumber << " has been removed from file.";
  fileToRead.close();
  fileToWrite.close();
  remove("data/student.dat");
  rename("data/temp_student.dat", "data/student.dat");
}

void addStudent()
{
  Student schoolStudent;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolStudent.inputStudentDetails();
  studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
  studentFile.close();
}

class Teacher
{
private:
  string teacherName, teacherQualification;
  short teacherExperience, teacherClass;
  char teacherSubject[11], teacherId[5];

public:
  void inputTeacherDetails();
  void generateTeacherId();
  string getTeacherName() { return teacherName; } // vk note: soon to be replaced by teacherId
};

void Teacher::generateTeacherId()
{
  Teacher schoolTeacherRead;
  fstream teacherFile("data/teacher.dat", ios::in | ios::out | ios::app | ios::binary);
  short flag = 0, id = 0;

  while (teacherFile.read((char *)&schoolTeacherRead, sizeof(schoolTeacherRead)))
  {
    flag++;
    if (strcmp(teacherSubject, schoolTeacherRead.teacherSubject) == 0)
    {
      id++;
    }
  }

  if (id == 0 || flag == 0) // flag = 0 indicates empty file and id = 0 indicates no subject match found
  {
    newTeacherId(teacherId, teacherSubject);
  }

  if (id != 0)
  {
    for (int i = 0, j = 48; i < 5; i++) // in ascii chart 48 = '0'
    {
      if (i < 3)
      {
        teacherId[i] = toupper(teacherSubject[i]);
      }
      else
      {
        if (((id % 10) == 9) && i == 3)
        {
          teacherId[i] = j + ((id / 10) + 1);
          i++;
          teacherId[i] = j;
        }
        else if (i == 3)
        {
          teacherId[i] = j + (id / 10);
          i++;
          teacherId[i] = j + ((id % 10) + 1);
        }
      }
    }
  }
}

void Teacher::inputTeacherDetails()
{
  system("cls");
  cout << "\nEnter teacher name: ";
  cin.ignore();
  getline(cin, teacherName);
  cout << "Enter the class to be taught (1 to 12): ";
  cin >> teacherClass;
  cout << "Enter the subject to be taught: ";
  cin.ignore();
  gets(teacherSubject);
  convertCharArrayToLower(teacherSubject, sizeof(teacherSubject));
  cout << "Enter teacher work experience (in years): ";
  cin >> teacherExperience;
  cout << "Enter teacher educational qualification: ";
  cin.ignore();
  getline(cin, teacherQualification);
  cout << "\nGenerated teacher ID is ";
  generateTeacherId();
  displayCharArray(teacherId, sizeof(teacherId));
  cout << ". Please, note it safely as it'll be asked during data modification.";
}

void addTeacher()
{
  Teacher schoolTeacher;
  fstream teacherFile("data/teacher.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolTeacher.inputTeacherDetails();
  teacherFile.write((char *)&schoolTeacher, sizeof(schoolTeacher));
  teacherFile.close();
}

void removeTeacher()
{
  Teacher teacherRead;
  string userTeacherName;
  short flag = 0;
  ifstream fileToRead("data/teacher.dat", ios::binary);
  ofstream fileToWrite("data/temp_teacher.dat", ios::binary | ios::app);
  cout << "Enter name of teacher whose data has to be removed: ";
  cin.ignore();
  getline(cin, userTeacherName);

  while (fileToRead.read((char *)&teacherRead, sizeof(teacherRead))) // vk note: not working
  {
    if (userTeacherName == teacherRead.getTeacherName())
    {
      flag++;
      continue;
    }
    else
    {
      fileToWrite.write((char *)&teacherRead, sizeof(teacherRead));
    }
  }

  if (flag == 0)
    cout << "Sorry, No Match found.";
  else
    cout << "Data of " << userTeacherName << " has been removed from file.";
  fileToRead.close();
  fileToWrite.close();
  remove("data/teacher.dat");
  rename("data/temp_teacher.dat", "data/teacher.dat");
}

void displayRemoveDataScreen()
{
  system("cls");
  int userChoice = 0;
  cout << "1. Remove an existing student";
  cout << "\n2. Remove an existing teacher";
  cout << "\n3. Remove an existing staff";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press '1' to 'Remove an existing student': ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    removeStudent();
    break;
  case 2:
    removeTeacher();
    break;
  case 3:
    // removeStaff();
    break;
  }
}

void displayAddDataScreen()
{
  system("cls");
  int userChoice = 0;
  cout << "1. Add a new student";
  cout << "\n2. Add a new teacher";
  cout << "\n3. Add a new staff";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press '1' to 'Add a new student': ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    addStudent();
    break;
  case 2:
    addTeacher();
    break;
  case 3:
    // addStaff();
    break;
  }
}

/**
 * Displays home screen
*/
void HomeScreen()
{
  system("cls");
  cout << "1. WORK WITH DATA RECORDS\t\t\t\t\t\t2. VIEW DATA RECORDS";
  cout << "\nA. Add a new student, teacher or staff\t\t\t\t\tD. View student data records";
  cout << "\nB. Remove an existing student, teacher or staff \t\t\tE. View teacher data records";
  cout << "\nC. Update data of an existing student, teacher or staff\t\t\tF. View staff data records";
  cout << "\n\n3. ACCOUNTING AND FINANCE\t\t\t\t\t\t4. STUDENT ACADEMICS";
  cout << "\nG. Receive student fee\t\t\t\t\t\t\tJ. Generate student attendance report";
  cout << "\nH. Pay salary to school teacher\t\t\t\t\t\tK. Generate student academic report";
  cout << "\nI. Pay salary to school staff\t\t\t\t\t\t";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press 'A' to 'Add a new student, teacher or staff': ";
  char menuOption;
  cin.get(menuOption);
  switch (tolower(menuOption))
  {
  case 'a':
    displayAddDataScreen();
    break;
  case 'b':
    displayRemoveDataScreen();
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
}
