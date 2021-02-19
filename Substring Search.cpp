#include <iostream>
#include <cstdio>
#include <cstring>
#include <windows.h>

using namespace std;

void FillTable(char *temp, int *table, int n)
{
    for (int i = 0; i < 256; i++)
        table[i] = n;

    char ch = temp[n-1];
    for (int i = 0; i < n - 1; i++)
        if (ch == temp[i])
            table[(int)ch] = n - i - 1;

    ch = temp[n-2];
    table[(int)ch] = 1;

    for (int i = n - 3; i > - 1; i--)
    {
        ch = temp[i];
        for (int j = i + 1; j < n - 1; j++)
            if (ch == temp[j])
                table[(int)ch] = table[(int)temp[j]];

        if (table[(int)ch] == n)
            table[(int)ch] = n - i - 1;
    }
}

int SubstringSearch(char *str, char *temp, int *table, int n, int m)
{
    int curr = m - 1;
    bool found = false;

    while (!found && (curr < n))
    {
        int i = curr, j = m - 1;
        while ((j > -1) && (str[i] == temp[j]))
        {
            i--;
            j--;
        }

        if (j != -1)
            curr += table[(int)str[curr]];
        else
            found = true;
    }

    if (found)
        return curr;
    else
        return 0;
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    char temp[100], str [200];
    cout << "enter string: " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        gets(str);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << endl << "enter search pattern: " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        gets(temp);
    cout << endl;

    int table[256];
    FillTable(temp, table, strlen(temp));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    int point = SubstringSearch(str, temp, table, strlen(str), strlen(temp));
    if (point)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        for (int i = 0; i < point - strlen(temp) + 1; i++)
            cout << str[i];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        for (int i = point - strlen(temp) + 1; i < point + 1; i++)
            cout << str[i];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        for (int i = point + 1; i < strlen(str); i++)
            cout << str[i];
    }
    else
        cout << "this string does not contain this pattern" << endl;

}
