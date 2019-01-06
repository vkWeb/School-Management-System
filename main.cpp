#include <iostream>          // For basic I/O operations e.g. cin, cout, etc.
#include <fstream>           // For data file handling
#include <iomanip>           // Manipulates floating point numbers and also manipulates console I/O
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

  int getId() const { return id; }
};

// Help Tip:
// If you are new to template functions. You should definitely learn about it.
// Template functions hugely reduces code duplication.
// Learn more about function templates here: https://www.learncpp.com/cpp-tutorial/131-function-templates/

// Using function template to remove contents of student, teacher or staff (as per user choice)
template <typename T>
void removeMember(const string filePath, const string tempFilePath, const T &schoolMember)
{
  system("cls");
  int inputId = 0;
  short flag = 0;
  ifstream fileToRead(filePath, ios::binary);
  ofstream fileToWrite(tempFilePath, ios::binary | ios::app);
  cout << "Enter ID of person whose data has to be removed: ";
  cin >> inputId;
  while (fileToRead.read((char *)&schoolMember, sizeof(schoolMember)))
  {
    if (inputId == schoolMember.getId())
      flag++;
    else
      fileToWrite.write((char *)&schoolMember, sizeof(schoolMember));
  }
  if (flag == 0)
    cout << "Sorry, No Match found.";
  else
    cout << "Data of ID " << inputId << " has been removed from file.";
  fileToRead.close();
  fileToWrite.close();
  remove(filePath.c_str());
  rename(tempFilePath.c_str(), filePath.c_str());
}

// Using function template to add contents of student, teacher or staff
template <typename T>
void addMember(const string filePath, T &schoolMember)
{
  fstream file(filePath, ios::in | ios::out | ios::app | ios::binary);
  schoolMember.inputDetails();
  file.write((char *)&schoolMember, sizeof(schoolMember));
  file.close();
}

// Allow users to view student, teacher or staff data records
template <typename T>
void viewData(const string filePath, const T &schoolMember)
{
  system("cls");
  ifstream fileToRead(filePath, ios::binary);
  int inputId = 0;
  short flag = 0;
  cout << "Enter ID of person whose data records you want to see: ";
  cin >> inputId;
  while (fileToRead.read((char *)&schoolMember, sizeof(schoolMember)))
  {
    if (inputId == schoolMember.getId())
    {
      ++flag;
      break;
    }
  }
  if (flag > 0)
    schoolMember.displayData();
  else
    cout << "No match found.";
}

// Allow users to update student, teacher or staff data records
// Ask for ID or rollnumber. Proceed to next step only if roll number exist in passed `filePath`
// If roll number exist, call `updateData()` and write to file.
template <typename T>
void updateMemberData(const string filePath, T &schoolMember)
{
  system("cls");
  int inputId = 0;
  short flag = 0;
  long filePosition = 0;
  fstream file(filePath, ios::in | ios::out | ios::binary);
  if (file)
  {
    cout << "Enter ID or roll number of person whose data has to be updated: ";
    cin >> inputId;
    while (!file.eof())
    {
      filePosition = file.tellg();
      file.read((char *)&schoolMember, sizeof(schoolMember));
      if (inputId == schoolMember.getId())
      {
        ++flag;
        break;
      }
    }
    if (flag > 0)
    {
      schoolMember.updateData();
      file.seekg(filePosition);
      file.write((char *)&schoolMember, sizeof(schoolMember));
      cout << "\nFile has been successfully updated.";
    }
    else
      cout << "Sorry, no match found.";
  }
  else
    cout << "\nThere's something wrong with file "
         << filePath << ". Please, make sure it exists.\n";
}

// --Everything for student Starts here--
class Student : public SchoolMember
{
private:
  int studentFee;

protected:
  short studentClass;
  char motherName[29], fatherName[29], studentSection;
  // using SchoolMember::id;

public:
  Student()
  {
    id = 1;
  }

  // int getId() const { SchoolMember::getId(); }
  void inputDetails();
  void updateData();
  void generateRollNumber();
  void displayData() const
  {
    cout << "\nName: " << name << "\nRoll Number: " << id << "\nClass: " << studentClass << " '" << char(toupper(studentSection)) << "' "
         << "\nMother's name: " << motherName << "\nFather's name: " << fatherName << "\nRemaining fee: Rs." << studentFee;
  }
  void deductFee(int amountPaid) { studentFee = studentFee - amountPaid; }
  int getStudentFee() const { return studentFee; }
  string getName() const { return name; }
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
      ++flag;
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
    id = (studentClass * 1000) + (tolower(studentSection) - 96) * 100 + id;
}

