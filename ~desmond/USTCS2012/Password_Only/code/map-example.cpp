/*
   Map containers are used to store key-value pairs, in which each key
   is UNIQUE and cannot be changed. Pairs can be inserted or removed but
   cannot be changed.

   Note: Keys are arranged in ascending order in map, i.e. in sorted order.
*/

#include <iostream>
#include <map>
using namespace std;

// A non-member to print all the pairs in map m
void print(const map<int,string>& m)
{
  // const_iterator is used as we are not supposed to change the
  // element that the iterator points at 
  for(map<int,string>::const_iterator it = m.begin(); it != m.end(); ++it)
    cout << "<" << it->first << "," << it->second << ">" << endl;
}

int main()
{
  // Create a map object m that stores <int,string> pairs
  map<int,string> m;

  // Add the pair with key = 21619321, and value = "Peter Wong"
  m[21619321] = "Peter Wong";
  // Add the pair with key = 21582152, and value = "John Chan"
  m[21582152] = "John Chan";
  // Add the pair with key = 21563291, and value = "Andy Pun"
  m[21563291] = "Andy Pun";

  // Print the value with key = 21582152
  cout << "The value of key 21582152: " << m[21582152] << endl;
  // Print the value with key = 21563291
  cout << "The value of key 21563291: " << m.at(21563291) << endl;

  // empty() returns true if the map is empty, else it returns false
  cout << "Is m empty? " << boolalpha << m.empty() << endl;
  // size() returns number of entries in the map
  cout << "Size of m: " << m.size() << endl;
  // count(k) returns the number of times the key k is present in m
  cout << "Number of times the key 21619321 is present: " << m.count(21619321) << endl;
  // max_size() returns the maximum number of entries that a map can contain
  cout << "Max size of m: " << m.max_size() << endl;

  // Print all the pairs in m
  print(m);

  // Insert the pair <21562671, "Desmond Tsoi"> to m
  m.insert(pair<int,string>(21562671, "Desmond Tsoi"));
  cout << "After pair <21562671,\"Desmond Tsoi\"> is inserted" << endl;
  // Print all the pairs in m
  print(m);

  // Do not insert the pair as m contains the key 21619321 already
  m.insert(pair<int,string>(21619321, "Haha"));
  cout << "After pair <21619321,\"Haha\"> is inserted" << endl;
  // Print all the pairs in m
  print(m);

  // Remove the element with key = 21582152
  m.erase(21582152);
  cout << "After the element with key = 21582152 is removed" << endl;
  // Print all the pairs in m
  print(m);

  // Removes all elements in m
  m.clear();
  cout << "After removing all the elements" << endl;
  // Print all the pairs in m
  print(m);

  return 0;
}
