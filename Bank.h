#pragma once
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<typeinfo>
#include <iomanip>
template<typename Type>
class List //лист
{
public:

    class Node //узел
    {
    public:
        Type data; //данные
        Node* prev; //указатель на предыдущий элемент
        Node* next; //указатель на следующий элемент
        Node() = default;
        Node(const Type& temp_data, Node* temp_prev = nullptr, Node* temp_next = nullptr) : data(temp_data), prev(temp_prev), next(temp_next) {}
        Node(const Node& node) : data(node.data), prev(nullptr), next(nullptr) {}
        ~Node() = default;
    };

private:
    size_t size; //количество узлов в листе
    Node* head; //указатель на голову
    Node* tail; //указатель на хвост
public:
    List() : size(0), head(nullptr), tail(nullptr) {}
    List(const List<Type>&);
    ~List();
    void push_back(const Type&); //добавление элемента в конец списка
    void push_front(const Type&); //добавление элемента в начало списка
    Type pop_back(); //удаление элемента в конце спика
    Type pop_front(); //удаление элемента в начале списка
    void insert(const Type&, size_t); //вставка элемента на позицию
    void insert(const Type&, size_t, size_t); //вставка нескольких элементов на позицию
    void replace(Type&, const Type&); //замена элемента по поиску
    void replace(size_t, const Type&); //замена элемента по индексу
    Type erase(size_t); //удаление элемента по индексу
    Type& operator[](size_t);
    const Type& operator[](size_t) const;

    class Iterator
    {
    private:
        Node* ptr;
    public:
        Iterator() = default;
        Iterator(Node* temp_ptr) : ptr(temp_ptr) {}
        ~Iterator() = default;
        Iterator& operator++(); //префиксна€ форма инкремента
        Iterator& operator++(int); //постфиксна€ форма инкремента
        Iterator& operator--(); //префиксна€ форма декремента
        Iterator& operator--(int); //постфиксна€ форма декремента
        Iterator& operator+(int); //переход на позицию +int
        Iterator& operator-(int); //переход на позицию -int
        Type& operator*() const { return ptr->data; } //разыменование
        Iterator* operator->();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
    };

    void find(const Type&);
    void erase(Iterator, Iterator);
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(tail->next); }

    friend std::ifstream& operator>>(std::ifstream& in, List<Type>& list) //перезагрузка >> 
    {
        if (!in)
        {
            std::cout << "File error!\n";
            return in;
        }

        while (!in.eof())
        {
            Type data;
            in >> data;
            list.push_back(data);
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, List<Type>& list) //перегрузка << дл€ вывода листа на конколь
    {
        std::cout << "List has form:\n";

        if (list.size == 0)
        {
            out << "List is empty!\n";
            return out;
        }

        for (auto i = list.begin(); i != list.end(); i++)
        {
            out << " " << *i;
        }

        std::cout << "\n";
        return out;
    }

    friend std::ofstream& operator<<(std::ofstream& out, List<Type>& list) //перегрузка << дл€ сохранени€ листа в файл
    {
        if (list.size == 0)
        {
            out << "List is empty!\n";
            return out;
        }

        for (auto i = list.begin(); i != list.end(); i++)
        {
            out << *i;
        }

        std::cout << "\n";
        return out;
    }
};

class Acc
{
public:
    std::string number;
    std::string code;
    std::string surname;
    double amount;
    size_t day;
    size_t month;
    size_t year;
    size_t rate;

    Acc() = default;
    Acc(std::string _number) : number(_number), code("nocode"), surname("noname"), amount(0), day(0), month(0), year(0), rate(0) {} //конструктор дл€ поиска по номеру
    Acc(size_t _day, size_t _month, size_t _year) :number("nonumber"), code("nocode"), surname("noname"), amount(0), day(_day), month(_month), year(_year), rate(0) {} //конструктор дл€ поиска по дате

    Acc& operator=(std::string _fio) //дл€ поиска по фамилии
    {
        surname = _fio;
        return *this;
    }

    Acc(std::string _number, std::string _code, std::string _surname, unsigned long long _amount, size_t _day, size_t _month, size_t _year, size_t _rate)
    {
        number = _number;
        code = _code;
        surname = _surname;
        amount = _amount;
        day = _day;
        month = _month;
        year = _year;
        rate = _rate;
    }

