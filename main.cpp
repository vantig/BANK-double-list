#include "Bank.cpp"

int main()
{
    //реализация с int, пока работает ккоректно
    {
                std::cout << "Task 1.\nCheck list operation (int type)\n\n";
                List<int> list;
                menu(list);
    }

    //домашнее задание про банк
    {
        std::cout << "Task 2.\nBank account\n\n";
        List<Acc> list;
        std::ifstream in("BY.txt"); //создаем поток для чтение файла
        in >> list; //копируем все из файла в List
        menu(list);
        in.close();
        system("pause");
    }

    system("pause");
    return 0;
}
