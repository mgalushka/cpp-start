#include <iostream>
#include <string>

using namespace std;

void concat_0() {
    const string hello = "Hello";
    const string message = hello + ", world" + "!";
    cout << message << endl;
}

void concat_1() {
    const string exclam = "!";
    const string message = "Hello, world" + exclam;
    cout << message << endl;
}

void block_0() {
    { const string exclam = "!";
      cout << exclam << endl; }
    { const string exclam = "Another string";
      cout << exclam << endl; }
}

void block_1() {
    { const string exclam = "!";
      cout << exclam << endl;
    { const string exclam1 = "Another string";
      cout << exclam1 << endl; }}
}

void block_2() {
    { const string a = "a string";
      const string b = a + ", really?"; 
      cout << a << endl;
      cout << b << endl; }
}

int main(){
    concat_0();
    concat_1();
    block_0();
    block_1();
    block_2();
}