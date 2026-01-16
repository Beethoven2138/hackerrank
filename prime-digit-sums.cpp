#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'primeDigitSums' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */

int primes[14]={2,3,5,7,11,13,17,19,23,29,31,37,41,43};

bool is_prime(int num)
{
    for (int i = 0; i < 14; ++i)
    {
        if (num == primes[i])
            return true;
    }
    return false;
}


int primeDigitSums(int n)
{
    n=5;
    vector<vector<int>> threes;
    for (int a = 9; a >= 0; --a)
    {
        for (int b = 0; b <= 9; ++b)
        {
            for (int c = 0; c <= 9; ++c)
            {
                if (is_prime(a+b+c))
                    threes.push_back({a,b,c});
            }
        }
    }
    if (n == 3)
    {
        for (int i = 0; i < threes.size(); ++i)
        {
            if (threes[i][0] == 0)
                return i;
        }
    }
    vector<vector<int>> fours;
    vector<vector<int>> fours_old;
    int dp[10000] = {};
    int dp_old[10000] = {};
    /*final element in one of them is the num of 
    n-digit Chloe-numbers ending in that four-digit number*/
    for (int i = 0; i < threes.size(); ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            if (is_prime(threes[i][0]+threes[i][1]+threes[i][2]+j)
                && is_prime(threes[i][1]+threes[i][2]+j))
                {
                    fours.push_back({threes[i][0],threes[i][1],threes[i][2],j,1});
                    fours_old.push_back({threes[i][0],threes[i][1],threes[i][2],j,1});
                    dp[threes[i][0]*1000+threes[i][1]*100+threes[i][2]*10+j]=1;
                    dp_old[threes[i][0]*1000+threes[i][1]*100+threes[i][2]*10+j]=1;
                }
        }
    }
    if (n == 4)
    {
        for (int i = 0; i < fours.size(); ++i)
        {
            if (fours[i][0] == 0)
                return i;
        }
    }
    /*
    Want to keep track of number of i-digit Chloe-numbers with a given final four digits.
    Then for i+1, we can iterate through the possible four-digit numbers, and for each one,
    we iterate through the digits 0-9, and if one ends up working, we increment the count of 
    the new final four-digit number by the count of the old four-digit number.
    */
    for (int i = 5; i <= n; ++i)
    { 
        //prev=curr
        for (int k = 0; k < fours.size(); ++k)
        {
            //fours_old[k][4]=fours[k][4];
            dp_old[fours[k][0]*1000+fours[k][1]*100+fours[k][2]*10+fours[k][3]] = 
            dp[fours[k][0]*1000+fours[k][1]*100+fours[k][2]*10+fours[k][3]];
            //fours[k][4]=0;
            dp[fours[k][0]*1000+fours[k][1]*100+fours[k][2]*10+fours[k][3]]=0;
        }
        if (i == 5)
        {
            for (int k = 0; k < fours.size(); ++k)
            {
                if (fours[k][0] == 0)
                    break;
                for (int j = 0; j <= 9; ++j)
                {
                    if (is_prime(fours[k][0]+fours[k][1]+fours[k][2]+fours[k][3]+j)
                    &&  is_prime(fours[k][1]+fours[k][2]+fours[k][3]+j)
                    &&  is_prime(fours[k][2]+fours[k][3]+j))
                    dp[fours[k][1]*1000+fours[k][2]*100+fours[k][3]*10+j]
                    += dp_old[fours[k][0]*1000+fours[k][1]*100+fours[k][2]*10+fours[k][3]]% 1000000007;
                }
            }
            continue;
        }
        for (int k = 0; k < fours.size(); ++k)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (is_prime(fours[k][0]+fours[k][1]+fours[k][2]+fours[k][3]+j)
                &&  is_prime(fours[k][1]+fours[k][2]+fours[k][3]+j)
                &&  is_prime(fours[k][2]+fours[k][3]+j))
                    dp[fours[k][1]*1000+fours[k][2]*100+fours[k][3]*10+j]
                    += dp_old[fours[k][0]*1000+fours[k][1]*100+fours[k][2]*10+fours[k][3]]% 1000000007;
            }
        }
    }
    int ret = 0;
    for (int i = 1; i < 10000; ++i)
    {
        ret += dp[i]% 1000000007;
    }
    return ret% 1000000007;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        int result = primeDigitSums(n);

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
