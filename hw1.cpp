#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int convertToDecimal(string number, int startingBase)
{
    int decimal = 0;
    int length = number.length();

    for (int i = 0; i < length; i++)
    {
        if (number[i] >= '0' && number[i] <= '9')
        {
            decimal += (number[i] - '0') * pow(startingBase, length - i - 1);
        }
        else if (number[i] >= 'A' && number[i] <= 'F')
        {
            decimal += (number[i] - 'A' + 10) * pow(startingBase, length - i - 1);
        }
    }
    return decimal;
}

void convertBase(string number, int startingBase, int targetBase)
{
    vector<int> bases = {2,
                         8,
                         10,
                         16};

    auto it = find(bases.begin(), bases.end(), startingBase);
    auto it2 = find(bases.begin(), bases.end(), targetBase);

    if (it == bases.end() || it2 == bases.end())
    {
        cout << "Invalid base input. Avaliable inputs: 2, 8, 10, 16." << endl;
    }

    int decimal = convertToDecimal(number, startingBase);
    int remainder;
    string result = "";

    while (decimal > 0)
    {
        remainder = decimal % targetBase;
        if (remainder < 10)
        {
            result += char(remainder + '0');
        }
        else
        {
            result += char((remainder - 10) + 'A');
        }
        decimal /= targetBase;
    }
    if (result.empty())
    {
        result = "0";
    }
    reverse(result.begin(), result.end());

    cout << "original: " << number << " (" << startingBase << ")" << endl;
    cout << "converted: " << result << " (" << targetBase << ")" << endl;

    // return result;
}

float recursiveSqrt(float x, int n)
{
    if (n <= 0)
    {
        return x;
    }
    return recursiveSqrt(std::sqrt(x), n - 1);
}

float recursiveSquare(float x, int n)
{
    if (n <= 0)
    {
        return x;
    }
    return recursiveSquare(x * x, n - 1);
}

vector<double> limit(vector<double> X, int part)
{

    vector<double> result;
    double y;
    double z;

    for (int i = 0; i < X.size(); ++i)
    {

        if (part == 1)
        {
            if (X[i] == 0)
            {
                z = 1;
            }
            else
            {
                z = (exp(X[i]) - 1) / X[i];
            }
            result.push_back(z);
        }
        else if (part == 2)
        {

            y = exp(X[i]);
            if (y == 1)
            {
                z = 1;
            }
            else
            {

                z = (y - 1) / log(y);
            }
            result.push_back(z);
        }
    }
    return result;
}

float sum(int n, int direction)
{
    float s;
    if (direction == 1)
    {
        for (int i = 1; i < n + 1; i++)
        {
            s += pow(-1, i + 1) * (1 / i);
        }
    }

    if (direction == 0)
    {
        for (int i = 0; i < n; i++)
        {
            s += pow(-1, n - i + 1) * (1 / (n - i));
        }
    }
    return s;
}

double getExponet(double f)
{
    double f_ab = fabs(f);
    uint64_t bits;
    memcpy(&bits, &f_ab, sizeof(f));

    int exponent = ((bits >> 52) & 0x7FF) - 1023;
    double x = exponent * log10(2);
    return x;
}

int main(void)
{

    convertBase("56", 10, 16);

    vector<int> N = {2, 5, 10, 20, 20, 40};
    // vector<float> X;
    // vector<float> diff;
    float squared_x;
    float x;

    for (int n : N)
    {
        squared_x = recursiveSqrt(100, n);
        x = recursiveSquare(squared_x, n);

        cout << "N: " << n << " x = " << x << " diff: " << fabs(x - 100) << endl;
    }

    vector<double> X = {1e-5,
                        1e-6,
                        1e-7,
                        1e-8,
                        1e-9,
                        1e-10,
                        1e-11,
                        1e-12,
                        1e-13,
                        1e-14,
                        1e-15,
                        1e-16,
                        1e-17};

    vector<double> z1;
    vector<double> z2;

    z1 = limit(X, 1);
    z2 = limit(X, 2);

    for (int i = 0; i < X.size(); i++)
    {
        cout << "x: " << X[i] << " z1: " << z1[i] << " z2: " << z2[i] << endl;
    }

    vector<int> N2 = {1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    vector<float> err1;
    vector<float> err2;
    float s = log(2);
    float s_fwd;
    float s_rvs;

    for (int n : N2)
    {

        s_fwd = sum(n, 1);
        s_rvs = sum(n, 0);

        err1.push_back(fabs(s_fwd - s));
        err2.push_back(fabs(s_rvs - s));
    }
    std::ofstream file("data.csv");
    if (file.is_open())
    {
        file << std::fixed << std::setprecision(8);
        file << "N,Error1,Error2\n";
        for (int i = 0; i < N2.size(); i++)
        {
            cout << "N: " << N2[i] << " fwd diff: " << err1[i] << " rvs diff: " << err2[i] << endl;
            file << N2[i] << "," << err1[i] << "," << err2[i] << "\n";
        }
    }
    vector<double> num5 = {1234.5678, 7.49 * pow(10, -8), 7547, 52500.5, 6.7854, 3408944};
    double exponet;
    for (double num : num5)
    {
        exponet = getExponet(num);
        cout << "float: " << num << " exponet: " << exponet << endl;
    }

    return 0;
}
