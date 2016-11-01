#include <iostream>
#include <stack>

using namespace std;

int main(void) {

  stack<int> s;
  s.push(0);
  s.push(1);
  s.push(2);
  s.push(3);

  cout << *s.begin() << " " << *s.end();

}