// Input student details
void Student::inputDetails()
{
  system("cls");
  cout << "Enter student name (max. 28 characters): ";
  // fixes skipping of input; this must be used when `cin` precedes `getline()` or `cin.get()`
  cin.ignore();
  gets(name);
  cout << "Enter the class (1 to 12): ";
  cin >> studentClass;
  cout << "Enter the section ('A' to 'D'): ";
  cin >> studentSection;
  cout << "Enter the annual fee student needs to pay (in Rs.): ";
  cin >> studentFee;
  cout << "Enter student father's name (max. 28 characters): ";
  cin.ignore();
  gets(fatherName);
  cout << "Enter student mother's name (max. 28 characters): ";
  gets(motherName);
  generateRollNumber();
  cout << "\nGenerated roll number is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
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
    if (inputRollNumber == schoolStudent.getId())
    {
      flag++;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, Roll number not found.";
  else if (schoolStudent.getStudentFee() == 0)
    cout << "Congratulations! All dues are clear for student " << schoolStudent.getId() << ".";
  else
  {
    cout << "Remaining fees to be paid by student " << schoolStudent.getId() << " is Rs." << schoolStudent.getStudentFee() << ". Enter fee you want to receive (in Rs.): ";
    cin >> amountPaid;
    while (amountPaid > schoolStudent.getStudentFee() || amountPaid < 0)
    {
      cout << "Sorry, we received an invalid fee. Please enter again (in Rs.): ";
      cin >> amountPaid;
    }
    schoolStudent.deductFee(amountPaid);
    studentFile.seekg(filePosition);
    studentFile.write((char *)&schoolStudent, sizeof(schoolStudent));
    cout << "We have successfully received " << amountPaid << ". Now remaining fee for student " << schoolStudent.getId() << " is: " << schoolStudent.getStudentFee();
  }
  studentFile.close();
}

// Allow users to update student data records
// Asks for input fields, updates them if user wants
void Student::updateData()
{
  char userChoice = ' ';
  cout << "Press '+' to update student name or press 'Enter' key to retain old data: ";
  cin.ignore();
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10) // 10 is ASCII value of linefeed (enter key)
  {
    cout << "Enter new name (max. 28 characters): ";
    cin.ignore();
    gets(name);
  }
  cout << "\nPress '+' to update student class or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new class (1 - 12): ";
    cin.ignore();
    cin >> studentClass;
    cin.ignore();
  }
  cout << "\nPress '+' to update student section or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new section ('A' to 'D'): ";
    cin.ignore();
    cin >> studentSection;
    cin.ignore();
  }
  cout << "\nPress '+' to update student annual fee or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new annual fee (in Rs.): ";
    cin.ignore();
    cin >> studentFee;
    cin.ignore();
  }
  cout << "\nPress '+' to update student father's name or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter father's name (max. 28 characters): ";
    cin.ignore();
    gets(fatherName);
  }
  cout << "\nPress '+' to update student mother's name or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter mother's name (max. 28 characters): ";
    cin.ignore();
    gets(motherName);
  }
  generateRollNumber();
  cout << "\nGenerated roll number is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
}
// --Everything for student Ends here--

// --Everything for teacher Starts here--
class Teacher : public SchoolMember
{
private:
  char teacherSubject[17], teacherQualification[9];
  short teacherExperience, teacherClass, teacherSubjectCode;
  int teacherSalary;

public:
  Teacher()
  {
    teacherSubjectCode = 0;
    id = 1;
  }
  void inputDetails();
  void generateTeacherId();
  void updateData();
  void deductTeacherSalary(int salaryPaid) { teacherSalary = teacherSalary - salaryPaid; }
  void displayData() const
  {
    cout << "\nName: " << name << "\nID: " << id << "\nTeacher Qualification: " << teacherQualification << "\nExperience: " << teacherExperience << " years"
         << "\nClass taught: " << teacherClass << "\nSubject taught: " << teacherSubject
         << "\nSalary to be paid: Rs." << teacherSalary;
  }
  int getTeacherSalary() const { return teacherSalary; }
};

