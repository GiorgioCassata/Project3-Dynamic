#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// A recursive function that builds all combinations of
// days with no repeats and without considering order
vector<vector<int>> Function(int n, vector<vector<int>> list) {
    vector<vector<int>> list2;
  // stop condition for recursion
  if (n == 0) {
      return list;
  }

  // add current day
  list2.push_back({n});

  list2.insert(list2.end(), list.begin(), list.end());
  // adding current day to all previous combinations
    for (int i = 1; i < list2.size(); ++i) {
        list2.at(i).push_back(n);
    }

  list.insert(list.end(), list2.begin(), list2.end());
  // recursive call to calculate combinations for next smaller size
  return Function(n-1, list);
}

//4,3,43,2,42,32,432,1,41,31,431,21,421,321,4321

int main() {
    vector<vector<int>> list;
    vector<int> x;
    vector<int> s;

    int numDays;
    int temp;
    bool trigger;
    ifstream file;

    // read in and store into vectors, the x and s series  of numbers
    file.open("input.txt");
    file >> numDays;
    vector<vector<int>> processes (numDays);
    vector<int> sums (pow(numDays-1,2),0);
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        x.push_back(temp);
        //cout << temp << ", ";
    }
    //cout << endl;
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        s.push_back(temp);
        //cout << temp << ", ";
    }
    //cout << endl;
    file.close();

    // calculate all possible processes needed
    for (int i = 0; i < numDays; ++i) {
        for (int j = 0; j < numDays; ++j) {
            if (s.at(j) > x.at(i)) {
                processes.at(i).push_back(x.at(i));
            } else {
                processes.at(i).push_back(s.at(j));
            }
            if (j >= i) {
                break;
            }
        }
    }

/*
    // print out processes matrix
    for (int i = 0; i < processes.size(); ++i) {
        for (int j = 0; j < processes.at(i).size(); ++j) {
            cout << processes.at(i).at(j) << ", ";
        }
        cout << endl;
    }
*/


    list = Function(numDays-1, list);
    list.insert(list.begin(), {0});
    for (int k = 0; k < sums.size()-1; ++k) {
        temp = 0;
        for (int i = 0; i < numDays; ++i) {
            trigger = false;
            for (int a = 0; a < list.at(k).size(); ++a) {
                if (list.at(k).at(a)-1 == i) {
                    temp = 0;
                    trigger = true;
                    break;
                }
            }
            if (trigger) {
                continue;
            }
            sums.at(k) += processes.at(i).at(temp);
            temp++;
        }
    }


    // print list to console w/ sums
    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < list.at(i).size(); ++j) {
            cout << list.at(i).at(j) << ", ";
        }
        cout << "   , " << sums.at(i) << endl;
    }
    cout << endl;

    return 0;
}
