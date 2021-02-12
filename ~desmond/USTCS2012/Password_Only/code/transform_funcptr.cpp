#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A int function used to specify the action for each element in the container
// For this example, we use a global function

int addOne(int n) {
  return n + 1;
}

int main() {
  // Construct a vector container to store int values
  vector<int> v;
  // Construct another vector container to store the processed results
  vector<int> resultV;

  // Push 10 values, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 to the container v
  for(int i=0; i<10; i++)
    v.push_back(i+1);

  // Resize the result container to size exactly the same as the input vector container
  resultV.resize(v.size());
  
  // Use transform algorithm provided STL to perform action on each value
  // Parameters needed:
  // - v.begin() 
  //   An iterator that points to the first element of the container
  // - v.end()
  //   An iterator that points to the element AFTER the last one in the container
  // - resultV.begin()
  //   An iterator that points to the start location where the results are stored
  //   In this case, first location of the container
  // - addOne
  //   A function that specifies what action to be performed.
  //   In this case, the function is specified using a function pointer

  // The returned value of transform algorithm is an iterator pointing to the element that follows
  // the last element written in the result container
  vector<int>::iterator it = transform(v.begin(), v.end(), resultV.begin(), addOne);  

  // Print all elements in the result container
  for(vector<int>::iterator p = resultV.begin(); p != resultV.end(); p++)
    cout << *p << " ";

  return 0;
}