// Generates id in format as explained:
// The first two digits are of class taught, the next digit is subject taught
// And the last two digits tell us when teacher was added. The below example will make things clear:
// For e.g. 12102 means teacher teach class 12th,
// subject science (subject code of science is 1), is the second teacher in school to teach class 12th science
void Teacher::generateTeacherId()
{
  Teacher schoolTeacherRead;
  ifstream teacherFile("data/teacher.dat", ios::binary);
  short flag = 0;
  while (teacherFile.read((char *)&schoolTeacherRead, sizeof(schoolTeacherRead)))
  {
    if (teacherSubjectCode == schoolTeacherRead.teacherSubjectCode && teacherClass == schoolTeacherRead.teacherClass)
    {
      ++flag;
      id = schoolTeacherRead.id + 1;
    }
  }
  if (flag == 0)
    id = (teacherClass * 1000) + (teacherSubjectCode * 100) + id;
}

// Take all teacher inputs
void Teacher::inputDetails()
{
  system("cls");
  cout << "Enter teacher name (max. 28 characters): ";
  cin.ignore();
  gets(name);
  cout << "Enter the class to be taught (1 to 12): ";
  cin >> teacherClass;
  cout << "\nSubject Code\tSubject\n     1\t\tScience\n     2\t\tMaths\n     3\t\tEnglish\n     4\t\tHindi\n     5\t\tSocial Studies";
  cout << "\nEnter the subject code from the above list to choose subject the teacher will teach, for e.g. Press '1' to choose 'Science': ";
  cin >> teacherSubjectCode;
  while (teacherSubjectCode > 5 || teacherSubjectCode < 1)
  {
    cout << "\nSorry, we received a wrong subject code. Please enter valid subject code viz. 1, 2, 3, 4 or 5: ";
    cin >> teacherSubjectCode;
  }
  switch (teacherSubjectCode)
  {
  case 1:
    strcpy(teacherSubject, "Science");
    break;
  case 2:
    strcpy(teacherSubject, "Maths");
    break;
  case 3:
    strcpy(teacherSubject, "English");
    break;
  case 4:
    strcpy(teacherSubject, "Hindi");
    break;
  case 5:
    strcpy(teacherSubject, "Social Studies");
    break;
  }
  cout << "\nEnter teacher annual salary (in Rs.): ";
  cin >> teacherSalary;
  cout << "Enter teacher work experience (in years): ";
  cin >> teacherExperience;
  cout << "Enter teacher educational qualification (max. 8 characters): ";
  cin.ignore();
  gets(teacherQualification);
  generateTeacherId();
  cout << "\nGenerated teacher ID is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
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
    if (inputTeacherId == schoolTeacher.getId())
    {
      ++flag;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, no teacher found with ID " << inputTeacherId << ".";
  else if (schoolTeacher.getTeacherSalary() == 0)
    cout << "Congratulations! Total annual salary has been paid to teacher " << schoolTeacher.getId() << ".";
  else
  {
    cout << "Remaining salary to be paid to teacher " << schoolTeacher.getId() << " is Rs. " << schoolTeacher.getTeacherSalary() << ". Enter the salary to be paid (in Rs.): ";
    cin >> salaryPaid;
    while (salaryPaid > schoolTeacher.getTeacherSalary() || salaryPaid < 0)
    {
      cout << "You have entered invalid salary. Please enter a valid salary (in Rs.): ";
      cin >> salaryPaid;
    }
    schoolTeacher.deductTeacherSalary(salaryPaid);
    teacherFile.seekg(filePosition);
    teacherFile.write((char *)&schoolTeacher, sizeof(schoolTeacher));
    cout << "You have successfully paid " << salaryPaid << ". Now remaining salary for teacher " << schoolTeacher.getId() << " is : Rs." << schoolTeacher.getTeacherSalary();
  }
  teacherFile.close();
}

// Allow users to update teacher data records
// Asks for input fields, updates them if user wants
void Teacher::updateData()
{
  char userChoice = ' ';
  cout << "Press '+' to update teacher name or press 'Enter' key to retain old data: ";
  cin.ignore();
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10) // 10 is ASCII value of linefeed (enter key)
  {
    cout << "Enter new name (max. 28 characters): ";
    cin.ignore();
    gets(name);
    cin.ignore();
  }
  cout << "\nPress '+' to update teacher class or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new class (1 to 12): ";
    cin.ignore();
    cin >> teacherClass;
    cin.ignore();
  }
  cout << "\nPress '+' to update teacher subject code or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "\nSubject Code\tSubject\n     1\t\tScience\n     2\t\tMaths\n     3\t\tEnglish\n     4\t\tHindi\n     5\t\tSocial Studies";
    cout << "\nEnter the subject code from the above list to choose subject the teacher will teach, for e.g. Press '1' to choose 'Science': ";
    cin.ignore();
    cin >> teacherSubjectCode;
    cin.ignore();
    while (teacherSubjectCode > 5 || teacherSubjectCode < 1)
    {
      cout << "\nSorry, we received a wrong subject code. Please enter valid subject code viz. 1, 2, 3, 4 or 5: ";
      cin >> teacherSubjectCode;
    }
    switch (teacherSubjectCode)
    {
    case 1:
      strcpy(teacherSubject, "Science");
      break;
    case 2:
      strcpy(teacherSubject, "Maths");
      break;
    case 3:
      strcpy(teacherSubject, "English");
      break;
    case 4:
      strcpy(teacherSubject, "Hindi");
      break;
    case 5:
      strcpy(teacherSubject, "Social Studies");
      break;
    }
  }
  cout << "\nPress '+' to update teacher annual salary or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new annual salary (in Rs.): ";
    cin.ignore();
    cin >> teacherSalary;
    cin.ignore();
  }
  cout << "\nPress '+' to update teacher work experience or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new work experience (in years): ";
    cin.ignore();
    cin >> teacherExperience;
    cin.ignore();
  }
  cout << "\nPress '+' to update teacher educational qualification or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new educational qualification (max. 8 characters): ";
    cin.ignore();
    gets(teacherQualification);
    cin.ignore();
  }
  generateTeacherId();
  cout << "\nGenerated ID is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
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
  void inputDetails();
  void updateData();
  void generateStaffId();
  void displayData() const
  {
    cout << "\nName: " << name << "\nID: " << id << "\nDepartment: " << staffDepartment
         << "\nSalary to be paid: Rs. " << staffSalary;
  }
  void deductStaffSalary(int salaryPaid) { staffSalary = staffSalary - salaryPaid; }
  int getStaffSalary() const { return staffSalary; }
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
void Staff::inputDetails()
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
  cout << "Generated staff ID is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
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
    if (inputStaffId == schoolStaff.getId())
    {
      ++flag;
      break;
    }
  }
  if (flag == 0)
    cout << "Sorry, no staff found with ID " << inputStaffId << ".";
  else if (schoolStaff.getStaffSalary() == 0)
    cout << "Congratulations! Total annual salary has been paid to staff " << schoolStaff.getId() << ".";
  else
  {
    cout << "Remaining salary to be paid to staff " << schoolStaff.getId() << " is Rs. " << schoolStaff.getStaffSalary() << ". Enter the salary to be paid (in Rs.): ";
    cin >> salaryPaid;
    while (salaryPaid > schoolStaff.getStaffSalary() || salaryPaid < 0)
    {
      cout << "You have entered invalid salary. Please enter a valid salary (in Rs.): ";
      cin >> salaryPaid;
    }
    schoolStaff.deductStaffSalary(salaryPaid);
    staffFile.seekg(filePosition);
    staffFile.write((char *)&schoolStaff, sizeof(schoolStaff));
    cout << "You have successfully paid " << salaryPaid << ". Now remaining salary for staff " << schoolStaff.getId() << " is: Rs." << schoolStaff.getStaffSalary();
  }
  staffFile.close();
}

