#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'abbreviation' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */

string abbreviation(string a, string b) {
    bool dp[1001][1001] = {};
    dp[0][0] = true;
    for (int i = 1; i < a.length(); ++i)
    {
        if (islower(a[i-1]))
            dp[i][0] = dp[i-1][0];
        else
            dp[i][0] = false;
    }
    for (int i = 1; i <= a.length(); ++i)
    {
        for (int j = 1; j <= b.length(); ++j)
        {
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else if (toupper(a[i-1]) == b[j-1])
                dp[i][j] = dp[i-1][j-1] || dp[i-1][j];
            else if (islower(a[i-1]))
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = false;
        }
    }
    if (dp[a.length()][b.length()])
        return "YES";
    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
