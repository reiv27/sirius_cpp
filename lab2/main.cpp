#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>


class Poly {
public:
    std::vector<double> p;

    Poly(std::vector<double> vec);

    size_t size() const;
    std::ostream& dump(std::ostream& os) const;
    void remove_zeros();

    Poly& operator+=(const Poly& x);
    Poly& operator-=(const Poly& x);
    Poly& operator*=(const Poly& x);
    Poly& operator/=(const Poly& x);
    Poly& operator%=(const Poly& x);

    Poly& count_expr(const std::string& file);

private:
    size_t sz;
};


Poly::Poly(std::vector<double> vec)
: p{vec}, sz{vec.size()} {
    // remove_zeros();
}


size_t Poly::size() const {
    return sz;
};


std::ostream& Poly::dump(std::ostream& os) const {
    // os << "Polynom: [";
    for(auto i = 0; i < p.size(); ++i) {
        if (i == p.size()-1) {
            os << p[i];
            continue;
        }
        // os << p[i] << ", ";
        os << p[i] << " ";
    }
    // os << "]" << "\n";
    os << "\n";
    return os;
}


std::ostream& operator<<(std::ostream& os, const Poly& x) {
    return x.dump(os);
}


void Poly::remove_zeros() {
    double e = 1e-10;
    while (!p.empty() && fabs(p.back()) < e) {
        p.pop_back();
        sz -= 1;
    }
}


Poly& Poly::operator+=(const Poly& x) {
    if (sz >= x.size()) {
        for(auto i = 0; i < x.size(); ++i) {
            p[i] += x.p[i];
        }
    }
    else {
        Poly tmp(p);
        p = x.p;
        sz = x.size();
        for(auto i = 0; i < tmp.size(); ++i) {
            p[i] += tmp.p[i];
        }
    }
    remove_zeros();
    return *this;
};


Poly& Poly::operator-=(const Poly& x) {
    if (sz >= x.size()) {
        for(auto i = 0; i < x.size(); ++i) {
            p[i] -= x.p[i];
        }
    }
    else {
        Poly tmp(p);
        p = x.p;
        sz = x.size();
        for(auto i = 0; i < sz; ++i) {
            p[i] = -p[i];
        }
        for(auto i = 0; i < tmp.size(); ++i) {
            p[i] += tmp.p[i];
        }
    }
    // remove_zeros();
    return *this;
};


Poly& Poly::operator*=(const Poly& x) {
    Poly tmp(p);
    sz += x.size() - 1;
    p = std::vector<double>(sz, 0);
    for(auto i = 0; i < tmp.size(); ++i) {
        for(auto j = 0; j < x.size(); ++j) {
            p[i+j] += tmp.p[i] * x.p[j]; 
        }
    }
    remove_zeros();
    return *this;
};


Poly& Poly::operator/=(const Poly& x) {
    Poly tmp(p);
    sz = p.size() - x.p.size() + 1;
    p = std::vector<double>(sz, 0);
    for(int i = sz-1; i > -1; --i) {
        p[i] = tmp.p.back() / x.p.back();

        // std::vector<double> y_vec(tmp.size(), 0);
        // std::cout << "vector y_vec size = " << y_vec.size() << std::endl;
        Poly y(std::vector<double>(tmp.size(), 0));
        // std::cout << "poly y size = " << y.size() << std::endl;
        // y.print();
        for(auto j = 0; j < x.size(); ++j) {
            y.p[i+j] = x.p[j] * p[i];
            // std::cout << "i=" << i << " j=" << j << std::endl;
            // std::cout << y.p[i+j] << " = " << x.p[j]<< " * " << p[i] << std::endl;
        }
        tmp -= y;
        tmp.remove_zeros();
    }
    return *this;
};


Poly& Poly::operator%=(const Poly& x) {
    Poly tmp(p);
    sz = p.size() - x.p.size() + 1;
    p = std::vector<double>(sz, 0);
    for(int i = sz-1; i > -1; --i) {
        p[i] = tmp.p.back() / x.p.back();
        Poly y(std::vector<double>(tmp.size(), 0));
        for(auto j = 0; j < x.size(); ++j) {
            y.p[i+j] = x.p[j] * p[i];
        }
        tmp -= y;
        tmp.remove_zeros();
    }
    p = tmp.p;
    sz = tmp.size();
    return *this;
};


Poly operator+(const Poly& x, const Poly& y) {
    Poly tmp(x);
    return tmp += y;
}
Poly operator-(const Poly& x, const Poly& y) {
    Poly tmp(x);
    return tmp -= y;
}
Poly operator*(const Poly& x, const Poly& y) {
    Poly tmp(x);
    return tmp *= y;
}
Poly operator/(const Poly& x, const Poly& y) {
    Poly tmp(x);
    return tmp /= y;
}
Poly operator%(const Poly& x, const Poly& y) {
    Poly tmp(x);
    return tmp %= y;
}


Poly& Poly::count_expr(const std::string& file) {
    std::ifstream input(file);
    std::vector<std::vector<double>> polynoms = {{}, {}, {}, {}, {}};
    std::string line;
    int line_id = 0;

    while(std::getline(input, line)) {
        std::stringstream ss(line);
        std::string t;
        char del = ',';

        while (getline(ss, t, del))
            polynoms[line_id].push_back(std::stod(t));
        ++line_id;
    }

    Poly p1(polynoms[0]);
    p1.remove_zeros();
    Poly p2(polynoms[1]);
    p2.remove_zeros();
    Poly p3(polynoms[2]);
    p3.remove_zeros();
    Poly p4(polynoms[3]);
    p4.remove_zeros();
    Poly p5(polynoms[4]);
    p5.remove_zeros();

    *this = ((p1 + p2) * p3 - p4) % p5;

    return *this;
}


int main(int argc, char* argv[]) {
    std::string input_file = argv[1];
    // count_expr(input_file);
    // Poly a({5.1, 2.0, 3.5});
    // Poly b({2.0, 4.0, 6.0, 1.0});
    // Poly c({1.1, 3.0});
    // Poly d({2.0, 4.0, -6.0, -1.0});
    // Poly e({1.0, 0.0});
    // Poly f({5.0, 3.0, 1.0});
    // Poly g({2.0, 1});
    // Poly h({4.0, 2.0, 1.0});
    // Poly p1({3, 5});
    // Poly p2({0, 0.5});
    // Poly p3({1, 1});
    // Poly p4({1.5, 3, 6});
    // Poly p5({2, 1});
    // Poly expr({});
    
    // std::cout << "p1: ";
    // p1.print();
    // std::cout << "p2: ";
    // p2.print();
    // std::cout << "p3: ";
    // p3.print();
    // std::cout << "p4: ";
    // p4.print();
    // std::cout << "p5: ";
    // p5.print();

    // expr = ((p1 + p2) * p3 - p4) % p5;
    // expr.print();
    // std::vector<std::vector<double>> vec = {{}, {}, {}, {}, {}};
    // vec[0].push_back(5.0);
    // std::cout << vec[0][0];
    Poly result({});
    std::cout << result.count_expr(input_file);
}