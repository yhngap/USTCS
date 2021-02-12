#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  // Construct a vector container to store int values
  vector<int> v;

  // Push 10 values, 1,2,3,4,5,6,7,8,9,10, to the container v
  for(int i=0; i<10; i++)
    v.push_back(i+1);
  
  // Assume we want to check whether value 5 is in the container
  int element = 5;

  // Use find algorithm provided STL to search for the value
  // Parameters needed:
  // - v.begin() 
  //   An iterator that points to the first element of the container
  // - v.end()
  //   An iterator that points to the element AFTER the last one in the container
  // - element
  //   The variable that carries the target value
  vector<int>::iterator it = find(v.begin(), v.end(), element);

  // If the returned iterator by find algorithm is not pointing at
  // the location AFTER the last one, then the element is found. 
  // Otherwise, it is not found
  if(it != v.end())
    cout << "Element " << element << " is in the container" << endl;
  else
    cout << "Element " << element << " is not in the container" << endl;
  return 0;
}
