#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream> 

using namespace std;

enum class StudyField {
    MECHANICAL_ENGINEERING = 1,
    SOFTWARE_ENGINEERING = 2,
    FOOD_TECHNOLOGY = 3,
    URBANISM_ARCHITECTURE = 4,
    VETERINARY_MEDICINE = 5
};

class Student {
private:
    string firstName;
    string lastName;
    string email;
    string enrollmentDate;
    string dateOfBirth;

public:
    Student(string first_name, string last_name, string email, string enrollment_date, string date_of_birth)
        : firstName(first_name), lastName(last_name), email(email), enrollmentDate(enrollment_date), dateOfBirth(date_of_birth) {}

    string getEmail() const {
        return email;
    }
};

class Faculty {
private:
    string name;
    string abbreviation;
    vector<Student> students;
    StudyField studyField;

public:
    Faculty(string name, string abbreviation, StudyField study_field)
        : name(name), abbreviation(abbreviation), studyField(study_field) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    string getName() const {
        return name;
    }

    vector<Student> getStudents() const {
        return students;
    }

    StudyField getStudyField() const {
        return studyField;
    }
};

class University {
private:
    vector<Faculty> faculties;

public:
    void createFaculty(string name, string abbreviation, StudyField study_field) {
        Faculty faculty(name, abbreviation, study_field);
        faculties.push_back(faculty);
    }

    bool assignStudentToFaculty(const string& student_email, const string& faculty_name) {
        for (auto& faculty : faculties) {
            if (faculty.getName() == faculty_name) {
                Student student(student_email, "", "", "", ""); 
                faculty.addStudent(student);
                return true;
            }
        }
        return false;
    }

    string searchFacultyByStudentEmail(const string& student_email) {
        for (const auto& faculty : faculties) {
            for (const auto& student : faculty.getStudents()) {
                if (student.getEmail() == student_email) {
                    return faculty.getName();
                }
            }
        }
        return "Student not found";
    }

    void displayUniversityFaculties() {
        for (const auto& faculty : faculties) {
            cout << faculty.getName() << endl;
        }
    }

    void displayAllFacultiesByField(StudyField study_field) {
        for (const auto& faculty : faculties) {
            if (faculty.getStudyField() == study_field) {
                cout << faculty.getName() << endl;
            }
        }
    }

    void saveState(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& faculty : faculties) {
                file << faculty.getName() << "," << static_cast<int>(faculty.getStudyField()) << ",";
                for (const auto& student : faculty.getStudents()) {
                    file << student.getEmail() << ",";
                }
                file << endl;
            }
            file.close();
            cout << "State saved successfully." << endl;
        } else {
            cerr << "Unable to open file." << endl;
        }
    }

    void loadState(const string& filename) {
        faculties.clear(); 
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string facultyName, studentEmail;
                int studyFieldInt;
                iss >> facultyName >> studyFieldInt;
                StudyField studyField = static_cast<StudyField>(studyFieldInt);
                createFaculty(facultyName, "", studyField);
                while (getline(iss, studentEmail, ',')) {
                    if (!studentEmail.empty()) 
                        assignStudentToFaculty(studentEmail, facultyName);
                }
            }
            file.close();
            cout << "State loaded successfully." << endl;
        } else {
            cerr << "Unable to open file." << endl;
        }
    }
};

int main() {
    University tumUniversity;

    while (true) {
        cout << "\n1. Create a new faculty" << endl;
        cout << "2. Create and assign a student to a faculty" << endl;
        cout << "3. Search what faculty a student belongs to by email" << endl;
        cout << "4. Display University faculties" << endl;
        cout << "5. Display all faculties belonging to a field" << endl;
        cout << "6. Save state" << endl;
        cout << "7. Load state" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, abbreviation;
                int studyFieldInt;
                cout << "Enter faculty name: ";
                cin >> name;
                cout << "Enter faculty abbreviation: ";
                cin >> abbreviation;
                cout << "Enter study field (1 - MECHANICAL_ENGINEERING, 2 - SOFTWARE_ENGINEERING, 3 - FOOD_TECHNOLOGY, 4 - URBANISM_ARCHITECTURE, 5 - VETERINARY_MEDICINE): ";
                cin >> studyFieldInt;
                StudyField studyField = static_cast<StudyField>(studyFieldInt);
                tumUniversity.createFaculty(name, abbreviation, studyField);
                break;
            }
            case 2: {
                string studentEmail, facultyName;
                cout << "Enter student email: ";
                cin >> studentEm
