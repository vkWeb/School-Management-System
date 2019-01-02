#include <iostream>          // For basic I/O operations e.g. cin, cout, etc.
#include <fstream>           // For data file handling
#include <string.h>          // For strcmp()
#include <stdio.h>           // For remove() and rename()
#include "utils/utilities.h" // Contain utils required for proper I/O

// We don't need to add 'std::' before standard library methods
using namespace std;

// Everything which a member of school have in common is declared here
class SchoolMember
{
protected:
  char name[29];
  int id;

public:
  SchoolMember()
  {
    id = 0;
  }
};

// --Everything for student Starts here--
class Student : public SchoolMember
{
private:
  int studentClass, studentFee;
  char motherName[29], fatherName[29], studentSection;

public:
  Student()
  {
    id = 1;
  }
  void inputStudentDetails();
  void generateRollNumber();
  void displayStudentData() const
  {
    cout << "\nName: " << name << "\nRoll Number: " << id << "\nClass: " << studentClass << " '" << char(toupper(studentSection)) << "' "
         << "\nMother's name: " << motherName << "\nFather's name: " << fatherName << "\nRemaining fee: Rs." << studentFee;
  }
  void deductFee(int amountPaid) { studentFee = studentFee - amountPaid; }
  int getRollNumber() const { return id; }
  int getStudentFee() const { return studentFee; }
};

// Generate roll number by using class, section and first four characters of name.
// Student roll number format is explained below:
// First two digits is class, third digit is section and last two are alphabetical position of student in his/her class.
// For e.g. 12252 is equivalent to class = 12th, section = 'B', alphabetical position = 52
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
        if (tolower(schoolStudentTemp.name[i]) > tolower(name[i]))
        {
          schoolStudentTemp.id++;
          id = schoolStudentTemp.id - 1;
          break;
        }
        else if (tolower(schoolStudentTemp.name[i]) < tolower(name[i]))
        {
          id = schoolStudentTemp.id + 1;
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
    id = (studentClass * 1000) + (tolower(studentSection) - 96) * 100 + id;
  }
}

