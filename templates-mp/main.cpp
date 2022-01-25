//
//  main.cpp
//
//  Created by Siddharth Bhasin
//

#include <iostream>
#include <vector>
#include <set>

/* enable_if definitions */
template<bool B, class T>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };


/* User defined types with toString member function */
class Person {
public:
    std::string toString() const {
        return "Person";
    }
};

class Animal {
public:
    std::string toString() const {
        return "Animal";
    }
};

class House {
public:
    std::string toString() const {
        return "House";
    }
};


/* Type traits for container*/
template<typename T>
struct is_type_container {
    static const bool value = false;
};
template<typename T>
struct is_type_container<std::vector<T>> {
    static const bool value = true;
};
template<typename T>
struct is_type_container<std::set<T>> {
    static const bool value = true;
};


/* Type traits for user defined types with toString method */
template<typename T>
struct has_to_string {
    static const bool value = false;
};
template<>
struct has_to_string<House> {
    static const bool value = true;
};
template<>
struct has_to_string<Person> {
    static const bool value = true;
};
template<>
struct has_to_string<Animal> {
    static const bool value = true;
};


/* Type traits for built in types */
template<typename T>
struct is_built_in_type {
    static const bool value = false;
};
template<>
struct is_built_in_type<int> {
    static const bool value = true;
};
template<>
struct is_built_in_type<float> {
    static const bool value = true;
};

/* ToString definitions for each type */

// Built-in types
template<typename T>
std::string ToString(const T& x,
        typename enable_if<is_built_in_type<T>::value, T>::type* = 0) {
    return std::to_string(x);
}

// User-defined types
template<typename T>
std::string ToString(const T& x,
        typename enable_if<has_to_string<T>::value, T>::type* = 0) {
    return x.toString();
}

// Collection types
template<typename T>
std::string ToString(const T& x,
        typename enable_if<is_type_container<T>::value, T>::type* = 0) {
    if(x.empty()) return "[]";
    std::string result = "[";
    for(auto& ele: x) {
        result += ToString(ele) + ",";
    }
    result.back() = ']';
    return result;
}

int main(int argc, const char * argv[]) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << ToString(nums) << std::endl;
    
    Person p;
    Animal a;
    std::cout << ToString(p) << " " << ToString(a) << std::endl;
    
    float pi = 3.14f;
    
    std::cout << ToString(pi) << "\n";
    
    return 0;
}
