#include "Bank.cpp"

int main()
{
    //���������� � int, ���� �������� ���������
    {
                std::cout << "Task 1.\nCheck list operation (int type)\n\n";
                List<int> list;
                menu(list);
    }

    //�������� ������� ��� ����
    {
        std::cout << "Task 2.\nBank account\n\n";
        List<Acc> list;
        std::ifstream in("BY.txt"); //������� ����� ��� ������ �����
        in >> list; //�������� ��� �� ����� � List
        menu(list);
        in.close();
        system("pause");
    }

    system("pause");
    return 0;
}
