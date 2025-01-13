#include <iostream>


template<int A, int B, int Y1, int Y2, unsigned N>
struct fibonachi {
    static const int64_t value = A * fibonachi<A, B, Y1, Y2, N-1>::value + B * fibonachi<A, B, Y1, Y2, N-2>::value;
};

// template<int A, int B, int Y1, int Y2>
// struct fibonachi<A, B, Y1, Y2, 0> {
//     static const int64_t value = 0;
// };

template<int A, int B, int Y1, int Y2>
struct fibonachi<A, B, Y1, Y2, 1> {
    static const int64_t value = Y1;
};

template<int A, int B, int Y1, int Y2>
struct fibonachi<A, B, Y1, Y2, 2> {
    static const int64_t value = Y2;
};


int main(int argc, char* argv[]) {
    std::cout << fibonachi<A_VALUE, B_VALUE, Y1_VALUE, Y2_VALUE, N_VALUE>::value << std::endl;
}


// #include <iostream>


// template<size_t N>
// struct fibonachi {
//     static const int64_t value = A_VALUE * fibonachi<N-1>::value + B_VALUE * fibonachi<N-2>::value;
// };

// template<>
// struct fibonachi<0> {
//     static const int64_t value = Y1_VALUE;
// };

// template<>
// struct fibonachi<1> {
//     static const int64_t value = Y2_VALUE;
// };

// int main(int argc, char* argv[]) {
//     std::cout << fibonachi<N_VALUE>::value << std::endl;
// }