#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'substrings' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING n as parameter.
 */

int substrings(string n) {
    long long ret = (long long)(n[0] - '0');
    long long sum_of_substrings_ending_at_prev = (n[0] - '0');
    for (int i = 1; i < n.length(); ++i)
    {
        sum_of_substrings_ending_at_prev = ((long long)(n[i] - '0') * i + sum_of_substrings_ending_at_prev * 10 + (long long)(n[i] - '0')) % 1000000007;
        ret = (ret + sum_of_substrings_ending_at_prev) % 1000000007;
    }
    return (int)(ret% 1000000007);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n;
    getline(cin, n);

    int result = substrings(n);

    fout << result << "\n";

    fout.close();

    return 0;
}
