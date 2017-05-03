#pragma once

struct true_type {};
struct false_type {};

template<typename E1, typename E2>
struct binary_traits {
public:
    // binary_traits<E1, E2>::type 
    typedef double binary_traits<int, double>::value_type;
    typedef double binary_traits<double, double>::value_type;
    typedef double binary_traits<double, int>::value_type;


    
private:

};


