#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

class Result
{
private:
    string semester;
    float averageScore;

public:
    Result() : semester(""), averageScore(0.0) {}
    Result(string semester, float score) : semester(semester), averageScore(score) {}
    Result(const Result &other) : semester(other.semester), averageScore(other.averageScore) {}
    ~Result() {}

    void input()
    {
        cout << "Enter semester: ";
        cin >> semester;
        cout << "Enter average score: ";
        cin >> averageScore;
    }

    void output() const
    {
        // cout << "Semester: " << setw(20) << ", Average Score: " << setw(20) << endl;
        cout << semester << averageScore << endl;
    }

    string getSemester() const
    {
        return semester;
    }

    float getAverageScore() const
    {
        return averageScore;
    }
};

class Person
{
private:
    string studentID;
    string fullName;
    string dateOfBirth;
    int yearOfEnrollment;
    float entranceScore;
    bool isPartTime;         // New attribute to indicate part-time status
    string trainingLocation; // New attribute for part-time students

    vector<Result> results;

public:
    Person() : studentID(""), fullName(""), dateOfBirth(""), yearOfEnrollment(0), entranceScore(0.0), isPartTime(false), trainingLocation("") {}
    Person(string id, string name, string dob, int year, float score, bool partTime, string location)
        : studentID(id), fullName(name), dateOfBirth(dob), yearOfEnrollment(year), entranceScore(score), isPartTime(partTime), trainingLocation(location) {}
    Person(const Person &other) : studentID(other.studentID), fullName(other.fullName), dateOfBirth(other.dateOfBirth), yearOfEnrollment(other.yearOfEnrollment), entranceScore(other.entranceScore), isPartTime(other.isPartTime), trainingLocation(other.trainingLocation), results(other.results) {}
    ~Person() {}

    void input()
    {
        cout << "Enter student ID: ";
        cin >> studentID;
        cout << "Enter full name: ";
        cin.ignore();
        getline(cin, fullName);
        cout << "Enter date of birth: ";
        cin >> dateOfBirth;
        cout << "Enter year of enrollment: ";
        cin >> yearOfEnrollment;
        cout << "Enter entrance score: ";
        cin >> entranceScore;
        cout << "Is this student part-time? (1 for yes, 0 for no): ";
        cin >> isPartTime;
        if (isPartTime)
        {
            cout << "Enter training location: ";
            cin >> trainingLocation;
        }
        int numResults;
        cout << "Enter number of results: ";
        cin >> numResults;
        for (int i = 0; i < numResults; ++i)
        {
            cout << "Result " << i + 1 << ":" << endl;
            Result result;
            result.input();
            results.push_back(result);
        }
    }

    double *output(double *arr) const
    {
        // int MaxentranceScore = 0;
        //  cout << "Student ID: " << setw(20) << "Full Name: " << setw(20) << "Date of Birth: " << setw(30) << "Year of Enrollment: " << setw(20) << "Entrance Score: " << setw(20) << "Training Location: " << endl;
        cout << studentID << setw(20) << fullName << setw(20) << dateOfBirth << setw(30) << yearOfEnrollment << setw(20) << entranceScore << setw(20) << trainingLocation;
        // cout << "Student ID: " << studentID << endl;
        // cout << "Full Name: " << fullName << endl;
        // cout << "Date of Birth: " << dateOfBirth << endl;
        // cout << "Year of Enrollment: " << yearOfEnrollment << endl;
        // cout << "Entrance Score: " << entranceScore << endl;
        // if (isPartTime)
        // {
        //     cout << "Student is part-time, Training Location: " << trainingLocation << endl;
        // }
        // cout << "Results:" << endl;
        for (const auto &result : results)
        {
            result.output();
        }
        if (isPartTime)
        {
            arr[1] = arr[1] + 1;
        }
        if (entranceScore > arr[2])
        {
            arr[2] = entranceScore;
        }
        return arr;
    }
    /* the largest number of students with the highest scores in the semester*/

    int outputHighEndYear(int endOfYear) const
    {

        if (yearOfEnrollment > endOfYear)
        {
            endOfYear = yearOfEnrollment;
        }
        return endOfYear;
    }
    /*create list have the largest number of students with the highest scores in the semester*/
    string listPastTime(int enOfYear, int HighScore)
    {
        string NameOfStudent;
        if (yearOfEnrollment == enOfYear)
        {
            if (entranceScore >= 8)
            {
                cout << studentID << setw(20) << fullName << setw(20) << dateOfBirth << setw(30) << yearOfEnrollment << setw(20) << entranceScore << setw(20) << trainingLocation;
            }
        }

        if (yearOfEnrollment > HighScore)
        {
            HighScore = yearOfEnrollment;
            NameOfStudent = studentID;
        }
        return NameOfStudent;
    }

    // /*Statistics on the number of students by year of admission.*/

    // int NumOfYear()
    // {
    //     map<int, int>  Year;

    //     Year[yearOfEnrollment]++;
    //     return Year[yearOfEnrollment];
    // }
    int getYearOfEnrollment() const
    {
        return yearOfEnrollment;
    }

    bool isRegular() const
    {
        return !isPartTime;
    }

    float getAverageScore(string semester) const
    {
        for (const auto &result : results)
        {
            if (result.getSemester() == semester)
            {
                return result.getAverageScore();
            }
        }
        return -1.0; // or throw exception if not found
    }

    string getFullName() const
    {
        return fullName;
    }
};

class Department
{
private:
    map<string, vector<Person *>> departments; // Map from department name to list of students

public:
    Department() {}

    void addStudent(const string &departmentName, Person *student)
    {
        departments[departmentName].push_back(student);
    }

