#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sign(int x)
{
    if (x == 0)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}

void print(const vector<vector<char>>& myField, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << myField[i][j] << " ";
        }
        printf("\n");
    }
}

void snow(vector<vector<char>>& myField, int depth, int curLevel, int x0, int y0, int xPrev, int yPrev)
{   
    if (curLevel != depth)
    {
        //cout << y0 << " " << x0 <<  " " << yPrev << " " << xPrev << " " << curLevel << endl;
        vector <int> x;
        vector <int> y;
        int l = abs(y0 - yPrev) + abs(x0 - xPrev);
        int signx = sign(x0-xPrev);
        int signy = sign(y0 - yPrev);
        if (l != 0)
        {
            if (signy == 0)
            {
                x.push_back(x0); x.push_back(x0); x.push_back(x0+l/2*signx); x.push_back(x0+l/2*signx);
                y.push_back(y0+l/2); y.push_back(y0-l/2); y.push_back(y0); y.push_back(y0); 
            }
            else
            {
                x.push_back(x0); x.push_back(x0); x.push_back(x0+l/2); x.push_back(x0-l/2);
                y.push_back(y0+l/2*signy); y.push_back(y0+l/2*signy); y.push_back(y0); y.push_back(y0);
            }
            for (int i = 0; i < 4; ++i)
            {   
                if ((x[i] > 0) && (y[i] > 0))
                {
                    myField[y[i]][x[i]] = '+';
                    snow(myField, depth, curLevel+1, x[i], y[i], x0, y0);
                }
            }
        }
    }

}


int main()
{
    int n, d;
    cout << "Matrix size (Natural number):" << endl;
    cin >> n;
    cout << "Difficulty (Natural number):" << endl;
    cin >> d;
    if ((n > 0) && (d > 0))
    {
        vector<vector<char>> field(n, vector<char> (n, ' '));
        //print(field, n);
        if (n % 2 == 1)
        {
            int x0 = n / 2;
            int y0 = n / 2;
            field[y0][x0] = '*';
            //cout << x0 << ' ' << y0 << endl;

            vector <int> x;
            vector <int> y;
            x.push_back(x0); x.push_back(x0); x.push_back(x0/2); x.push_back(n-1-x0/2);
            y.push_back(y0/2); y.push_back(n-1-y0/2); y.push_back(y0); y.push_back(y0); 

            for (int i = 0; i < 4; ++i)
            {   
                field[y[i]][x[i]] = '*';
                snow(field, d, 1, x[i], y[i], x0, y0);
            }
            print(field, n);
        }
        else
        {
            vector <int> x0;
            vector <int> y0;
            x0.push_back(n/2); x0.push_back(n/2); x0.push_back(n/2-1); x0.push_back(n/2-1);
            y0.push_back(n/2); y0.push_back(n/2-1); y0.push_back(n/2); y0.push_back(n/2-1);

            vector <int> x;
            vector <int> y;
            x.push_back(x0[0]); x.push_back(x0[1]); x.push_back(n-1-x0[2]/2); x.push_back(x0[3]/2);
            y.push_back(n-1-y0[0]/2); y.push_back(y0[1]/2); y.push_back(y0[2]); y.push_back(y0[3]);

            for (int i = 0; i < 4; ++i)
            {   
                //cout << x0[i] << " " << y0[i] << " " << x[i] << " " << y[i] << endl;
                field[y0[i]][x0[i]] = '*';
                field[y[i]][x[i]] = '*';
                snow(field, d, 1, x[i], y[i], x0[i], y0[i]);
            }
            print(field, n);
        }
    }
    else
    {
        cout << "Wrong params" << endl;
    }

    return 0;
}