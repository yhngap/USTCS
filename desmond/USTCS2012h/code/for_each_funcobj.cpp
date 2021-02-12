#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A void function used to specify the action to be performed for each element in the container
// For this example, we use operator()

class Show {
  public:
    void operator()(int n) {
       cout << n << " ";
    }
};

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
  // - showObj
  //   A function that specifies what action to be performed.
  //   In this case, the function is specified using a function object

  // The returned value of for_each algorithm is a function object that we passed to it
  // In this case, showObj
  Show showObj;
  Show obj = for_each(v.begin(), v.end(), showObj);  

  return 0;
}