// Allow users to update staff data records
// Asks for input fields, updates them if user wants
void Staff::updateData()
{
  char userChoice = ' ';
  cout << "Press '+' to update staff name or press 'Enter' key to retain old data: ";
  cin.ignore();
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10) // 10 is ASCII value of linefeed (enter key)
  {
    cout << "Enter new name (max. 28 characters): ";
    cin.ignore();
    gets(name);
    cin.ignore();
  }
  cout << "\nPress '+' to update staff department code or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "\nDepartment Code\t\tName of Department\n\t1\t\tCleaning\n\t2\t\tManagement\n\t3\t\tOffice work\n\t4\t\tOthers";
    cout << "\nEnter department code from above list to assign staff to that department: ";
    cin.ignore();
    cin >> staffDepartmentCode;
    cin.ignore();
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
  }
  cout << "\nPress '+' to update staff annual salary or press 'Enter' key to retain old data: ";
  cin.get(userChoice);
  if (userChoice == '+' && userChoice != 10)
  {
    cout << "Enter new annual salary (in Rs.): ";
    cin.ignore();
    cin >> staffSalary;
    cin.ignore();
  }
  generateStaffId();
  cout << "\nGenerated ID is " << getId() << ". Please, note it safely as it'll be asked during data modification.";
}
// --Everything for staff Ends here--

