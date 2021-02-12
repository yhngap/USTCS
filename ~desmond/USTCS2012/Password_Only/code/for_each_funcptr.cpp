#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A void function used to specify the action to be performed for each element in the container
// For this example, we use a global function

void show(int n) {
  cout << n << " ";
}

int main() {
  // Construct a vector container to store int values
  vector<int> v;

  // Push 10 values, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 to the container v
  for(int i=0; i<10; i++)
    v.push_back(i+1);
  
  // Use for_each algorithm provided STL to perform action on each value
  // Parameters needed:
  // - v.begin() 
  //   An iterator that points to the first element of the container
  // - v.end()
  //   An iterator that points to the element AFTER the last one in the container
  // - show
  //   A function that specifies what action to be performed.
  //   In this case, the function is specified using a function pointer

  // The returned value of for_each algorithm is a function pointer points to the function
  // that we passed to it
  // In this case, show function
  void(*f)(int) = for_each(v.begin(), v.end(), show);  

  return 0;
}
