//This is a program for executing 2 different searching algorithms, linear and binary search.

#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std::chrono;
using namespace std;

class Searching
{
public:
    
    //Constructor to initially write data to file 
    Searching()
    {
        fstream file;
        int height;
        int roll_no = 1;      //roll_no and iterator

        file.open("data.txt", ios::trunc | ios::out | ios::in);

        while (roll_no <= 1000)
        {

            height = rand()%10;
            file << height << endl;
            roll_no++;

        }

        file.close();
    }

    //Home function calls the banner and the choice function which displays a menu
    void home()
    {
        //system("CLS");
        banner();
        int result;
        result = choice();
        action(result);
    }

    //Banner for the program
    void banner()
    {
        cout << "\n##########################" << endl;
        cout << "    Searching Algorithms" << endl;
        cout << "##########################" << endl;
    }

    //Menu for asking the user for a choice
    int choice()
    {
        int x;
        cout << "\nChoose: " << endl;
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter you choice: ";
        cin >> x;
        return x;
    }

    //Calling the searching algorithm based on user input
    void action(int res)
    {
        if (res == 1)
        {
            int height;
            cout<<"Enter the height you are looking for: ";
            cin>>height;
            linearSearch(height);
            home();
        }
        else if (res == 2)
        {
            int height;
            cout<<"Enter the height you are looking for: ";
            cin>>height;
            vector< pair <int,int> > data = read();
            data = mergeSort(data);
            int s = data.size();
            binarySearch(data, 0, s, height);
            home();
        }
        else if (res == 3)
        {
            exit(0);
        }
        else
        {
            cout << "\nInvalid Input" << endl;
            cout << "Redirecting back to home screen..." << endl;
            sleep(2);
            home();
        }
    }

    //Read data from the file and add it to a vector
    vector< pair <int,int> > read()
    {
        vector< pair <int,int> > data;
        fstream file;
        int height;
        int roll_no = 1;

        file.open("data.txt", ios::out | ios::in);

        file.seekg(0, ios::beg);

        while (!file.eof())
        {
            file >> height;
            data.push_back(make_pair(height, roll_no));
            roll_no++;
        }

        file.close();

        return data;
    }

    //Linear search on vector pair, prints all the students who have height greater than the user input
    void linearSearch(int height)
    {
        vector< pair <int,int> > data = read();
        data = mergeSort(data);

        // Start time
        auto start = high_resolution_clock::now();

        int s = data.size();
        for (int i=0; i<s; i++)
        {
            if(data[i].first > height)
            {
                cout << "Roll No: " << data[i].second << " , " << "Height: " << data[i].first<< endl;
            }
        }

        // Stop time
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\nTime taken for execution: " << duration.count() << endl;

    }

    //Binary search on vector pair, prints all students who have height greater than user input
    void binarySearch(vector< pair <int,int> > data, int lb, int ub, int height)
    {
        // Start time
        auto start = high_resolution_clock::now();

        while (lb != ub) {
            int mid = (lb + ub) / 2;
            if (data[mid].first <= height) 
            {
                lb = mid + 1;
            }
            else 
            {
                ub = mid;
            }
        }
        
        int s = data.size();
        for (int i=ub; i<s; i++)
        {
            if(data[i].first > height)
            {
                cout << "Roll No: " << data[i].second << " , " << "Height: " << data[i].first<< endl;
            }
        }

        // Stop time
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\nTime taken for execution: " << duration.count() << endl;
    }

    //Merge sort algorithm
    vector< pair <int,int> > mergeSort(vector< pair <int,int> > data)
    {
        if (data.size() <= 1)
            return data;

        vector< pair <int,int> > left, right, result;
        int middle = (data.size() + 1) / 2;

        for (int i = 0; i < middle; i++)
        {
            left.push_back(data[i]);
        }

        for (int i = middle; i < data.size(); i++)
        {
            right.push_back(data[i]);
        }

        left = mergeSort(left);
        right = mergeSort(right);
        result = merge(left, right);

        return result;
    }

    //Merge the left and right vector received from the mergeSort function
    vector< pair <int,int> > merge(vector< pair <int,int> > left, vector< pair <int,int> > right)
    {
        vector< pair <int,int> > result;
        while (left.size() > 0 || right.size() > 0)
        {
            if (left.size() > 0 && right.size() > 0)
            {
                if (left.front() <= right.front())
                {
                    result.push_back(left.front());
                    left.erase(left.begin());
                }
                else
                {
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            }
            else if (left.size() > 0)
            {
                for (int i = 0; i < left.size(); i++)
                    result.push_back(left[i]);
                break;
            }
            else if (right.size() > 0)
            {
                for (int i = 0; i < right.size(); i++)
                    result.push_back(right[i]);
                break;
            }
        }
        return result;
    }

};

int main()
{
    Searching search;
    search.home();
}