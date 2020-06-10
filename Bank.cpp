#include "Bank.h"

template <typename Type>
List<Type>::List(const List<Type>& list)
{
    head = tail = nullptr;
    size = 0;
    Node* pos = list.head;

    while (pos != nullptr)
    {
        push_back(pos->data);
        pos = pos->next;
    }
}

template <typename Type>
List<Type>:: ~List()
{
    while (size != 0)
    {
        pop_back();
    }
}

template <typename Type>
void List<Type>::push_back(const Type& temp_data)
{
    Node* temp = new Node(temp_data, tail, nullptr);

    if (size == 0)
    {
        head = temp;
    }
    else
    {
        tail->next = temp;
    }

    tail = temp;
    size++;
}

template <typename Type>
void List<Type>::push_front(const Type& temp_data)
{
    Node* temp = new Node(temp_data, nullptr, head);

    if (size == 0)
    {
        tail = temp;
    }
    else
    {
        head->prev = temp;
    }

    head = temp;
    size++;
}

template<typename Type>
Type List<Type>::pop_back()
{
    Node* temp = tail;
    Type value;

    if (size == 0)
    {
        std::cout << "List is empty!\n";
        return Type();
    }

    if (size == 1)
    {
        tail = head = nullptr;
    }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }

    value = temp->data;
    delete temp;
    size--;
    return value;
}

template<typename Type>
Type List<Type>::pop_front()
{
    Node* temp = head;
    Type value;

    if (size == 0)
    {
        std::cout << "List is empty!\n";
        return Type();
    }

    if (size == 1)
    {
        tail = head = nullptr;
    }
    else
    {
        head = head->next;
        head->prev = nullptr;
    }

    value = temp->data;
    delete temp;
    size--;
    return value;
}

template<typename Type>
void List<Type>::insert(const Type& temp_data, size_t index)
{
    if (index > size)
    {
        std::cout << "Error index! Insert cannot be done!\n";
        return;
    }

    if (index == 0)
    {
        push_front(temp_data);
        return;
    }

    if (index == size)
    {
        push_back(temp_data);
        return;
    }

    Node* pos = head;
    size_t count = 0;

    while (count != index) //поиск нужной позиции
    {
        pos = pos->next;
        count++;
    }

    Node* temp = new Node(temp_data, pos->prev, pos);
    (pos->prev)->next = temp;
    pos->prev = temp;
    size++;
}

template<typename Type>
void List<Type>::insert(const Type& temp_data, size_t index, size_t count)
{
    while (count != 0)
    {
        insert(temp_data, index);
        count--;
    }
}

template<typename Type>
void List<Type>::replace(Type& temp_data, const Type& new_data)
{
    if (size == 0)
    {
        std::cout << "List is empty!\n";
        return;
    }

    Node* pos = head;

    while (pos != nullptr)
    {
        if (pos->data == temp_data)
        {
            pos->data = new_data;
            return;
        }

        pos = pos->next;
    }

    std::cout << "Error! No such data in list!\n";
}

template<typename Type>
void List<Type>::replace(size_t index, const Type& new_data)
{
    if (size == 0)
    {
        std::cout << "List is empty!\n";
        return;
    }

    if (index > size)
    {
        std::cout << "Error index! Replace cannot be done!\n";
        return;
    }

    erase(index);
    insert(new_data, index);
}

template<typename Type>
Type& List<Type>:: operator[](size_t index)
{
    if (index >= size)
    {
        std::cout << "Wrong index!\n";
        Type();
    }

    Node* pos = head;
    size_t count = 0;

    while (count < index)
    {
        pos = pos->next;
        count++;
    }

    return pos->data;
}

template<typename Type>
const Type& List<Type>:: operator[](size_t index) const
{
    if (index >= size)
    {
        std::cout << "Wrong index!\n";
        Type();
    }

    Node* pos = head;
    size_t count = 0;

    while (count < index)
    {
        pos = pos->next;
        count++;
    }

    return pos->data;
}

template<typename Type>
Type List<Type>::erase(size_t index)
{
    if (index >= size)
    {
        std::cout << "Wrong index!\n";
        return Type();
    }

    if (index == 0)
    {
        return pop_front();
    }

    if (index == size - 1)
    {
        return pop_back();
    }

    Node* pos = head;
    size_t count = 0;

    while (count < index)
    {
        pos = pos->next;
        count++;
    }

    Type temp = pos->data;
    (pos->prev)->next = pos->next;
    (pos->next)->prev = pos->prev;
    delete pos;
    size--;
    return temp;
}

template <typename Type>
void List<Type>::erase(Iterator start, Iterator finish)
{
    if (start == nullptr)
    {
        std::cout << "Wrong index!\n";
        return;
    }

    size_t index = 0;
    Iterator cur = head;

    while (cur != start) //находим начальный элемент, подлежащий удалению
    {
        cur++;
        index++;
    }

    if (start == finish) //если нужно удалить только один элемент
    {
        erase(index);
        return;
    }

    ++finish; //чтобы удалить finish включительно

    while (cur != finish && cur != nullptr) //удаляем пока не finish или конец списка
    {
        ++cur;
        erase(index);
    }
}

template <typename Type>
void List<Type>::find(const Type& element)
{
    List<Type> temp_list;
    Node* cur = head;
    size_t count = 0;

    while (cur != nullptr)
    {
        if (cur->data == element)
        {
            temp_list.push_front(cur->data);
            count++;
        }

        cur = cur->next;
    }

    if (count == 0)
    {
        std::cout << "Error! No data on such accounts\n";
        return;
    }

    std::cout << temp_list;
    std::cout << "Save data to file?\n1. Yes\n2. No\n\nEnter number: ";
    size_t save;
    std::string name;
    std::cin >> save;

    if (save == 1)
    {
        while (true)
        {
            std::cout << "Enter name file: ";
            std::cin >> name;

            if (name.length() != 0)
            {
                name += ".txt";
                break;
            }

            std::cout << "Error name file!\n";
        }

        std::ofstream out(name);
        out << temp_list;
        std::cout << "Save completed in file " << name << "\n";
        out.close();
    }
}

