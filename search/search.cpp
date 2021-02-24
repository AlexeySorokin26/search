#include <iostream>
#include <string>

# define NO_OF_CHARS 256  

using namespace std;

void printArr(const int* arr, const int size) {
    for (size_t i = 0; i < size; ++i)
        cout << arr[i] << '\t';
    cout << endl;
}

int bindarySearchRecursion(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return bindarySearchRecursion(arr, l, mid - 1, x);
        return bindarySearchRecursion(arr, mid + 1, r, x);
    }
    return -1; // don't have such element
}

void search(const string& pat, const string& txt)
{
    int M = pat.size();
    int N = txt.size();
    int j;
    for (int i = 0; i <= N - M; i++) {
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) 
                break; 
        } 
        if (j == M)
            cout << "Pattern found at index " << i << endl; 
    }
}

void computeLPS(const string& pat, int* lps) {
    int j = 0;
    lps[0] = 0;

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else {
            if (j != 0)
                j = lps[j - 1]; // move if we increse 
            else
                lps[i++] = 0;
        }
    }
}

void KMPSearch(const string& pat, const string& txt)
{
    int* lps = new int[pat.size()];

    computeLPS(pat, lps);

    int i = 0;
    int j = 0;
    while (i < txt.size()) {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == pat.size()) {
            cout << "Found pattern at index" << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < txt.size() && pat[j] != txt[i]) {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
    delete[] lps;
}

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void searchMur(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            cout << "pattern occurs at shift = " << s << endl;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }
        else {
            int bc = badchar[txt[s + j]];
            s += max(1, j - bc);
        }
    }
}

bool subArraySum(int* arr, int n, int sum) {
    int totalSum = 0;
    for (size_t i = 0; i < n; ++i)
        totalSum += arr[i];
    if (sum > totalSum) {
        cout << "-1" << endl;
        return false;
    }

    
    int i = 0;

    int tmpSum = 0;
    int shifter = 0;

    while (shifter < n && i < n){
        tmpSum += arr[i];
        if (tmpSum == sum) {
            cout << shifter << " " << i << endl;
            return true;
        }
        if (tmpSum > sum) {
            tmpSum = 0;
            shifter++;
            i = shifter;
        }
        else {
            i++;
        } 
    }
    cout << "-1" << endl;
    return false;
}

bool isKPeriodic(const string& str, const int k) {
    // if k is unvalid
    // it could be less than 0 or bigger than a size of str or we could't divide our str into k equals elements 
    if ((k <= 0) || (k >= str.size()) || (str.size() % k != 0))
        return false;
    
    // first we accumulate our pattern; 
    // abcabcabc -> in the first iteration: a; in the second: ab; and so on
    string pattern = str.substr(0, k);

    // second we should compare our possible periodicy
    // if already first element after our pattern is wrong -> we don't have any periodicy
    //cout << (str.size() / k) << endl;
    for (size_t i = 1; i < (str.size() / k); ++i) {
        //cout << str.substr(k * i, k) << endl;
        if (pattern != str.substr(k * i, k ))
            return false;
    }
    return true;
}
int main()
{
    string text{ "ABCABCABC" };
    cout << isKPeriodic(text, 3) << endl;
    string text1{ "ABCABCABB" };
    cout << isKPeriodic(text1, 3) << endl;
    string text2{ "AABAACAABAA" };
    cout << isKPeriodic(text2, 3) << endl;
    string text3{ "ABCABCAB" };
    cout << isKPeriodic(text3, 3) << endl;
    string text4{ "ABCABC" };
    cout << isKPeriodic(text4, 3) << endl;
    string text5{ "ABC" };
    cout << isKPeriodic(text5, 1) << endl;
    //int* lps = new int[pattern.size()];
    //KMPSearch(pattern, text);
    //const int size = 10;
    //int arr[size]{ 0,-1,100,1,10,1,1,2,1,1 };
    //subArraySum(arr, size, 3);
    //delete[] lps;
    
}
