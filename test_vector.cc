#include <iostream>
#include <vector>


void PrintVector(_std::vector<int>& xx) {
  std::cout << "begin:" << xx.begin()
            << ",end:" << xx.end() 
            << ",size:" << xx.size()
            << ",capacity:" << xx.capacity() 
            << std::endl;
}


int main() {
  std::cout << "testing the sgi stl vector container .." << std::endl;
  _std::vector<int> xx;

  std::cout << "  ---- test vector<int>.push_back()" << std::endl;
  xx.push_back(4);
  xx.push_back(2);
  xx.push_back(6);
  xx.push_back(8);

  _std::vector<int>::iterator it;
  for (it = xx.begin(); it != xx.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  PrintVector(xx);
  //std::cout << "  ---- test list<int>.empty()" << std::endl;
  //std::cout << xx.empty() << std::endl;

  //std::cout << "  ---- test list<int>.pop_front()" << std::endl;
  //xx.pop_front();
  //for (it = xx.begin(); it != xx.end(); ++it) {
  //  std::cout << *it << " ";
  //}
  //std::cout << std::endl;

  //std::cout << "  ---- test list<int>.pop_back()" << std::endl;
  //xx.pop_back();
  //for (it = xx.begin(); it != xx.end(); ++it) {
  //  std::cout << *it << " ";
  //}
  //std::cout << std::endl;


  //std::cout << "  ---- test list<int>.push_front()" << std::endl;
  //xx.push_front(12);
  //for (it = xx.begin(); it != xx.end(); ++it) {
  //  std::cout << *it << " ";
  //}
  //std::cout << std::endl;

  //std::cout << "  ---- test list<std::string>.push_back()" << std::endl;

  //_std::list<std::string> xx_str;
  //xx_str.push_back("hello");
  //xx_str.push_back("world");
  //_std::list<std::string>::iterator it_str;
  //for (it_str = xx_str.begin(); it_str != xx_str.end(); ++it_str) {
  //  std::cout << *it_str << " ";
  //}
  //std::cout << std::endl;

  return 0;
}
