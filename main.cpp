#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits>

using namespace std;

struct Node {
  int znach;
  Node *next;
};

struct List {
  Node *first;
  Node *last;
};

void input(List &list, int znach) {
  Node *curr = new Node{znach, nullptr};
  if (list.first == nullptr)
    list.first = curr;
  else {
    if (list.first->next == nullptr) list.first->next = curr;
    if (list.last != nullptr) list.last->next = curr;
    list.last = curr;
  }
}

void print_list(Node *&curr) {
  do {
    if (curr->next != nullptr)
      cout << curr->znach << " -> ";
    else
      cout << curr->znach << endl;
    curr = curr->next;
  } while (curr != nullptr);
}

void menu() {
  cout << "Выберите одну из операций:" << endl;
  cout << "1. Распечатать список" << endl;
  cout << "2. Добавить элементы в список" << endl;
  cout << "3. Удалить элемент" << endl;
  cout << "4. Найти позиции элементов" << endl;
  cout << "5. Заменить элемент на другой" << endl;
  cout << "6. Отсортировать элементы списка" << endl;
  cout << "7. Завершить работу программы" << endl;
}

void addition_elements(List &list) {
  cout << "Введите новые элементы" << endl;
  string new_elements;
  int znach = 0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, new_elements);
  for (int i = 0; i < new_elements.length(); i++) {
    if (new_elements[i] != ' ')
      znach = znach * 10 + new_elements[i] - 48;
    else {
      input(list, znach);
      znach = 0;
    }
    if (i == new_elements.length() - 1) input(list, znach);
  }
}

void delete_element(List &list) {
  cout << "Введите удаляемый элемент" << endl;
  int deleting_element = 0;
  cin >> deleting_element;
  bool element_availability = false;
  Node *curr = list.first;
  Node *previous = nullptr;
  if (curr->znach == deleting_element) {
    if ((curr == (list.first)) && (list.first != list.last)) {
      list.first = list.first->next;
      delete curr;
      element_availability = true;
    } else {
      if ((curr == list.first) && (list.first == list.last)) {
        list.first = nullptr;
        list.last = list.first;
        delete curr;
        element_availability = true;
      }
    }
  }
  previous = curr;
  curr = curr->next;
  while (curr != nullptr) {
    if ((curr->znach == deleting_element) && (curr != list.last)) {
      previous->next = curr->next;
      delete curr;
      element_availability = true;
    } else {
      if ((curr->znach == deleting_element) && (curr == list.last)) {
        list.last = previous;
        list.last->next = nullptr;
        delete curr;
        element_availability = true;
      }
    }
    previous = curr;
    curr = curr->next;
  }
  if (element_availability == false)
    cout << "Указанный элемент отсутствует" << endl;
}

void find_pozitions(List &list) {
  cout << "Введите элемент, позицию которого вы хотите узнать:" << endl;
  int finding_element = 0;
  cin >> finding_element;
  int pozitions = 0;
  bool element_availability = false;
  Node *curr = list.first;
  while (curr != nullptr) {
    if (curr->znach == finding_element) {
      cout << pozitions << " ";
      pozitions++;
      element_availability = true;
    } else
      pozitions++;
    curr = curr->next;
  }
  if (element_availability == false) cout << "Элемент не найден" << endl;
}

void replace_element(List &list) {
  cout << "Введите позицию и новое значение:" << endl;
  int pozition = 0, new_element, i = 0;
  cin >> pozition >> new_element;
  bool element_availability = false;
  Node *curr = list.first;
  while (curr != nullptr) {
    if (i == pozition) {
      curr->znach = new_element;
      element_availability = true;
    }
    curr = curr->next;
    i++;
  }
  if (element_availability == false)
    cout << "Элемент с данной позицией не существует";
}

void sort_elements(List &list) {
  Node *curr = list.first;
  int n = 0;
  while (curr != nullptr) {
    n++;
    curr = curr->next;
  }
  curr = list.first;
  int a[n];
  for (int i = 0; i < n; i++) {
    a[i] = curr->znach;
    curr = curr->next;
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        int repl = a[j];
        a[j] = a[j + 1];
        a[j + 1] = repl;
      }
    }
  }
  curr = list.first;
  for (int i = 0; i < n; i++) {
    curr->znach = a[i];
    curr = curr->next;
  }
}

int main(int argc, char *argv[]) {
  int znach;
  List list;
  list.first = nullptr;
  list.last = nullptr;
  Node *curr = nullptr;
  if (argc == 1) cout << "Список пуст!" << endl;
  if (argc > 1) {
    if (argc == 2) {
      for (int i = 0; i < strlen(argv[1]); i++) {
        if ((argv[1][i] >= '0') && (argv[1][i] <= '9'))
          znach = znach * 10 + argv[1][i] - 48;
        else {
          if (argv[1][i] == ',') {
            input(list, znach);
            znach = 0;
          }
        }
        if (i == strlen(argv[1]) - 1) input(list, znach);
      }
    } else {
      for (int i = 0; i < argc - 1; i++) {
        znach = atoi(argv[i + 1]);
        input(list, znach);
      }
    }
    menu();
    while (true) {
      int choice;
      cin >> choice;
      switch (choice) {
        case 1:
          curr = list.first;
          if (curr != nullptr)
            print_list(curr);
          else
            cout << "Список пуст!" << endl;
          menu();
          break;
        case 2:
          addition_elements(list);
          menu();
          break;
        case 3:
          delete_element(list);
          menu();
          break;
        case 4:
          find_pozitions(list);
          menu();
          break;
        case 5:
          replace_element(list);
          menu();
          break;
        case 6:
          sort_elements(list);
          menu();
          break;
        case 7:
          cout << "Вы действительно хотите выйти из программы?(yes/no)" << endl;
          string answer;
          cin >> answer;
          if (answer == "y" || answer == "yes" || answer == "Yes" ||
              answer == "Y" || answer == "YES")
            return 0;
          else if (answer == "n" || answer == "no" || answer == "No" ||
                   answer == "N" || answer == "NO")
            menu();
          break;
      }
    }
  }
}
