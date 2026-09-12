#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;
//STRUCTURES
struct Student{
    int id;
    string name;
    string program;
    int semester;
};
struct Attendance{
    int studentId;
    string date;
    string status;
};
struct Result{
    int studentId;
    float subject1;
    float subject2;
    float subject3;
    float finalGrade;
};
//GLOBAL DATA
vector<Student> students;
vector<Attendance> attendanceRecords;
vector<Result> results;
//FILE HANDLING
void saveStudents(){
    ofstream file("students.txt");
    for (const Student& s : students){
        file << s.id << "|"
            << s.name << "|"
            << s.program << "|"
            << s.semester << endl;
    }
    file.close();
}
void loadStudents(){
    ifstream file("students.txt");
    if (!file)
        return;
    Student s;
    string line;
    while (getline(file, line)){
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            continue;
        s.id = stoi(line.substr(0, p1));
        s.name = line.substr(p1 + 1, p2 - p1 - 1);
        s.program = line.substr(p2 + 1, p3 - p2 - 1);
        s.semester = stoi(line.substr(p3 + 1));
        students.push_back(s);
    }
    file.close();
}
void saveAttendance(){
    ofstream file("attendance.txt");
    for (const Attendance& a : attendanceRecords){
        file << a.studentId << "|"
            << a.date << "|"
            << a.status << endl;
    }
    file.close();
}
void loadAttendance(){
    ifstream file("attendance.txt");
    if (!file)
        return;
    Attendance a;
    string line;
    while (getline(file, line)){
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        if (p1 == string::npos || p2 == string::npos)
            continue;
        a.studentId = stoi(line.substr(0, p1));
        a.date = line.substr(p1 + 1, p2 - p1 - 1);
        a.status = line.substr(p2 + 1);
        attendanceRecords.push_back(a);
    }
    file.close();
}
void saveResults(){
    ofstream file("results.txt");
    for (const Result& r : results){
        file << r.studentId << "|"
            << r.subject1 << "|"
            << r.subject2 << "|"
            << r.subject3 << "|"
            << r.finalGrade << endl;
    }
    file.close();
}
void loadResults(){
    ifstream file("results.txt");
    if (!file)
        return;
    Result r;
    string line;
    while (getline(file, line)){
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        if (p1 == string::npos || p2 == string::npos ||
            p3 == string::npos || p4 == string::npos)
            continue;
        r.studentId = stoi(line.substr(0, p1));
        r.subject1 = stof(line.substr(p1 + 1, p2 - p1 - 1));
        r.subject2 = stof(line.substr(p2 + 1, p3 - p2 - 1));
        r.subject3 = stof(line.substr(p3 + 1, p4 - p3 - 1));
        r.finalGrade = stof(line.substr(p4 + 1));
        results.push_back(r);
    }
    file.close();
}
//HELPER FUNCTIONS
int findStudentIndex(int id){
    for (int i = 0; i < students.size(); i++){
        if (students[i].id == id)
            return i;
    }
    return -1;
}
int findResultIndex(int studentId){
    for (int i = 0; i < results.size(); i++){
        if (results[i].studentId == studentId)
            return i;
    }
    return -1;
}
float calculateAverage(float a, float b, float c){
    return (a + b + c) / 3.0;
}
string getGrade(float average){
    if (average >= 85)
        return "A";
    if (average >= 75)
        return "B";
    if (average >= 65)
        return "C";
    if (average >= 50)
        return "D";
    return "F";
}
bool validMarks(float marks){
    return marks >= 0 && marks <= 100;
}
//STUDENT MANAGEMENT
// Story 1: Add New Student Record
void addStudent()
{
    Student s;
    cout << "\n========== ADD NEW STUDENT ==========\n";
    cout << "Enter Student ID: ";
    cin >> s.id;
    if (findStudentIndex(s.id) != -1)
    {
        cout << "Error: Student ID already exists.\n";
        return;
    }
    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, s.name);
    cout << "Enter Program: ";
    getline(cin, s.program);
    cout << "Enter Semester: ";
    cin >> s.semester;
    if (s.semester < 1 || s.semester > 8)
    {
        cout << "Invalid semester.\n";
        return;
    }
    students.push_back(s);
    saveStudents();
    cout << "\nStudent record added successfully!\n";
}
// Story 2: View Student Details
void viewStudent()
{
    int id;
    cout << "\n========== VIEW STUDENT DETAILS ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    int index = findStudentIndex(id);
    if (index == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    Student s = students[index];
    cout << "\nStudent ID: " << s.id << endl;
    cout << "Name: " << s.name << endl;
    cout << "Program: " << s.program << endl;
    cout << "Semester: " << s.semester << endl;
}
// Story 3: Update Student Information
void updateStudent()
{
    int id;
    cout << "\n========== UPDATE STUDENT ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    int index = findStudentIndex(id);
    if (index == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    cin.ignore();
    cout << "Enter New Name: ";
    getline(cin, students[index].name);
    cout << "Enter New Program: ";
    getline(cin, students[index].program);
    cout << "Enter New Semester: ";
    cin >> students[index].semester;
    if (students[index].semester < 1 ||
        students[index].semester > 8)
    {
        cout << "Invalid semester.\n";
        return;
    }
    saveStudents();
    cout << "\nStudent information updated successfully!\n";
}
// Story 4: Search Students by ID or Name
void searchStudents()
{
    string search;
    cout << "\n========== SEARCH STUDENTS ==========\n";
    cout << "Enter Student ID or Name: ";
    cin.ignore();
    getline(cin, search);
    bool found = false;
    for (const Student& s : students)
    {
        string id = to_string(s.id);
        string studentName = s.name;
        transform(studentName.begin(), studentName.end(),
            studentName.begin(), ::tolower);
        string searchText = search;
        transform(searchText.begin(), searchText.end(),
            searchText.begin(), ::tolower);
        if (id == search || studentName.find(searchText) != string::npos)
        {
            cout << "\nID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Program: " << s.program << endl;
            cout << "Semester: " << s.semester << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No matching student found.\n";
}
//ATTENDANCE MANAGEMENT
// Story 5: Mark Student Attendance
void markAttendance()
{
    Attendance a;
    cout << "\n========== MARK ATTENDANCE ==========\n";
    cout << "Enter Student ID: ";
    cin >> a.studentId;
    if (findStudentIndex(a.studentId) == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    cin.ignore();
    cout << "Enter Date (DD-MM-YYYY): ";
    getline(cin, a.date);
    // Prevent duplicate attendance
    for (const Attendance& record : attendanceRecords)
    {
        if (record.studentId == a.studentId &&
            record.date == a.date)
        {
            cout << "Attendance already exists for this date.\n";
            return;
        }
    }
    cout << "Enter Status (Present/Absent/Late): ";
    getline(cin, a.status);
    if (a.status != "Present" &&
        a.status != "Absent" &&
        a.status != "Late")
    {
        cout << "Invalid attendance status.\n";
        return;
    }
    attendanceRecords.push_back(a);
    saveAttendance();
    cout << "\nAttendance marked successfully!\n";
}
// Story 6: View Attendance Records
void viewAttendance()
{
    int id;
    cout << "\n========== VIEW ATTENDANCE ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    if (findStudentIndex(id) == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    bool found = false;
    cout << "\nDate\t\tStatus\n";
    cout << "-----------------------------\n";
    for (const Attendance& a : attendanceRecords)
    {
        if (a.studentId == id)
        {
            cout << a.date << "\t" << a.status << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No attendance records found.\n";
}
// Story 7: Update Attendance Record
void updateAttendance()
{
    int id;
    string date;
    cout << "\n========== UPDATE ATTENDANCE ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Date (DD-MM-YYYY): ";
    getline(cin, date);
    for (Attendance& a : attendanceRecords)
    {
        if (a.studentId == id && a.date == date)
        {
            cout << "Current Status: " << a.status << endl;
            cout << "Enter New Status (Present/Absent/Late): ";
            getline(cin, a.status);
            if (a.status != "Present" &&
                a.status != "Absent" &&
                a.status != "Late")
            {
                cout << "Invalid status.\n";
                return;
            }
            saveAttendance();
            cout << "Attendance updated successfully!\n";
            return;
        }
    }
    cout << "Attendance record not found.\n";
}
// Story 8: View Attendance Summary
void attendanceSummary()
{
    int id;
    cout << "\n========== ATTENDANCE SUMMARY ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    if (findStudentIndex(id) == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    int present = 0;
    int absent = 0;
    int late = 0;
    for (const Attendance& a : attendanceRecords)
    {
        if (a.studentId == id)
        {
            if (a.status == "Present")
                present++;
            else if (a.status == "Absent")
                absent++;
            else if (a.status == "Late")
                late++;
        }
    }
    int total = present + absent + late;
    cout << "\nPresent: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
    cout << "Total Records: " << total << endl;
    if (total > 0)
    {
        float percentage =
            ((float)present / total) * 100;
        cout << fixed << setprecision(2);
        cout << "Present Percentage: "
            << percentage << "%\n";
    }
}
//RESULT MANAGEMENT
// Story 9: Enter Student Grades
void enterGrades()
{
    Result r;
    cout << "\n========== ENTER STUDENT GRADES ==========\n";
    cout << "Enter Student ID: ";
    cin >> r.studentId;
    if (findStudentIndex(r.studentId) == -1)
    {
        cout << "Student record not found.\n";
        return;
    }
    if (findResultIndex(r.studentId) != -1)
    {
        cout << "Result already exists. Use Update Student Result.\n";
        return;
    }
    cout << "Enter Subject 1 Marks: ";
    cin >> r.subject1;
    cout << "Enter Subject 2 Marks: ";
    cin >> r.subject2;
    cout << "Enter Subject 3 Marks: ";
    cin >> r.subject3;
    if (!validMarks(r.subject1) ||
        !validMarks(r.subject2) ||
        !validMarks(r.subject3))
    {
        cout << "Marks must be between 0 and 100.\n";
        return;
    }
    r.finalGrade =
        calculateAverage(r.subject1,
            r.subject2,
            r.subject3);
    results.push_back(r);
    saveResults();
    cout << "\nGrades saved successfully!\n";
    cout << "Final Percentage: "
        << fixed << setprecision(2)
        << r.finalGrade << "%\n";
    cout << "Grade: "
        << getGrade(r.finalGrade) << endl;
}
// Story 10: View Student Results
void viewResults()
{
    int id;
    cout << "\n========== VIEW STUDENT RESULTS ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    int index = findResultIndex(id);
    if (index == -1)
    {
        cout << "Result not found.\n";
        return;
    }
    Result r = results[index];
    cout << fixed << setprecision(2);
    cout << "\nStudent ID: " << r.studentId << endl;
    cout << "Subject 1: " << r.subject1 << endl;
    cout << "Subject 2: " << r.subject2 << endl;
    cout << "Subject 3: " << r.subject3 << endl;
    cout << "Final Percentage: " << r.finalGrade << "%" << endl;
    cout << "Final Grade: " << getGrade(r.finalGrade) << endl;
}
// Story 11: Calculate Final Grade
void calculateFinalGrade()
{
    int id;
    cout << "\n========== CALCULATE FINAL GRADE ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    int index = findResultIndex(id);
    if (index == -1)
    {
        cout << "Result not found. Enter grades first.\n";
        return;
    }
    Result& r = results[index];
    r.finalGrade =
        calculateAverage(r.subject1,
            r.subject2,
            r.subject3);
    saveResults();
    cout << fixed << setprecision(2);
    cout << "\nFinal Percentage: "
        << r.finalGrade << "%\n";
    cout << "Final Grade: "
        << getGrade(r.finalGrade) << endl;
}
// Story 12: Update Student Result
void updateResult()
{
    int id;
    cout << "\n========== UPDATE STUDENT RESULT ==========\n";
    cout << "Enter Student ID: ";
    cin >> id;
    int index = findResultIndex(id);
    if (index == -1)
    {
        cout << "Result not found.\n";
        return;
    }
    Result& r = results[index];
    cout << "Enter New Subject 1 Marks: ";
    cin >> r.subject1;
    cout << "Enter New Subject 2 Marks: ";
    cin >> r.subject2;
    cout << "Enter New Subject 3 Marks: ";
    cin >> r.subject3;
    if (!validMarks(r.subject1) ||
        !validMarks(r.subject2) ||
        !validMarks(r.subject3))
    {
        cout << "Marks must be between 0 and 100.\n";
        return;
    }
    r.finalGrade =
        calculateAverage(r.subject1,
            r.subject2,
            r.subject3);
    saveResults();
    cout << "\nStudent result updated successfully!\n";
}
//MENUS
void studentMenu()
{
    int choice;
    do
    {
        cout << "\n====================================\n";
        cout << "       STUDENT MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Add New Student Record\n";
        cout << "2. View Student Details\n";
        cout << "3. Update Student Information\n";
        cout << "4. Search Students by ID or Name\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            searchStudents();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
void attendanceMenu()
{
    int choice;
    do
    {
        cout << "\n====================================\n";
        cout << "       ATTENDANCE MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Mark Student Attendance\n";
        cout << "2. View Attendance Records\n";
        cout << "3. Update Attendance Record\n";
        cout << "4. View Attendance Summary\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            markAttendance();
            break;
        case 2:
            viewAttendance();
            break;
        case 3:
            updateAttendance();
            break;
        case 4:
            attendanceSummary();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
void resultMenu()
{
    int choice;
    do
    {
        cout << "\n====================================\n";
        cout << "      RESULT / GRADE MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Enter Student Grades\n";
        cout << "2. View Student Results\n";
        cout << "3. Calculate Final Grade\n";
        cout << "4. Update Student Result\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            enterGrades();
            break;
        case 2:
            viewResults();
            break;
        case 3:
            calculateFinalGrade();
            break;
        case 4:
            updateResult();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
//MAIN
int main()
{
    loadStudents();
    loadAttendance();
    loadResults();
    int choice;
    cout << "============================================\n";
    cout << "     UNIVERSITY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    do
    {
        cout << "\n============================================\n";
        cout << "              MAIN MENU\n";
        cout << "============================================\n";
        cout << "1. Student Management\n";
        cout << "2. Attendance Management\n";
        cout << "3. Result / Grade Management\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            studentMenu();
            break;
        case 2:
            attendanceMenu();
            break;
        case 3:
            resultMenu();
            break;
        case 4:
            cout << "\nThank you for using University Management System!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}