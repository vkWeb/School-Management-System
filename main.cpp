#include <iostream>          // for basic I/O operations e.g. cin, cout, etc.
#include <fstream>           // for data file handling
#include <string.h>          // for strcmp()
#include <stdio.h>           // for remove() and rename()
#include "utils/utilities.h" // contains utils required for proper I/O

// we don't need to add 'std::' before standard library methods
using namespace std;

// --Everything for student Starts here--
class Student
{
private:
  int rollNumber, studentClass, studentFee;
  char studentName[29], studentSection;
  string motherName, fatherName;

public:
  Student()
  {
    rollNumber = 1;
  }
  void inputStudentDetails();
  void generateRollNumber();
  void deductFee(int amountPaid) { studentFee = studentFee - amountPaid; }
  int getRollNumber() { return rollNumber; }
  int getStudentFee() { return studentFee; }
};

// Generate and return student roll number in format - 12252 which is equivalent to 12th 'B' 52
// We generate roll number alphabetically by using the first four characters of name.
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

// Inputs student details
void Student::inputStudentDetails()
{
  system("cls");
  // fixes skipping of input; this must be used when `cin` precedes `getline()` or `cin.get()`
  cin.ignore();
  cout << "\nEnter student name(max. 28 characters): ";
  gets(studentName);
  cout << "Enter the class(1 to 12): ";
  cin >> studentClass;
  cout << "Enter the section('A' to 'D'): ";
  cin.ignore();
  cin.get(studentSection);
  cout << "Enter the annual fee student needs to pay(in Rs.): ";
  cin >> studentFee;
  cout << "Enter student father's name: ";
  cin.ignore();
  getline(cin, fatherName);
  cout << "Enter student mother's name: ";
  getline(cin, motherName);
  generateRollNumber();
  cout << "\nGenerated roll number is " << getRollNumber() << ". Please, note it safely as it'll be asked during data modification.";
}

// Asks roll number. If found then student is removed from file
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
      flag++;
    else
      fileToWrite.write((char *)&studentRead, sizeof(studentRead));
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

// Adds student
void addStudent()
{
  Student schoolStudent;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolStudent.inputStudentDetails();
  studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
  studentFile.close();
}

