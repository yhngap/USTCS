#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A predicate, i.e. a boolean function, used to specify the criteria for the searching
// In our case, the criteria is prime
// For this example, we use a global function as the predicate

bool isPrime(int n) {
  if(n <= 1)
    return false;
  for(int i=2; i<=n/2; i++) {
    if(n%i == 0)
      return false;
  }
  return true;
}

int main() {
  // Construct a vector container to store int values
  vector<int> v;

  // Push 10 values, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, to the container v
  for(int i=10; i>1; i--)
    v.push_back(i);
  
  // Use find_if algorithm provided STL to search for the first value that satisfy the criteria
  // specified by the predicate, i.e. the first prime number
  // Parameters needed:
  // - v.begin() 
  //   An iterator that points to the first element of the container
  // - v.end()
  //   An iterator that points to the element AFTER the last one in the container
  // - isPrime
  //   A predicate that specifies the searching criteria 
  //   In this case, the predicate is specified using a function pointer
  vector<int>::iterator it = find_if(v.begin(), v.end(), isPrime);

  // If the returned iterator by find_if algorithm is not pointing at
  // the location AFTER the last one, then the element is found.
  // Otherwise, it is not found
  if(it != v.end())
    cout << "Element is found and it is " << *it << endl;
  else
    cout << "No element satisfies the criteria specified by the prediacte" << endl;

  return 0;
}
