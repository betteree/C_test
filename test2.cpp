#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#define NUM 100000

using namespace std;
int main()
{
    int N;
    cin >> N;
    int old[NUM];
    char name[NUM];

    for (int i = 0; i < N; i++) {
        cin >> old[i] >> name[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++)
        {
            if (old[i] > old[j] || (old[i] == old[j] && i > j))
            {
                swap(old[i], old[j]);
                swap(name[i], name[j]);
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << old[i] << " " << name[i] << endl;
    }


    return 0;

}
