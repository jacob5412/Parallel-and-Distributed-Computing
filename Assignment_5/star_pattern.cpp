#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

int main()
{
    int n = 64;
    vector<vector<int>> vectors(4, vector<int>());
#pragma omp parallel num_threads(4), shared(vectors, n)
    {
#pragma omp for schedule(static)
        for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
    vector<string> strings(4, string());

    for (int i = 0; i != n; i++)
    {
        for (int j = 0; j != 4; j++)
        {
            const auto &vector = vectors[j];
            auto it = find(vector.begin(), vector.end(), i);

            if (it != vector.end())
            {
                strings[j] += "*";
            }
            else
            {
                strings[j] += " ";
            }
        }
    }
    for (auto &s : strings)
    {
        cout << s << "\n";
    }

    cout << std::endl;

    return 0;
}