// Inputs student details
void Student::inputStudentDetails()
{
  system("cls");
  cout << "Enter student name (max. 28 characters): ";
  // fixes skipping of input; this must be used when `cin` precedes `getline()` or `cin.get()`
  cin.ignore();
  gets(name);
  cout << "Enter the class (1 to 12): ";
  cin >> studentClass;
  cout << "Enter the section ('A' to 'D'): ";
  cin.ignore();
  cin.get(studentSection);
  cout << "Enter the annual fee student needs to pay (in Rs.): ";
  cin >> studentFee;
  cout << "Enter student father's name (max. 28 characters): ";
  cin.ignore();
  gets(fatherName);
  cout << "Enter student mother's name (max. 28 characters): ";
  gets(motherName);
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
// Reflects the same in a data file
void receiveStudentFee()
{
  system("cls");
  Student schoolStudent;
  int inputRollNumber = 0, amountPaid = 0;
  short flag = 0;
  long filePosition = 0;
  fstream studentFile("data/student.dat", ios::in | ios::out | ios::binary);
  cout << "Enter the roll number of student whose fees you want to receive: ";
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
  else if (schoolStudent.getStudentFee() == 0)
    cout << "Congratulations! All dues are clear for student " << schoolStudent.getRollNumber() << ".";
  else
  {
    cout << "Remaining fees to be paid by student " << schoolStudent.getRollNumber() << " is Rs." << schoolStudent.getStudentFee() << ". Enter fee you want to receive (in Rs.): ";
    cin >> amountPaid;
    while (amountPaid > schoolStudent.getStudentFee() || amountPaid < 0)
    {
      cout << "Sorry, we received an invalid fee. Please enter again (in Rs.): ";
      cin >> amountPaid;
    }
    schoolStudent.deductFee(amountPaid);
    studentFile.seekg(filePosition);
    studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
    cout << "We have successfully received " << amountPaid << ". Now remaining fee for student " << schoolStudent.getRollNumber() << " is: " << schoolStudent.getStudentFee();
  }
  studentFile.close();
}

// Displays student sata records stored in student.dat file
void viewStudentData()
{
  system("cls");
  Student studentRead;
  ifstream fileToRead("data/student.dat", ios::binary);
  int inputRollNumber = 0;
  short flag = 0;
  cout << "Enter roll number of student whose data records you want to see: ";
  cin >> inputRollNumber;
  while (fileToRead.read((char *)&studentRead, sizeof(studentRead)))
  {
    if (inputRollNumber == studentRead.getRollNumber())
    {
      ++flag;
      break;
    }
  }
  if (flag != 0)
    studentRead.displayStudentData();
  else
    cout << "No match found.";
}
// --Everything for student Ends here--

// --Everything for teacher Starts here--
class Teacher : public SchoolMember
{
private:
  char teacherSubjects[29], teacherQualification[9];
  short teacherExperience, teacherClass, teacherSubjectCode[3];
  int teacherSalary;

public:
  Teacher()
  {
    teacherSubjectCode[0] = 0;
    teacherSubjectCode[1] = 0;
    teacherSubjectCode[2] = 0;
  }
  void inputTeacherDetails();
  void generateTeacherId();
  void deductTeacherSalary(int salaryPaid) { teacherSalary = teacherSalary - salaryPaid; }
  void displayTeacherData() const
  {
    cout << "\nName: " << name << "\nID: " << id << "\nTeacher Qualification: " << teacherQualification << "\nExperience: " << teacherExperience << " years"
         << "\nClass taught: " << teacherClass << "\nSubjects taught: " << teacherSubjects
         << "\nSalary to be paid: Rs." << teacherSalary;
  }
  int getTeacherId() const { return id; }
  int getTeacherSalary() const { return teacherSalary; }
};

// Generates id in format: first three digits are subject code of subject the teacher teaches and the last two digits are
// incremented when same subject set of teacher is found. For e.g. 12305 indicates that teacher teach subject codes 1, 2 & 3 and
// is the 5th teacher to teach the same three subjects in school.
void Teacher::generateTeacherId()
{
  Teacher schoolTeacherRead;
  ifstream teacherFile("data/teacher.dat", ios::binary);
  short tempId = 1, arrayEquality = 0, loopCounter = 0;
  while (teacherFile.read((char *)&schoolTeacherRead, sizeof(schoolTeacherRead)))
  {
    arrayEquality = 0;
    for (loopCounter = 0; loopCounter < 3; ++loopCounter)
    {
      if (teacherSubjectCode[loopCounter] == schoolTeacherRead.teacherSubjectCode[loopCounter])
        ++arrayEquality;
    }
    if (arrayEquality == loopCounter)
      tempId++;
  }
  id = (teacherSubjectCode[0] * 10000) + (teacherSubjectCode[1] * 1000) + (teacherSubjectCode[2] * 100) + tempId;
}

// Take all teacher inputs
void Teacher::inputTeacherDetails()
{
  system("cls");
  short flag = 0;
  char userChoice, keepRunning;
  cout << "Enter teacher name (max. 28 characters): ";
  cin.ignore();
  gets(name);
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
  setTeacherSubjects(teacherSubjectCode, teacherSubjects);
  cout << "\nEnter teacher annual salary (in Rs.): ";
  cin >> teacherSalary;
  cout << "Enter teacher work experience (in years): ";
  cin >> teacherExperience;
  cout << "Enter teacher educational qualification (max. 8 characters): ";
  cin.ignore();
  gets(teacherQualification);
  generateTeacherId();
  cout << "\nGenerated teacher ID is " << getTeacherId() << ". Please, note it safely as it'll be asked during data modification.";
}

// Adds new teacher
void addTeacher()
{
  Teacher schoolTeacher;
  fstream teacherFile("data/teacher.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolTeacher.inputTeacherDetails();
  teacherFile.write((char *)&schoolTeacher, sizeof(schoolTeacher));
  teacherFile.close();
}

// Removes an existing teacher
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

// Pay salary to teacher then deducts from remaining
// Reflects the same in teacher.dat
void paySalaryToTeacher()
{
  system("cls");
  Teacher schoolTeacher;
  int inputTeacherId = 0, salaryPaid = 0;
  long filePosition = 0;
  short flag = 0;
  fstream teacherFile("data/teacher.dat", ios::in | ios::out | ios::binary);
  cout << "Enter ID of teacher to pay salary: ";
  cin >> inputTeacherId;
  while (!teacherFile.eof())
  {
    filePosition = teacherFile.tellg();
    teacherFile.read((char *)&schoolTeacher, sizeof(schoolTeacher));
    if (inputTeacherId == schoolTeacher.getTeacherId())
    {
      ++flag;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, no teacher found with ID " << inputTeacherId << ".";
  else if (schoolTeacher.getTeacherSalary() == 0)
    cout << "Congratulations! Total annual salary has been paid to teacher " << schoolTeacher.getTeacherId() << ".";
  else
  {
    cout << "Remaining salary to be paid to teacher " << schoolTeacher.getTeacherId() << " is Rs. " << schoolTeacher.getTeacherSalary() << ". Enter the salary to be paid (in Rs.): ";
    cin >> salaryPaid;
    while (salaryPaid > schoolTeacher.getTeacherSalary() || salaryPaid < 0)
    {
      cout << "You have entered invalid salary. Please enter a valid salary (in Rs.): ";
      cin >> salaryPaid;
    }
    schoolTeacher.deductTeacherSalary(salaryPaid);
    teacherFile.seekg(filePosition);
    teacherFile.write((char *)&schoolTeacher, sizeof(schoolTeacher));
    cout << "You have successfully paid " << salaryPaid << ". Now remaining salary for teacher " << schoolTeacher.getTeacherId() << " is : Rs." << schoolTeacher.getTeacherSalary();
  }
  teacherFile.close();
}

void viewTeacherData()
{
  system("cls");
  Teacher teacherRead;
  ifstream fileToRead("data/teacher.dat", ios::binary);
  int inputId = 0;
  short flag = 0;
  cout << "Enter ID of teacher whose data records you want to see: ";
  cin >> inputId;
  while (fileToRead.read((char *)&teacherRead, sizeof(teacherRead)))
  {
    if (inputId == teacherRead.getTeacherId())
    {
      ++flag;
      break;
    }
  }
  if (flag != 0)
    teacherRead.displayTeacherData();
  else
    cout << "No match found.";
}
// --Everything for teacher Ends here--

// --Everything for staff Starts here--
class Staff : public SchoolMember
{
private:
  char staffDepartment[29];
  int staffSalary;
  short staffDepartmentCode;

public:
  void inputStaffDetails();
  void generateStaffId();
  void displayStaffData() const
  {
    cout << "\nName: " << name << "\nID: " << id << "\nDepartment: " << staffDepartment
         << "\nSalary to be paid: Rs. " << staffSalary;
  }
  void deductStaffSalary(int salaryPaid) { staffSalary = staffSalary - salaryPaid; }
  int getStaffSalary() const { return staffSalary; }
  int getStaffId() const { return id; }
};

// Generate staff id in format as explained:
// First digit indicates staff department, it is multiplied by 1000
// Then if same staff department is found, id is incremented by 1
void Staff::generateStaffId()
{
  Staff staffRead;
  short tempId = 1;
  ifstream fileToRead("data/staff.dat", ios::binary);
  while (fileToRead.read((char *)&staffRead, sizeof(staffRead)))
  {
    if (staffDepartmentCode == staffRead.staffDepartmentCode)
      tempId++;
  }
  id = (staffDepartmentCode * 1000) + tempId;
}

// All staff inputs
void Staff::inputStaffDetails()
{
  system("cls");
  cout << "Enter staff name (max. 28 characters): ";
  cin.ignore();
  gets(name);
  cout << "\nDepartment Code\t\tName of Department\n\t1\t\tCleaning\n\t2\t\tManagement\n\t3\t\tOffice work\n\t4\t\tOthers";
  cout << "\nEnter department code from above list to assign staff to that department: ";
  cin >> staffDepartmentCode;
  while (staffDepartmentCode > 4 || staffDepartmentCode < 1)
  {
    cout << "\nSorry, we received a wrong department code. Please enter valid department code viz. 1, 2, 3 or 4: ";
    cin >> staffDepartmentCode;
  }
  switch (staffDepartmentCode)
  {
  case 1:
    strcpy(staffDepartment, "Cleaning");
    break;
  case 2:
    strcpy(staffDepartment, "Management");
    break;
  case 3:
    strcpy(staffDepartment, "Office Work");
    break;
  case 4:
    strcpy(staffDepartment, "Others");
    break;
  }
  cout << "Enter staff annual salary (in Rs.): ";
  cin >> staffSalary;
  generateStaffId();
  cout << "Generated staff ID is " << getStaffId() << ". Please, note it safely as it'll be asked during data modification.";
}

// Removal of existing staff
void removeStaff()
{
  Staff staffRead;
  int inputStaffId;
  short flag = 0;
  ifstream fileToRead("data/staff.dat", ios::binary);
  ofstream fileToWrite("data/temp_staff.dat", ios::binary | ios::app);
  cout << "Enter ID of staff whose data has to be removed: ";
  cin >> inputStaffId;
  while (fileToRead.read((char *)&staffRead, sizeof(staffRead)))
  {
    if (inputStaffId == staffRead.getStaffId())
      flag++;
    else
      fileToWrite.write((char *)&staffRead, sizeof(staffRead));
  }
  if (flag == 0)
    cout << "Sorry, No Match found.";
  else
    cout << "Data of staff " << inputStaffId << " has been removed from file.";
  fileToRead.close();
  fileToWrite.close();
  remove("data/staff.dat");
  rename("data/temp_staff.dat", "data/staff.dat");
}

// Adds new staff
void addStaff()
{
  Staff schoolStaff;
  fstream staffFile("data/staff.dat", ios::in | ios::out | ios::app | ios::binary);
  schoolStaff.inputStaffDetails();
  staffFile.write((char *)&schoolStaff, sizeof(schoolStaff));
  staffFile.close();
}

// Pay salary to staff.
// Deduct salary paid and reflect in staff.dat file.
void paySalaryToStaff()
{
  system("cls");
  Staff schoolStaff;
  int inputStaffId = 0, salaryPaid = 0;
  long filePosition = 0;
  short flag = 0;
  fstream staffFile("data/staff.dat", ios::in | ios::out | ios::binary);
  cout << "Enter ID of staff to pay salary: ";
  cin >> inputStaffId;
  while (!staffFile.eof())
  {
    filePosition = staffFile.tellg();
    staffFile.read((char *)&schoolStaff, sizeof(schoolStaff));
    if (inputStaffId == schoolStaff.getStaffId())
    {
      ++flag;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, no staff found with ID " << inputStaffId << ".";
  else if (schoolStaff.getStaffSalary() == 0)
    cout << "Congratulations! Total annual salary has been paid to staff " << schoolStaff.getStaffId() << ".";
  else
  {
    cout << "Remaining salary to be paid to staff " << schoolStaff.getStaffId() << " is Rs. " << schoolStaff.getStaffSalary() << ". Enter the salary to be paid (in Rs.): ";
    cin >> salaryPaid;
    while (salaryPaid > schoolStaff.getStaffSalary() || salaryPaid < 0)
    {
      cout << "You have entered invalid salary. Please enter a valid salary (in Rs.): ";
      cin >> salaryPaid;
    }
    schoolStaff.deductStaffSalary(salaryPaid);
    staffFile.seekg(filePosition);
    staffFile.write((char *)&schoolStaff, sizeof(schoolStaff));
    cout << "You have successfully paid " << salaryPaid << ". Now remaining salary for staff " << schoolStaff.getStaffId() << " is: Rs." << schoolStaff.getStaffSalary();
  }
  staffFile.close();
}
void viewStaffData()
{
  system("cls");
  Staff staffRead;
  ifstream fileToRead("data/staff.dat", ios::binary);
  int inputId = 0;
  short flag = 0;
  cout << "Enter ID of staff whose data records you want to see: ";
  cin >> inputId;
  while (fileToRead.read((char *)&staffRead, sizeof(staffRead)))
  {
    if (inputId == staffRead.getStaffId())
    {
      ++flag;
      break;
    }
  }
  if (flag != 0)
    staffRead.displayStaffData();
  else
    cout << "No match found.";
}
// --Everything for staff Ends here--

// --Everything for student academics starts here--
class Academic : public Student
{
  // Under progress...
};
// --Everything for student academics ends here--

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
    removeStaff();
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
    addStaff();
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
  cout << "\nG. Receive student fee\t\t\t\t\t\t\tJ. View student academics report";
  cout << "\nH. Pay salary to school teacher\t\t\t\t\t\tK. Generate student academic report";
  cout << "\nI. Pay salary to school staff\t\t\t\t\t\tL. Generate student attendance report";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press 'A' to 'Add a new student, teacher or staff': ";
  char expectedInput[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
  cin >> menuOption;
  validateCharInput(menuOption, expectedInput, 12);
  switch (menuOption)
  {
  case 'a':
    displayAddDataScreen();
    break;
  case 'b':
    displayRemoveDataScreen();
    break;
  case 'c':
    // Update data section
    break;
  case 'd':
    viewStudentData();
    break;
  case 'e':
    viewTeacherData();
    break;
  case 'f':
    viewStaffData();
    break;
  case 'g':
    receiveStudentFee();
    break;
  case 'h':
    paySalaryToTeacher();
    break;
  case 'i':
    paySalaryToStaff();
    break;
  case 'j':
    break;
  case 'k':
    break;
  case 'l':
    break;
    // Default case will never get executed ;)
  }
}

int main(void)
{
  HomeScreen();
}