    Acc(const Acc& acc)
    {
        number = acc.number;
        code = acc.code;
        surname = acc.surname;
        amount = acc.amount;
        day = acc.day;
        month = acc.month;
        year = acc.year;
        rate = acc.rate;
    }

    ~Acc() = default;

    friend std::ifstream& operator>>(std::ifstream& in, Acc& acc) //перегрузка >> дл€ записи в лист из файла
    {
        in >> acc.number >> acc.code >> acc.surname >> acc.amount >> acc.day >> acc.month >> acc.year >> acc.rate;
        return in;
    }

    friend std::istream& operator>>(std::istream& in, Acc& acc) //перегрузка >> дл€ заполнени€ элемента с консоли
    {
        bool flag = false;
        std::string number = "BY02AKBB36", temp;
        size_t code;

        while (true)
        {
            std::cout << "\nEnter number (BY02AKBB36 XXXXX): ";
            std::cin >> acc.number;

            if (acc.number.length() == 5)
            {
                acc.number = number + acc.number;
                break;
            }

            std::cout << "Error number!\n";
        }

        while (true)
        {
            std::cout << "\nCode:\n1. BY\n2. RU\n3. USD\n4. EUR\n\nEnter code: ";
            std::cin >> code;

            switch (code)
            {
            case 1:
            {
                acc.code = "BY";
                acc.rate = 10;
                flag = true;
                break;
            }
            case 2:
            {
                acc.code = "RU";
                acc.rate = 8;
                flag = true;
                break;
            }
            case 3:
            {
                acc.code = "USD";
                acc.rate = 4;
                flag = true;
                break;
            }
            case 4:
            {
                acc.code = "EUR";
                acc.rate = 2;
                flag = true;
                break;
            }
            default:
            {
                std::cout << "Error code!\n";
            }
            }

            if (flag)
            {
                break;
            }
        }

        std::cout << "\nEnter surname: ";
        std::cin >> acc.surname;

        while (true)
        {
            std::cout << "\nEnter amount: ";
            std::cin >> acc.amount;
            acc.amount = round(acc.amount * 100) / 100;

            if (acc.amount > 0)
            {
                break;
            }

            std::cout << "Error amount!\n";
        }

        while (true)
        {
            std::cout << "\nEnter day: ";
            std::cin >> acc.day;
            std::cout << "Enter month: ";
            std::cin >> acc.month;
            std::cout << "Enter year: ";
            std::cin >> acc.year;

            if (acc.check_date(acc))
            {
                break;
            }

            std::cout << "Error data!\n";
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, Acc& acc) //перегрузка << дл€ вывода данных узла на консоль
    {
        out << std::left << std::setw(18) << acc.number << std::setw(6) << acc.code << std::setw(12) << acc.surname << std::setw(15) << std::fixed << std::setprecision(2) << acc.amount << std::setw(3) << acc.day << std::setw(3) << acc.month << std::setw(7) << acc.year << std::setw(5) << acc.rate << "\n";
        return out;
    }

    friend std::ofstream& operator<<(std::ofstream& out, Acc& acc) //перегрузка << дл€ записи узла в файл
    {
        out << acc.number << " " << acc.code << " " << acc.surname << " " << acc.amount << " " << acc.day << " " << acc.month << " " << acc.year << " " << acc.rate << "\n";
        return out;
    }

    bool operator==(const Acc& acc)const
    {
        return  acc.number == number || acc.surname == surname || (acc.day == day && acc.month == month && acc.year == year) ? true : false;
    }

    bool operator!=(const Acc& acc) const
    {
        return (number != acc.number || code != acc.code || surname != acc.surname || amount != acc.amount || day != acc.day || month != acc.month || year != acc.year || rate != acc.rate) ? true : false;
    }

    bool check_date(const Acc& acc) //метод дл€ проверки корректности введенной даты
    {
        size_t days_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

        if ((acc.year < 1900) || (acc.year > 2100))
        {
            return false;
        }

        if (acc.year % 4 == 0) //если год высокосный
        {
            days_month[2] = 29;
        }

        if ((acc.month < 1) || (acc.month > 12))
        {
            return false;
        }

        if ((acc.day < 1) || (acc.day > days_month[acc.month]))
        {
            return false;
        }

        return true;
    }
};

template<typename Type>
void menu(List<Type>&);

