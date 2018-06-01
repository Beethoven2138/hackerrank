long lesser_right_cnt(int element, int *arr, int n)
{
    long ret = 0;
    for (int i = element + 1; i < n; ++i)
    {
        if (arr[i] < arr[i-1])
            ++ret;
        else
            return ret;
    }
    return ret;
}

// Complete the candies function below.
long candies(int n, int arr_count, int* arr) {
    long candy[n];
    for (int i = 0; i < n; ++i)
        candy[i] = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i - 1 >= 0)
        {
            long right = lesser_right_cnt(i, arr, n) + 1;
            long left;
            if (arr[i-1] >= arr[i])
                left = 1;
            else
                left = candy[i-1] + 1;
            if (left >= right)
                candy[i] = left;
            else
                candy[i] = right;
        }
        else
        {
            candy[i] = lesser_right_cnt(i, arr, n) + 1;
        }
    }
    long ret = 0;
    for (int i = 0; i < n; ++i)
    {
        ret += candy[i];
    }
    return ret;
}
