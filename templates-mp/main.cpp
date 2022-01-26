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


/* True type and False type*/
struct true_type {
    static const bool value = true;
};

struct false_type {
    static const bool value = false;
};


/* Type traits for container*/
template<typename T>
struct is_type_container : false_type {};

template<typename T>
struct is_type_container<std::vector<T>> : true_type {};
template<typename T>
struct is_type_container<std::set<T>> : true_type {};


/* Type traits for user defined types with toString method */
template<typename T>
struct has_to_string : false_type {};

template<>
struct has_to_string<House> : true_type {};
template<>
struct has_to_string<Person> : true_type {};
template<>
struct has_to_string<Animal> : true_type {};


/* Type traits for built in types */
template<typename T>
struct is_built_in_type :false_type {};

template<>
struct is_built_in_type<int> : true_type {};
template<>
struct is_built_in_type<float> : true_type {};


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

template<typename T>
void LOG(const T& t) {
    std::cout << ToString(t) << std::endl;
}

int main(int argc, const char * argv[]) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    Person p;
    Animal a;
    float pi = 3.14f;

    LOG(nums);

    LOG(p);

    LOG(a);

    LOG(pi);
    
    return 0;
}
