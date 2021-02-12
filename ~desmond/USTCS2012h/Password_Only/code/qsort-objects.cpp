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
    // Grant access right to functions compareByName and compareByAge
    friend int compareByName(const void* a, const void* b);
    friend int compareByAge(const void* a, const void* b);
};

// Function that compares person objects by name
int compareByName(const void* a, const void* b) {
  const Person* p1 = static_cast<const Person*>(a);
  const Person* p2 = static_cast<const Person*>(b);
  if(p1->name > p2->name)
    return 1;
  else if(p1->name < p2->name)
    return -1;
  else
    return 0;
}

// Function that compares person objects by age
int compareByAge(const void* a, const void* b) {
  const Person* p1 = static_cast<const Person*>(a);
  const Person* p2 = static_cast<const Person*>(b);
  if(p1->age > p2->age)
    return 1;
  else if(p1->age < p2->age)
    return -1;
  else
    return 0;
}

int main() {
  vector<Person> personVector;

  Person p1("Peter", 18);
  Person p2("John", 20);
  Person p3("Tom", 21);

  personVector.push_back(p1);
  personVector.push_back(p2);
  personVector.push_back(p3);

  // Use qsort to sort the objects in the container according to name
  qsort(personVector.data(), personVector.size(), sizeof(Person), compareByName);
  cout << "----- Ordered by name -----" << endl;
  for(vector<Person>::iterator it = personVector.begin(); it != personVector.end(); it++)
    (*it).print();

  cout << endl;

  // Use qsort to sort the objects in the container according to age
  qsort(personVector.data(), personVector.size(), sizeof(Person), compareByAge);
  cout << "----- Ordered by age -----" << endl;
  for(vector<Person>::iterator it = personVector.begin(); it != personVector.end(); it++)
    (*it).print();

  return 0;
}
