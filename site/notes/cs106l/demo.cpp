#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::set;
using std::string;

void string_constructor() {
  string s1;           // 空构造器
  string s2 = "Blast"; // 字符串字面量
  string s3(s2);       // 拷贝构造器
  string s4(10, 'h');  // s4 = 10 * 'h'
  string s5(s4, 1);    // s5 = s4[1:]
  // string s6(char* begin, char* end);
  char prompt[20] = "Hello world";
  string s7(prompt);
  string s8(prompt, 5);

  cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s7
       << " " << s8 << " " << endl;
}

void string_find() {
  string a = "Hello world";
  cout << (a.find('l', 0) == 2) << endl;  //
  cout << (a.find("wo", 0) == 6) << endl; //
  cout << (a.find("x", 0) == -1) << endl;
  cout << a.substr(6, 10) << endl; // 从下标1开始的7 个字符
  cout << a.substr(6, 2) << endl;
}

void test_set() {
  set<int> s = {1, 2, 3, 4, 5, 6, 7};
  for (auto &ss : s) {
    if (ss & 1) {
      s.insert(s.size());
    } else {
      cout << ss << endl;
    }
  }
}

int main() {
  string a = "AAA";
  cout << a.substr(1);
  return 0;
}
/*
 *
 *
AA
 Blast Blast hhhhhhhhhh hhhhhhhhh Hello world Hello
1
1
1
world
wo
 * */
