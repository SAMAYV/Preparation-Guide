// Solution 2: Using Template Arguments
// The critical point is that the calculation is done at compile-time.

#include <iostream>

template<int m, int n>
struct Power{
    static int const value = m * Power<m,n-1>::value;
};

template<int m>
struct Power<m,0>{
   static int const value = 1;
};

int main(){
   std::cout << Power<2,10>::value << std::endl;
}

// Solution 3: Using Template Arguments and Function Arguments
// When we invoke the power<10>(2) function, the argument in () brackets is evaluated at runtime and the argument in <> brackets is evaluated at compile-time. 
// Therefore, we can say that the round brackets are run time arguments and the angle brackets are compile-time arguments.

#include <iostream>

template<int n>
int power(int m){
    return m * power<n-1>(m);
}

template<>
int power<1>(int m){
    return m;
}

template<>
int power<0>(int m){
    return 1;
}

int main(){
    std::cout << power<10>(2) << std::endl;
}