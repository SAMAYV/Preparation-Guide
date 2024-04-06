/*
The process of substituting the template parameters with the template arguments is called instantiation.

In contrast to a function template, a class template is not capable of automatically deriving the template parameters. 
Each template argument must be explicitly specified. This restriction no longer exists with C++17.
*/

// Let’s have a look at the declaration of the method template inside the class and its definition outside the class

template <class T, int N> 
class Array{
public:
  template <class T2>
  Array<T, N>& operator = (const Array<T2, N>& a); ...
};

template<class T, int N>
template<class T2>
  Array<T, N>& Array<T, N>::operator = (const Array<T2, N>& a{
  ...
  }

// The destructor and copy constructor cannot be templates.

-------------------------------------------------------------------------------------------------------------------------------

template <typename T>
struct Base{
  void func(){ ...
};

template <typename T> 
struct Derived: Base<T>{
  void func2(){
  func();       // ERROR
  }
}

// If a class or a class template inherits from a class template, the methods of the base class or base class template 
// are not automatically available in the derived class.

/*
3 Solutions:
    Qualification via this pointer: this->func()
    Introducing the name using Base<T>::func
    Full qualified access Base<T>::func()
*/

-------------------------------------------------------------------------------------------------------------------------------

// Alias Templates
template <typename T, int Line, int Col> 
class Matrix{
...
};

template <typename T, int Line>
using Square = Matrix<T, Line, Line>;

template <typename T, int Line>
using Vector = Matrix<T, Line, 1>;

Matrix<int, 5, 3> ma;
Square<double, 4> sq;
Vector<char, 5> vec;

-------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

class Account{
public:
  explicit Account(double amount=0.0): balance(amount){}

  void deposit(double amount){
    balance+= amount;
  }

  void withdraw(double amount){
    balance-= amount;
  }
  
  double getBalance() const{
    return balance;
  }

private:
  double balance;
};

template <typename T, int N>
class Array{

public:
  Array()= default;
  int getSize() const;

private:
  T elem[N];
};

template <typename T, int N>
int Array<T,N>::getSize() const {
  return N;
}

int main(){

  std::cout << std::endl;

  Array<double,10> doubleArray;
  std::cout << "doubleArray.getSize(): " << doubleArray.getSize() << std::endl;

  Array<Account,1000> accountArray;
  std::cout << "accountArray.getSize(): " << accountArray.getSize() << std::endl;

  std::cout << std::endl;
}

-------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

template <typename T>
class Base{
public:
  void func1() const {
    std::cout << "func1()" << std::endl;
  }
  void func2() const {
    std::cout << "func2()" << std::endl;
  }
  void func3() const {
    std::cout << "func3()" << std::endl;
  }
};

template <typename T>
class Derived: public Base<T>{
public:
  using Base<T>::func2;
  
  void callAllBaseFunctions(){
    this->func1();
    func2();
    Base<T>::func3();
  }
};

int main(){
  std::cout << std::endl;

  Derived<int> derived;
  derived.callAllBaseFunctions();

  std::cout << std::endl;
}

-------------------------------------------------------------------------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T, int N>
class Array{

public:
  Array()= default;

  template <typename T2>
  Array<T, N>& operator=(const Array<T2, N>& arr){
    elem.clear();
	  elem.insert(elem.begin(), arr.elem.begin(), arr.elem.end());
	  return *this;
  }

  int getSize() const;

  std::vector<T> elem;
};

template <typename T, int N>
int Array<T, N>::getSize() const {
  return N;
}

int main(){

  Array<double, 10> doubleArray{};
  Array<int, 10> intArray{};

  doubleArray= intArray;

  Array<std::string, 10> strArray{};
  Array<int, 100> bigIntArray{};

  // doubleArray= strArray;            // ERROR: cannot convert ‘const std::basic_string<char>’ to ‘double’
  // doubleArray= bigIntArray;         // ERROR: no match for ‘operator=’ in ‘doubleArray = bigIntArray
}