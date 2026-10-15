#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct student {
    string name;
    string group;
    vector<int> marks;
};

struct group {
    string name;
};

//добавление группы
void add_group(vector<group>& groups, string name) {
    group new_g;
    new_g.name = name;
    groups.push_back(new_g);
}

//удаление группы
void delete_group(vector<group>& groups, vector<student>& students, string name) {
    int s_size = students.size();
    for (int i = 0; i < s_size; i++) {
        if (students[i].group == name) {
            cout << "Ошибка! В группе есть студенты, удалить нельзя!" << endl;
            return;
        }
    }
    //если пустая группа. то удаляем
    int g_size = groups.size();
    for (int i = 0; i < g_size; i++) {
        if (groups[i].name == name) {
            groups.erase(groups.begin() + i);
            cout << "Группа успешно удалена" << endl;
            return;
        }
    }
    cout << "Группа не найдена!" << endl;
}

//изменение группы
void edit_group(vector<group>& groups, vector<student>& students, string old_name) {
    string new_name;
    int g_size = groups.size();
    for (int i = 0; i < g_size; i++) {
        if (groups[i].name == old_name) {
            cout << "Введи новое название группы: ";
            cin >> new_name;
            groups[i].name = new_name;
            //меняем группу у всех студентов которые в ней были 
            int s_size = students.size();
            for (int j = 0; j < s_size; j++) {
                if (students[j].group == old_name) {
                    students[j].group = new_name;
                }
            }
            cout << "Название изменено" << endl;
            return;
        }
    }
    cout << "Группа не найдена!" << endl;
}

//добавление студента
void add_student(vector<student>& students, string name, string group) {
    student new_s;
    new_s.name = name;
    new_s.group = group;
    students.push_back(new_s);
}

//удаление студента
void delete_student(vector<student>& students, string name) {
    int s_size = students.size();
    for (int i = 0; i < s_size; i++) {
        if (students[i].name == name) {
            students.erase(students.begin() + i);
            cout << "Студент успешно удален" << endl;
            return;
        }
    }
    cout << "Студент не найден!" << endl;
}

//изменение студента
void edit_student(vector<student>& students, string name) {
    int s_size = students.size();
    for (int i = 0; i < s_size; i++) {
        if (students[i].name == name) {
            cout << "Введи новое ФИО: ";
            cin.ignore();
            getline(cin, students[i].name);
            cout << "Введи новую группу для него: ";
            getline(cin, students[i].group);
            cout << "Данные студента изменены" << endl;
            return;
        }
    }
    cout << "Студент не найден!" << endl;
}
//вывод студентов
void print_students(vector<student>& students) {
    cout << "\nСписок студентов" << endl;

    if (students.empty()) {
        cout << "Студентов пока нет!" << endl;
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << ". ФИО: " << students[i].name
            << " | Группа: " << students[i].group << endl;
    }
}

//вывод групп
void print_groups(vector<group>& groups) {
    cout << "\nСписок групп" << endl;

    if (groups.empty()) {
        cout << "Групп пока нет!" << endl;
        return;
    }

    for (int i = 0; i < groups.size(); i++) {
        cout << i + 1 << ". " << groups[i].name << endl;
    }
}

//добавление оценки
void add_mark(vector<student>& students, string name, int mark) {
    int s_size = students.size();
    for (int i = 0; i < s_size; i++) {
        if (students[i].name == name) {
            students[i].marks.push_back(mark);
            cout << "Оценка успешно добавлена" << endl;
            return;
        }
    }
    cout << "Студент не найден!" << endl;
}

//средний балл
void print_averages(vector<student>& students, string group_name) {
    cout << "\nСредний балл по группе " << group_name << ":" << endl;
    double group_sum = 0.0;
    int group_total_marks = 0;
    int s_size = students.size();

    for (int i = 0; i < s_size; i++) {
        if (students[i].group == group_name) {
            double student_sum = 0.0;
            int m_size = students[i].marks.size();
            if (m_size > 0) {
                for (int j = 0; j < m_size; j++) {
                    student_sum += students[i].marks[j];
                    group_sum += students[i].marks[j];
                    group_total_marks++;
                }
                cout << "Студент " << students[i].name << ": " << student_sum / m_size << endl;
            }
            else {
                cout << "Студент " << students[i].name << ": Оценок нет" << endl;
            }
        }
    }

    if (group_total_marks > 0) {
        cout << "Общий средний балл всей группы: " << group_sum / group_total_marks << endl;
    }
    else {
        cout << "В этой группе пока никто не получил оценок." << endl;
    }
}