// --Everything for student academics starts here--
class Academic
{
private:
  short marks[5], daysPresent, totalWorkingDays;
  float averageMarks, attendancePercentage;
  // using Student::id;

public:
  Academic()
  {
    marks[0] = 0;
    marks[1] = 0;
    marks[2] = 0;
    marks[3] = 0;
    marks[4] = 0;
    daysPresent = 0;
    totalWorkingDays = 0;
    averageMarks = 0.0f;
    attendancePercentage = 0.0f;
  }

  // int getId() const { Student::getId(); }
  void generateAcademicReport(Student, short &);
  void generateAttendanceReport(Student &, short &);
  void displayAttendanceReport(Student student)
  {
    cout << "Name: " << student.getName();
    cout << "\nRoll number: " << student.getId();
    cout << fixed << setprecision(1) << "\nAttendance percentage = " << attendancePercentage;
  }
};

// Generates student academic report
// Validates roll number, if roll number is found
// Then marks for five subjects is asked then average is calculated
void Academic::generateAcademicReport(Student studentRead, short &flag)
{
  system("cls");
  int inputRollNumber = 0;
  cout << "Enter student roll number whose academic report you want to generate: ";
  cin >> inputRollNumber;
  ifstream fileToRead("data/student.dat", ios::binary);
  while (fileToRead.read((char *)&studentRead, sizeof(studentRead)))
  {
    if (inputRollNumber == studentRead.getId())
    {
      ++flag;
      break;
    }
  }
  if (flag > 0)
  {
    cout << "\nEnter marks of student " << inputRollNumber << " between 0 to 100 in subjects asked below: ";
    cout << "\n1. Science = ";
    cin >> marks[0];
    validateSubjectMarks(marks, 0);
    cout << "2. Maths = ";
    cin >> marks[1];
    validateSubjectMarks(marks, 1);
    cout << "3. English = ";
    cin >> marks[2];
    validateSubjectMarks(marks, 2);
    cout << "4. Hindi = ";
    cin >> marks[3];
    validateSubjectMarks(marks, 3);
    cout << "5. Social Studies = ";
    cin >> marks[4];
    validateSubjectMarks(marks, 4);
    averageMarks = (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]) / 5;
    cout << fixed << setprecision(1) << "Generated Average Marks = " << averageMarks;
  }
  else
    cout << "No match found.";
}

// Generates student attendance report
// Validates roll number, if roll number is found
// Then total number of working days and days present is asked
// Attendance % is calculated as: (days present / total no. of days) * 100
void Academic::generateAttendanceReport(Student &studentRead, short &flag)
{
  system("cls");
  int inputRollNumber = 0;
  cout << "Enter student roll number whose attendance report you want to generate: ";
  cin >> inputRollNumber;
  ifstream fileToRead("data/student.dat", ios::binary);
  while (fileToRead.read((char *)&studentRead, sizeof(studentRead)))
  {
    if (inputRollNumber == studentRead.getId())
    {
      ++flag;
      break;
    }
  }
  if (flag > 0)
  {
    cout << "\nEnter total number of working days (1 - 366): ";
    cin >> totalWorkingDays;
    validateDays(totalWorkingDays);
    cout << "Enter number of days student " << inputRollNumber << " was present (1 - 366): ";
    cin >> daysPresent;
    validateDays(daysPresent);
    attendancePercentage = ((daysPresent / totalWorkingDays) * 100);
    cout << fixed << setprecision(1) << "Generated Attendance Percentage = " << attendancePercentage << "%";
  }
  else
    cout << "No match found.";
}

// Calls studentAcademics.generateAcademicReport(Student)
// And writes recorded information to academic_report.dat file
void academicReport()
{
  short flag = 0;
  Academic studentAcademics;
  Student studentRead;
  fstream reportFile("data/academic_report.dat", ios::in | ios::out | ios::app | ios::binary);
  studentAcademics.generateAcademicReport(studentRead, flag);
  if (flag > 0)
    reportFile.write((char *)&studentAcademics, sizeof(studentAcademics));
  reportFile.close();
}