    void inputStudents()
    {
        int numDepartments;
        cout << "Enter number of departments: ";
        cin >> numDepartments;
        for (int i = 0; i < numDepartments; ++i)
        {
            string departmentName;
            cout << "Enter name of department " << i + 1 << ": ";
            cin >> departmentName;

            int numStudents;
            cout << "Enter number of students in department " << departmentName << ": ";
            cin >> numStudents;

            for (int j = 0; j < numStudents; ++j)
            {
                cout << "Enter details for student " << j + 1 << " in department " << departmentName << ":" << endl;
                Person *student = new Person();
                student->input();
                addStudent(departmentName, student);
            }
        }
    }

    void outputStudents() const
    {
        int TheNumFulltime = 0;
        int TheNumPasttime = 0;
        double *p = new double[2];
        p[0] = 0; // Maximum entrance score
        p[1] = 0; // Number of part-time students

        for (const auto &department : departments)
        {
            cout << "Student ID: " << setw(20) << "Full Name: " << setw(20) << "Date of Birth: " << setw(30) << "Year of Enrollment: " << setw(20) << "Entrance Score: " << setw(20) << "Training Location: " << setw(20)
                 << "Semester: " << setw(20) << ", Average Score: " << setw(20) << endl;
            cout << "Students in Department " << department.first << ":" << endl;
            for (const auto &student : department.second)
            {
                p = student->output(p);
                cout << endl;
            }
            cout << endl;
            cout << " the number of student hác srouce high is:" << p[2] << endl;
            cout << " the number of student is full time is:" << p[1] << "\n"
                 << endl;
        }
    }
    /*the largest number of students with the highest scores in the semester and Highest semester average score*/
    void outputEndyear()
    {
        int enOfYear = 0;
        int HighScore = 0;
        string NameOfStudent;
        for (const auto &department : departments)
        {
            cout << "Students in Department " << department.first << ":" << endl;
            cout << "Student ID: " << setw(20) << "Full Name: " << setw(20) << "Date of Birth: " << setw(30) << "Year of Enrollment: " << setw(20) << "Entrance Score: " << setw(20) << "Training Location: " << setw(20)
                 << "Semester: " << setw(20) << ", Average Score: " << setw(20) << endl;
            enOfYear = 0;

            for (const auto &student : department.second)
            {
                enOfYear = student->outputHighEndYear(enOfYear);
                // cout << endl;
            }

            for (const auto &student : department.second)
            {
                NameOfStudent = student->listPastTime(enOfYear, HighScore);
                cout << "\n";
            }
            cout << endl;
            cout << " the student have Highest semester average score is: " << NameOfStudent << endl;
        }
    }

    void countStudentsByYear() const
    {
        for (const auto &department : departments)
        {
            map<int, int> yearCount; // Map to store count of students by enrollment year
            cout << "Department: " << department.first << endl;
            for (const auto &student : department.second)
            {
                int year = student->getYearOfEnrollment();
                yearCount[year]++;
            }
            // Output the count for each year
            for (const auto &pair : yearCount)
            {
                cout << "Year " << pair.first << ": " << pair.second << " students" << endl;
            }
            cout << endl;
        }
    }

    void addStudentToDepartment()
    {
        string studentName;
        cout << "Enter the name of the student: ";
        cin.ignore();
        getline(cin, studentName);

        Person *existingStudent = findStudent(studentName);
        if (existingStudent != nullptr)
        {
            cout << "Student " << studentName << " already exists." << endl;
            return;
        }

        // Student does not exist, prompt for department and create new student
        string departmentName;
        cout << "Enter the name of the department for the new student: ";
        cin >> departmentName;

        // Check if the department exists
        if (departments.find(departmentName) == departments.end())
        {
            cout << "Department " << departmentName << " does not exist." << endl;
            return;
        }

        // Create a new student
        Person *student = new Person();
        student->input();

        // Add the student to the department
        addStudent(departmentName, student);
    }

    Person *findStudent(const string &fullName) const
    {
        for (const auto &department : departments)
        {
            for (const auto &student : department.second)
            {
                if (student->getFullName() == fullName)
                {
                    return student;
                }
            }
        }
        return nullptr;
    }

    // Implement other necessary methods for department management
};

int main()
{
    Department university;

    // Input students for each department
    // university.inputStudents();

    // Output students in each department
    // university.outputStudents();

    // Add a new student to a department
    // university.addStudentToDepartment();

    // Output students in each department after adding a new student
    // cout << "After adding a new student:" << endl;
    // university.outputStudents();
    university.addStudent("Computer Science", new Person("001", "Alice", "01/01/2000", 2020, 9.0, false, ""));
    university.addStudent("Computer Science", new Person("002", "Bob", "02/02/2001", 2021, 8.5, true, "Location A"));
    university.addStudent("Computer Science", new Person("002", "Bob", "02/02/2001", 2021, 9, true, ""));
    university.addStudent("Computer Science", new Person("002", "Bob", "02/02/2001", 2021, 6, true, "Location B"));
    university.addStudent("Electrical Engineering", new Person("003", "Charlie", "03/03/2002", 2019, 8.7, true, ""));
    university.addStudent("Electrical Engineering", new Person("004", "David", "04/04/2003", 2020, 9.2, true, "Location B"));
    university.outputStudents();
    cout << "so sinh vien có diem trung binh co nhat " << endl;
    university.outputEndyear();

    cout << "áhdkajdkasdkashdashdlasdlhsadhaskdhasdjasdjgasdjasjd" << endl;
    university.countStudentsByYear();

    return 0;
}