template <typename Type>
bool List<Type>::Iterator:: operator==(const List<Type>::Iterator& temp) const
{
    return ptr == temp.ptr;
}

template <typename Type>
bool List<Type>::Iterator:: operator!=(const List<Type>::Iterator& temp) const
{
    return ptr != temp.ptr;
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator++()
{
    if (ptr == nullptr)
    {
        return *this;
    }

    ptr = ptr->next;
    return *this;
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator++(int)
{
    operator++();
    return *(this - 1);
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator--()
{
    if (ptr == nullptr)
    {
        return *this;
    }

    ptr = ptr->prev;
    return *this;
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator--(int)
{
    operator--();
    return *(this + 1);
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator+(int count)
{
    while (count)
    {
        operator++();
        count--;
    }

    return *this;
}

template <typename Type>
typename List<Type>::Iterator& List<Type>::Iterator:: operator-(int count)
{
    while (count)
    {
        operator--();
        count--;
    }

    return *this;
}

template <typename Type>
typename List<Type>::Iterator* List<Type>::Iterator:: operator->()
{
    return this;
}

template <typename Type>
void menu(List<Type>& list)
{
    while (true)
    {
        std::cout << list;
        size_t operation;
        std::cout << "\nPossible operations:\n"
            << "1. push back (data)\n"
            << "2. push front (data)\n"
            << "3. pop back\n"
            << "4. pop front\n"
            << "5. insert (data, index)\n"
            << "6. insert (data, index, count)\n"
            << "7. replace (data)\n"
            << "8. replace (index, data)\n"
            << "9. erase (index)\n"
            << "10. erase (start index, end index)\n"
            << "11. search and save file\n"
            << "12. exit program\n"
            << "Choose operation: ";
        std::cin >> operation;
        std::cout << "\n";

        switch (operation)
        {
        case 1:
        {
            Type element;
            std::cout << "Enter element: ";
            std::cin >> element;
            list.push_back(element);
            break;
        }
        case 2:
        {
            Type element;
            std::cout << "Enter element: ";
            std::cin >> element;
            list.push_front(element);
            break;
        }
        case 3:
        {
            list.pop_back();
            break;
        }
        case 4:
        {
            list.pop_front();
            break;
        }
        case 5:
        {
            Type element;
            std::cout << "Enter element: ";
            std::cin >> element;
            size_t index;
            std::cout << "Enter index: ";
            std::cin >> index;
            list.insert(element, index);
            break;
        }
        case 6:
        {
            Type element;
            std::cout << "Enter element: ";
            std::cin >> element;
            size_t index, count;
            std::cout << "Enter index: ";
            std::cin >> index;
            std::cout << "Enter count: ";
            std::cin >> count;
            list.insert(element, index, count);
            break;
        }
        case 7:
        {
            Type search_element, new_element;
            std::cout << "Enter search element: ";
            std::cin >> search_element;
            std::cout << "Enter new element: ";
            std::cin >> new_element;
            list.replace(search_element, new_element);
            break;
        }
        case 8:
        {
            Type new_element;
            size_t index;
            std::cout << "Enter index: ";
            std::cin >> index;
            std::cout << "Enter new element: ";
            std::cin >> new_element;
            list.replace(index, new_element);
            break;
        }
        case 9:
        {
            size_t index;
            std::cout << "Enter index: ";
            std::cin >> index;
            list.erase(index);
            break;
        }
        case 10:
        {
            int start, finish;
            std::cout << "Enter start index: ";
            std::cin >> start;
            std::cout << "Enter end index: ";
            std::cin >> finish;
            list.erase(list.begin() + start, list.begin() + finish);
            break;
        }

        case 11:
        {
            Type check;


            if (strstr(typeid(check).name(), "Acc") != nullptr)
                bool flag1 = true; //если используется Type Acc, то if == true

#if(flag1)  
                while (true)
                {
                    std::cout << "Operations:\n"
                        << "1. Find number account\n"
                        << "2. Find by date\n"
                        << "3. Find by surname\n\nEnter operation: ";
                    int choice;
                    bool flag = false;
                    std::cin >> choice;

                    switch (choice)
                    {
                    case 1:
                    {
                        std::cout << "\nEnter number account: ";
                        std::string temp_number;
                        std::cin >> temp_number;
                        Type acc(temp_number);
                        std::cout << "\n";
                        list.find(acc);
                        flag = true;
                        break;
                    }
                    case 2:
                    {
                        Acc acc(0, 0, 0);

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
                                flag = true;
                                std::cout << "\n";
                                list.find(acc);
                                break;
                            }

                            std::cout << "Error data!\n";
                        }

                        break;
                    }
                    case 3:
                    {
                        std::string surname;
                        std::cout << "Enter surname: ";
                        std::cin >> surname;
                        Acc acc;
                        acc.surname = surname;
                        std::cout << "\n";
                        list.find(acc);
                        flag = true;
                        break;
                    }
                    default:
                    {
                        std::cout << "Operation selected incorrectly!\n";
                    }
                    }

                    if (flag == true)
                    {
                        break;
                    }
                }
            
            else
            {
                Type element;
                std::cout << "Enter element: ";
                std::cin >> element;
                list.find(element);
                break;
            }
#endif
            break;
        }
 
        case 12:
        {
            return;
        }
        default:
        {
            std::cout << "Operation selected incorrectly!\n";
        }
        }

        std::cout << "\n";
    }
}

