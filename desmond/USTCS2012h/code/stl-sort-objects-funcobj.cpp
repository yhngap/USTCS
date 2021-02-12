#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Person class with two data members: name and age
class Person {
  private:
    string name;
    int age;
  public:
    Person(string name, int age) {
      this->name = name;
      this->age = age;
    }
    void print() {
       cout << "Name: " << name << ", Age: " << age << endl;
    }

    // Grant access right to classes CompareByName and CompareByAge
    friend class CompareByName;
    friend class CompareByAge;
};

// Function object class to compare Person objects by name
class CompareByName {
  public:
    bool operator()(const Person& a, const Person& b) {
      if(a.name > b.name)
        return 1;
      else if(a.name < b.name)
        return -1;
      else
        return 0;
    }
};

// Function object class to compare Person objects by age
class CompareByAge {
  public:
    bool operator()(const Person& a, const Person& b) {
      if(a.age > b.age)
        return 1;
      else if(a.age < b.age)
        return -1;
      else
        return 0;
    }
};

int main() {
  vector<Person> personVector;

  Person p1("Peter", 18);
  Person p2("John", 20);
  Person p3("Tom", 21);

  personVector.push_back(p1);
  personVector.push_back(p2);
  personVector.push_back(p3);

  // Use STL sort to sort the objects in the container according to name
  sort(personVector.begin(), personVector.end(), CompareByName());
  cout << "----- Ordered by name -----" << endl;
  for(vector<Person>::iterator it = personVector.begin(); it != personVector.end(); it++)
    (*it).print();

  cout << endl;

  // Use STL sort to sort the objects in the container according to age
  sort(personVector.begin(), personVector.end(), CompareByAge());
  cout << "----- Ordered by age -----" << endl;
  for(vector<Person>::iterator it = personVector.begin(); it != personVector.end(); it++)
    (*it).print();

  return 0;
}