//статистика группы
void print_stats(vector<student>& students, string group_name) {
    int otlichniki = 0;
    int horoshisti = 0;
    int s_size = students.size();

    for (int i = 0; i < s_size; i++) {
        if (students[i].group == group_name) {
            int m_size = students[i].marks.size();
            if (m_size == 0) continue;

            bool has_troika_or_dvoika = false;
            bool has_chetverka = false;

            for (int j = 0; j < m_size; j++) {
                if (students[i].marks[j] <= 3) {
                    has_troika_or_dvoika = true;
                }
                if (students[i].marks[j] == 4) {
                    has_chetverka = true;
                }
            }

            if (has_troika_or_dvoika == false) {
                if (has_chetverka == true) {
                    horoshisti++;
                }
                else {
                    otlichniki++;
                }
            }
        }
    }

    cout << "\nСтатистика группы " << group_name << ":" << endl;
    cout << "Отличников: " << otlichniki << endl;
    cout << "Хорошистов: " << horoshisti << endl;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<student> students;
    vector<group> groups;

    //группы и студенты 
    group g1; g1.name = "БД-1-25"; groups.push_back(g1);
    group g2; g2.name = "П-2-24"; groups.push_back(g2);

    student s1; s1.name = "Васильцов Г.Е"; s1.group = "БД-1-25"; s1.marks.push_back(5); s1.marks.push_back(5); students.push_back(s1);
    student s2; s2.name = "Мурзагалиев Т.А"; s2.group = "БД-1-25"; s2.marks.push_back(4); s2.marks.push_back(5); students.push_back(s2);
    student s3; s3.name = "Литвин М.А"; s3.group = "П-2-24"; s3.marks.push_back(5); s3.marks.push_back(5); students.push_back(s3);
    student s4; s4.name = "Смирнов В.О"; s4.group = "П-2-24"; s4.marks.push_back(4); s4.marks.push_back(5); students.push_back(s4);

    int choice = -1;
    int action = 0;
    string s_name, g_name;
    int mark = 0;


    while (choice != 0) {
        cout << "\nМеню:" << endl;
        cout << "1. Студенты (добавить/удалить/измениь)" << endl;
        cout << "2. Группы (добавить/удалить/изменить)" << endl;
        cout << "3. Поставить оценку" << endl;
        cout << "4. Средний балл" << endl;
        cout << "5. Статистика группы" << endl;
        cout << "6. Список студентов" << endl;
        cout << "7. Список групп" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "1. Добавить студента\n2. Удалить студента\n3. Изменить студента\nВыбор: ";
            cin >> action;

            if (action == 1) {
                cout << "ФИО нового студента: ";
                cin.ignore();
                getline(cin, s_name);
                cout << "Имя группы для него: ";
                getline(cin, g_name);
                add_student(students, s_name, g_name);
            }
            else if (action == 2) {
                cout << "ФИО студента для удаления: ";
                cin.ignore();
                getline(cin, s_name);
                delete_student(students, s_name);
            }
            else if (action == 3) {
                cout << "ФИО студента для изменения: ";
                cin.ignore();
                getline(cin, s_name);
                edit_student(students, s_name);
            }
            break;
        case 2:
            cout << "1. Добавить группу\n2. Удалить группу\n3. Изменить группу\nВыбор: ";
            cin >> action;

            if (action == 1) {
                cout << "Имя новой группы: ";
                cin.ignore();
                getline(cin, g_name);
                add_group(groups, g_name);
            }
            else if (action == 2) {
                cout << "Какую группу удалить: ";
                cin.ignore();
                getline(cin, g_name);
                delete_group(groups, students, g_name);
            }
            else if (action == 3) {
                cout << "Какую группу изменить: ";
                cin.ignore();
                getline(cin, g_name);
                edit_group(groups, students, g_name);
            }
            break;

        case 3:
            cout << "ФИО студента: ";
            cin.ignore();
            getline(cin, s_name);
            cout << "Введите оценку (целое число): ";
            cin >> mark;
            add_mark(students, s_name, mark);
            break;

        case 4:
            //средний балл стужентов группы
            cout << "Введите название группы: ";
            cin.ignore();
            getline(cin, g_name);
            print_averages(students, g_name);
            break;

        case 5:
            //статистика группы
            cout << "Введите название группы: ";
            cin.ignore();
            getline(cin, g_name);
            print_stats(students, g_name);
            break;

        case 6:
            print_students(students);
            break;

        case 7:
            print_groups(groups);
            break;


        case 0:
            cout << "Работа программы завершена." << endl;
            break;

        default:
            cout << "Неверный пункт меню!" << endl;
            break;
        }
    }

    return 0;
}