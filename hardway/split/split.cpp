#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <string>

using namespace std;

unique_ptr<vector<string>> split(const string& input, const char& separator);

int main(){
    string input("some input");
    unique_ptr<vector<string>> results = split(input, ' ');
    for (auto split : *results) {
        cout << split << endl;
    }
    return 0;
}

// splits string to tokens by separator
unique_ptr<vector<string>> split(const string& input, const char& separator) {
    unique_ptr<vector<string>> result(new vector<string>());
    string tmp("");
    for (auto i : input) {
        if (i == separator) {
            result->push_back(tmp);
            tmp = "";
        } else {
            tmp.push_back(i);
        }
    }
    if (tmp.length() > 0) {
        result->push_back(tmp);
    }
    return result;
}