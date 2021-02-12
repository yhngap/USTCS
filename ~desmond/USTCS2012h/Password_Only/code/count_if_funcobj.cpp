#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A predicate, i.e. a boolean function, to specify the criteria for the counting
// In our case, the criteria is prime
// For this example, we use operator() as the predicate

class Prime {
  public:
    bool operator()(int n) {
      if(n <= 1)
        return false;
      for(int i=2; i<n/2; i++) {
        if( n%i == 0 )
           return false;
      }
      return true;
    }
};

int main() {
  // Construct a vector container to store int values
  vector<int> v;

  // Push 10 values, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, to the container v
  for(int i=10; i>1; i--)
    v.push_back(i);
  
  // Use count_if algorithm provided STL to count the number of elements satisfy the criteria
  // i.e. prime
  // Parameters needed:
  // - v.begin() 
  //   An iterator that points to the first element of the container
  // - v.end()
  //   An iterator that points to the element AFTER the last one in the container
  // - primeObj
  //   A predicate that specifies what value we would like to take into acoount
  //   In this case, the predicate is specified using a function object
  Prime primeObj;
  int number = count_if(v.begin(), v.end(), primeObj);

  cout << "The number of elements satisfy the criteria specified by the predicate is " << number << endl;

  return 0;
}