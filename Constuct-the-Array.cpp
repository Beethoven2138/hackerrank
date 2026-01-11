#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countArray' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER x
 */

long countArray(int n, int k, int x) {
    // Return the number of ways to fill in the array.
    long dp[n+1][2]; 
    /*dp[n][0] is num of arrays of length n ending in 1,
    dp[n][0] = num of arrays of length n where x != 1*/
    dp[2][0] = 0;
    dp[2][1] = 1;
    for (int i = 3; i <= n; ++i)
    {
        dp[i][0] = ((k-1)*dp[i-1][1]) % 1000000007;
        dp[i][1] = (dp[i-1][0] + (k-2)*dp[i-1][1]) % 1000000007;
    }
    if (1 == x)
    {
        return dp[n][0];
    }
    else
        return dp[n][1];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    int x = stoi(first_multiple_input[2]);

    long answer = countArray(n, k, x);

    fout << answer << "\n";

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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