// Receives student fee and deducts from the remaining
void receiveStudentFee()
{
  system("cls");
  Student schoolStudent;
  int inputRollNumber = 0, amountToPay = 0, flag = 0;
  long filePosition = 0;
  char inputChoice;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::binary);
  cout << "Enter the roll number of student whose fees you want to receive(in Rs.): ";
  cin >> inputRollNumber;
  while (!studentFile.eof())
  {
    filePosition = studentFile.tellg();
    studentFile.read((char *)&schoolStudent, sizeof(schoolStudent));
    if (inputRollNumber == schoolStudent.getRollNumber())
    {
      flag++;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, Roll number not found.";
  else
  {
    if (schoolStudent.getStudentFee() != 0)
    {
      do
      {
        if (amountToPay > schoolStudent.getStudentFee())
        {
          cout << "\nIt looks like you have entered more fees than the remaining. Please, enter fee equal to or less than remaining: ";
          cin >> amountToPay;
        }
        else
        {
          cout << "Remaining fee the student(" << schoolStudent.getRollNumber() << ") has to pay: Rs. " << schoolStudent.getStudentFee() << ".\nEnter the amount of fee to receive: ";
          cin >> amountToPay;
        }
      } while (amountToPay > schoolStudent.getStudentFee());
      cout << "Rs." << amountToPay << " will be deducted from remaining fee of Rs. " << schoolStudent.getStudentFee() << ". Press 'Y' to proceed or 'N' to abort the transaction.\n=> ";
      char expectedInput[] = {'y', 'n'};
      cin >> inputChoice;
      validateCharInput(inputChoice, expectedInput, 2);
      switch (inputChoice)
      {
      case 'y':
        schoolStudent.deductFee(amountToPay);
        cout << "Successful! Rs. " << amountToPay << " has been deducted. Now, remaining fees is: " << schoolStudent.getStudentFee();
        studentFile.seekg(filePosition);
        studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
        break;
      case 'n':
        cout << "Transaction aborted!";
        break;
      }
    }
    else
      cout << "Congratulations! All dues are clear for student " << schoolStudent.getRollNumber() << ".";
  }
  studentFile.close();
}
// --Everything for student Ends here--

// --Everything for teacher Starts here--
class Teacher
{
private:
  string teacherName, teacherQualification;
  short teacherExperience, teacherClass, teacherSubjectCode[3];
  int teacherId;

public:
  Teacher()
  {
    teacherSubjectCode[0] = 0;
    teacherSubjectCode[1] = 0;
    teacherSubjectCode[2] = 0;
    teacherId = 0;
  }
  void inputTeacherDetails();
  void generateTeacherId();
  int getTeacherId() { return teacherId; }
};

// Generates teacherId in format: first three digits are subject code of subject the teacher teaches and the last two digits are
// incremented when same subject set of teacher is found. For e.g. 12305 indicates that teacher teach subject codes 1, 2 & 3 and
// is the 5th teacher to teach the same three subjects in school.
void Teacher::generateTeacherId()
{
  Teacher schoolTeacherRead;
  ifstream teacherFile("data/teacher.dat", ios::binary);
  short flag = 0, id = 1, arrayEquality = 0, loopCounter = 0;
  while (teacherFile.read((char *)&schoolTeacherRead, sizeof(schoolTeacherRead)))
  {
    flag++;
    arrayEquality = 0;
    for (loopCounter = 0; loopCounter < 3; ++loopCounter)
    {
      if (teacherSubjectCode[loopCounter] == schoolTeacherRead.teacherSubjectCode[loopCounter])
        ++arrayEquality;
    }
    if (arrayEquality == loopCounter)
      id++;
  }
  teacherId = (teacherSubjectCode[0] * 10000) + (teacherSubjectCode[1] * 1000) + (teacherSubjectCode[2] * 100) + id;
}

// Take all teacher inputs
void Teacher::inputTeacherDetails()
{
  system("cls");
  short flag = 0;
  char userChoice, keepRunning;
  cout << "\nEnter teacher name: ";
  cin.ignore();
  getline(cin, teacherName);
  cout << "Enter the class to be taught (1 to 12): ";
  cin >> teacherClass;
  cout << "\nSubject Code\tSubject\n     1\t\tScience\n     2\t\tMaths\n     3\t\tEnglish\n     4\t\tHindi\n     5\t\tSocial Studies";
  cout << "\nEnter the subject code(s) from the above list to choose subject(s) the teacher will teach, for e.g. Press '1' to choose 'Science': ";
  cin >> teacherSubjectCode[flag];
  teacherSubjectCodeVerifier(teacherSubjectCode, flag);
  ++flag;
  do
  {
    if (flag == 3)
    {
      cout << "Maximum limit of subject per teacher has reached. No more subject can be assigned.\n";
      break;
    }
    else
    {
      cout << "Do you want to assign more subjects? Enter 'Y' for yes or 'N' for no: ";
      cin >> userChoice;
      if (userChoice == 'y')
      {
        cout << "Please enter a subject code: ";
        cin >> teacherSubjectCode[flag];
        teacherSubjectCodeVerifier(teacherSubjectCode, flag);
        do
        {
          keepRunning = 'n';
          for (short i = 0; i < flag; ++i)
          {
            if (teacherSubjectCode[flag] == teacherSubjectCode[i])
            {
              cout << "You have already assigned this subject. Please enter another subject code: ";
              cin >> teacherSubjectCode[flag];
              teacherSubjectCodeVerifier(teacherSubjectCode, flag);
              keepRunning = 'y';
              break;
            }
          }
        } while (keepRunning == 'y');
        ++flag;
      }
    }
  } while (userChoice == 'y' && flag < 4);
  cout << "\nEnter teacher work experience (in years): ";
  cin >> teacherExperience;
  cout << "Enter teacher educational qualification: ";
  cin.ignore();
  getline(cin, teacherQualification);
  generateTeacherId();
  cout << "\nGenerated teacher ID is " << getTeacherId() << " Please, note it safely as it'll be asked during data modification.";
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
  int inputTeacherId;
  short flag = 0;
  ifstream fileToRead("data/teacher.dat", ios::binary);
  ofstream fileToWrite("data/temp_teacher.dat", ios::binary | ios::app);
  cout << "Enter ID of teacher whose data has to be removed: ";
  cin >> inputTeacherId;
  while (fileToRead.read((char *)&teacherRead, sizeof(teacherRead))) // vk note: not working
  {
    if (inputTeacherId == teacherRead.getTeacherId())
      flag++;
    else
      fileToWrite.write((char *)&teacherRead, sizeof(teacherRead));
  }
  if (flag == 0)
    cout << "Sorry, No Match found.";
  else
    cout << "Data of teacher " << inputTeacherId << " has been removed from file.";
  fileToRead.close();
  fileToWrite.close();
  remove("data/teacher.dat");
  rename("data/temp_teacher.dat", "data/teacher.dat");
}
// -- Everything for teacher Ends here --

// Displays screen for removal of existing student, teacher ot staff
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

// Displays screen for addition of new student, teacher or staff
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

// Displays home screen
void HomeScreen()
{
  system("cls");
  char menuOption;
  Student schoolStudent;
  cout << "1. WORK WITH DATA RECORDS\t\t\t\t\t\t2. VIEW DATA RECORDS";
  cout << "\nA. Add a new student, teacher or staff\t\t\t\t\tD. View student data records";
  cout << "\nB. Remove an existing student, teacher or staff \t\t\tE. View teacher data records";
  cout << "\nC. Update data of an existing student, teacher or staff\t\t\tF. View staff data records";
  cout << "\n\n3. ACCOUNTING AND FINANCE\t\t\t\t\t\t4. STUDENT ACADEMICS";
  cout << "\nG. Receive student fee\t\t\t\t\t\t\tJ. Generate student attendance report";
  cout << "\nH. Pay salary to school teacher\t\t\t\t\t\tK. Generate student academic report";
  cout << "\nI. Pay salary to school staff\t\t\t\t\t\t";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press 'A' to 'Add a new student, teacher or staff': ";
  char expectedInput[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  cin >> menuOption;
  validateCharInput(menuOption, expectedInput, 11);
  switch (menuOption)
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
    receiveStudentFee();
    break;
  case 'h':
    cout << "\nWork under progress...";
    break;
  case 'i':
    cout << "\nWork under progress...";
    break;
  // Default case will never get executed ;)
  default:
    cout << "\nWrong Input Received.";
  }
}

int main(void)
{
  HomeScreen();
}