// Calls studentAcademics.generateAttendanceReport(Student)
// And writes recorded information to attendance_report.dat file
void attendanceReport()
{
  short flag = 0;
  Academic studentAcademics;
  Student studentRead;
  fstream reportFile("data/attendance_report.dat", ios::in | ios::out | ios::app | ios::binary);
  studentAcademics.generateAttendanceReport(studentRead, flag);
  if (flag > 0)
  {
    reportFile.write((char *)&studentRead, sizeof(studentRead));
    reportFile.write((char *)&studentAcademics, sizeof(studentAcademics));
  }
  reportFile.close();
}

void viewAcademicReports()
{
  system("cls");
  Academic academicRead;
  Student studentRead;
  ifstream attendanceFile("data/attendance_report.dat", ios::binary);
  ifstream academicFile("data/academic_report.dat", ios::binary);
  int inputRollNumber = 0;
  short userChoice = 0, flag = 0;
  cout << "1. View academic report";
  cout << "\n2. View attendance report";
  cout << "\nEnter your choice (1 or 2): ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    cout << "\nEnter student roll number whose academic report you want to see: ";
    cin >> inputRollNumber;
    break;
  case 2:
    cout << "\nEnter student roll number whose attendance report you want to see: ";
    cin >> inputRollNumber;
    while (attendanceFile.read((char *)&studentRead, sizeof(studentRead)))
    {
      if (inputRollNumber == studentRead.getId())
      {
        attendanceFile.read((char *)&academicRead, sizeof(academicRead));
        ++flag;
        break;
      }
    }
    if (flag > 0)
      academicRead.displayAttendanceReport(studentRead);
    else
      cout << "No attendance report found for student " << inputRollNumber << ".";
    break;
  }
}
// --Everything for student academics ends here--

// Displays screen for addition of new student, teacher or staff
void displayAddDataScreen()
{
  system("cls");
  int userChoice = 0;
  Student schoolStudent;
  Teacher schoolTeacher;
  Staff schoolStaff;
  cout << "1. Add a new student";
  cout << "\n2. Add a new teacher";
  cout << "\n3. Add a new staff";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press '1' to 'Add a new student': ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    addMember("data/student.dat", schoolStudent);
    break;
  case 2:
    addMember("data/teacher.dat", schoolTeacher);
    break;
  case 3:
    addMember("data/staff.dat", schoolStaff);
    break;
  }
}

// Displays screen for removal of existing student, teacher or staff
void displayRemoveDataScreen()
{
  system("cls");
  int userChoice = 0;
  Student schoolStudent;
  Teacher schoolTeacher;
  Staff schoolStaff;
  cout << "1. Remove an existing student";
  cout << "\n2. Remove an existing teacher";
  cout << "\n3. Remove an existing staff";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press '1' to 'Remove an existing student': ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    removeMember("data/student.dat", "data/temp_student.dat", schoolStudent);
    break;
  case 2:
    removeMember("data/teacher.dat.dat", "data/temp_teacher.dat", schoolTeacher);
    break;
  case 3:
    removeMember("data/staff.dat", "data/temp_staff.dat", schoolStaff);
    break;
  }
}

// Give user options to choose whose data has to be updated
void displayUpdateDataScreen()
{
  system("cls");
  int userChoice = 0;
  Student schoolStudent;
  Teacher schoolTeacher;
  Staff schoolStaff;
  cout << "1. Update data of an existing student";
  cout << "\n2. Update data of an existing teacher";
  cout << "\n3. Update data of an existing staff";
  cout << "\n\n=> Enter your choice to proceed. For e.g. Press '1' to 'Update data of an existing student': ";
  cin >> userChoice;
  switch (userChoice)
  {
  case 1:
    updateMemberData("data/student.dat", schoolStudent);
    break;
  case 2:
    updateMemberData("data/teacher.dat", schoolTeacher);
    break;
  case 3:
    updateMemberData("data/staff.dat", schoolStaff);
    break;
  }
}

// Displays home screen
void HomeScreen()
{
  system("cls");
  char menuOption;
  Student schoolStudent;
  Teacher schoolTeacher;
  Staff schoolStaff;
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
    displayUpdateDataScreen();
    break;
  case 'd':
    viewData("data/student.dat", schoolStudent);
    break;
  case 'e':
    viewData("data/teacher.dat", schoolTeacher);
    break;
  case 'f':
    viewData("data/staff.dat", schoolStaff);
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
    // Vk note: viewAcademicReports() is WIP (work in progress)
    viewAcademicReports();
    break;
  case 'k':
    academicReport();
    break;
  case 'l':
    attendanceReport();
    break;
    // Congratulations! Default case will never get executed ;)
  }
}

int main(void)
{
  HomeScreen();
}
