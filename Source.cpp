#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;

enum Speciality { CS, INF, ME, PI, TN };
string specialityStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    string surname;
    unsigned course;
    Speciality speciality;
    int physics;
    int math;
    union {
        int programming;
        int numericalMethods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
int GetSubjectGrade(Student& s);


int main() {
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);
    PrintIndexSorted(s, IndexSort(s, N), N);

    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get(); // ������� ����� ��������� � �� ����������� �������
        cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

        cout << " �������: "; getline(cin, s[i].surname);
        cout << " ����: "; cin >> s[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> speciality;
        s[i].speciality = (Speciality)speciality;
        cout << " ������ � ������: "; cin >> s[i].physics;
        cout << " ������ � ����������: "; cin >> s[i].math;
        switch (s[i].speciality) {
        case CS:
            cout << " ������ � �������������: "; cin >> s[i].programming;
            break;
        case INF:
            cout << " ������ � ��������� ������: "; cin >> s[i].numericalMethods;
            break;
        case ME:
        case PI:
        case TN:
            cout << " ������ � ���������: "; cin >> s[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "�" << " |" << setw(15) << "�������" << " |" << setw(6) << "����" << " |" << setw(25) << "������������" << " |" << setw(8) << "Գ����" << " |" << setw(13) << "����������" << " |" << setw(15) << "�������������" << " |" << setw(15) << "������� ������" << " |" << setw(10) << "���������" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[i].surname
            << "| " << setw(5) << s[i].course << " "
            << "| " << setw(25) << specialityStr[s[i].speciality]
            << "| " << setw(8) << s[i].physics
            << "| " << setw(12) << s[i].math << " ";
        switch (s[i].speciality) {
        case CS:
            cout << "| " << setw(15) << s[i].programming
                << "| " << setw(15) << " "
                << "| " << setw(15) << " " << endl;
            break;
        case INF:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].numericalMethods
                << "| " << setw(15) << " " << endl;
            break;
        case ME:
        case PI:
        case TN:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "====================================================================================================" << endl;
    cout << endl;


}

int* IndexSort(Student* s, const int N) {
    int* I = new int[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        I[i] = i; // ��������� ���� ����������� ������

    // �������� ��������� ����� �������
    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;

        // ��������� �� ������� �����, ������� ����� �� ��������
        while (j >= 0 && (
            s[I[j]].course > s[value].course ||
            (s[I[j]].course == s[value].course &&
                s[I[j]].physics + s[I[j]].math + GetSubjectGrade(s[I[j]]) > s[value].physics + s[value].math + GetSubjectGrade(s[value]) ||
                (s[I[j]].course == s[value].course &&
                    s[I[j]].physics + s[I[j]].math + GetSubjectGrade(s[I[j]]) == s[value].physics + s[value].math + GetSubjectGrade(s[value]) &&
                    s[I[j]].surname > s[value].surname)
                ))) {
            I[j + 1] = I[j];
            j--;
        }

        I[j + 1] = value;
    }

    return I;
}

int GetSubjectGrade(Student& s) {
    switch (s.speciality) {
    case CS:
        return s.programming;
    case INF:
        return s.numericalMethods;
    case ME:
    case PI:
    case TN:
        return s.pedagogy;
    default:
        return 0;
    }
}

void PrintIndexSorted(Student* s, int* I, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "�" << " |" << setw(15) << "�������" << " |" << setw(6) << "����" << " |" << setw(25) << "������������" << " |" << setw(8) << "Գ����" << " |" << setw(13) << "����������" << " |" << setw(15) << "�������������" << " |" << setw(15) << "������� ������" << " |" << setw(10) << "���������" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[I[i]].surname
            << "| " << setw(5) << s[I[i]].course << " "
            << "| " << setw(25) << specialityStr[s[I[i]].speciality]
            << "| " << setw(8) << s[I[i]].physics
            << "| " << setw(12) << s[I[i]].math << " ";
        switch (s[i].speciality) {
        case CS:
            cout << "| " << setw(15) << s[I[i]].programming
                << "| " << setw(15) << " "
                << "| " << setw(15) << " " << endl;
            break;
        case INF:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << s[I[i]].numericalMethods
                << "| " << setw(15) << " " << endl;
            break;
        case ME:
        case PI:
        case TN:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << " "
                << "| " << setw(15) << s[I[i]].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "====================================================================================================" << endl;
    cout << endl;
    cout << "====================================================================================================" << endl;
    cout << endl;
}