#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <sstream>


class IOperator {
public:
    virtual void calc(std::stack<double>&) = 0;
    virtual ~IOperator() {};
};


class CCos : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = std::cos(st.top());
        st.pop();
        st.push(tmp);
    }

    static CCos& instance() {
        static CCos m;
        return m;
    }
private:
    CCos() {};
};


class CSin : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = std::sin(st.top());
        st.pop();
        st.push(tmp);
    }

    static CSin& instance() {
        static CSin m;
        return m;
    }
private:
    CSin() {};
};


class CExp : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = std::exp(st.top());
        st.pop();
        st.push(tmp);
    }

    static CExp& instance() {
        static CExp m;
        return m;
    }
private:
    CExp() {};
};


class CLn : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = std::log(st.top());
        st.pop();
        st.push(tmp);
    }

    static CLn& instance() {
        static CLn m;
        return m;
    }
private:
    CLn() {};
};


class CLg : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = std::log10(st.top());
        st.pop();
        st.push(tmp);
    }

    static CLg& instance() {
        static CLg m;
        return m;
    }
private:
    CLg() {};
};


class CSqrt : public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double tmp = st.top();
        st.pop();
        st.push(std::sqrt(tmp));
    }

    static CSqrt& instance() {
        static CSqrt m;
        return m;
    }
private:
    CSqrt() {};
};


class CPow: public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        double y = st.top();
        st.pop();
        st.push(std::pow(x, y));
    }

    static CPow& instance() {
        static CPow m;
        return m;
    }
private:
    CPow() {};
};


class CPlus: public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        double y = st.top();
        st.pop();
        st.push(x + y);
    }

    static CPlus& instance() {
        static CPlus m;
        return m;
    }
private:
    CPlus() {};
};


class CMinus: public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        double y = st.top();
        st.pop();
        st.push(y - x);
    }

    static CMinus& instance() {
        static CMinus m;
        return m;
    }
private:
    CMinus() {};
};


class CMult: public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        double y = st.top();
        st.pop();
        st.push(x * y);
    }

    static CMult& instance() {
        static CMult m;
        return m;
    }
private:
    CMult() {};
};


class CDiv: public IOperator {
public:
    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        double y = st.top();
        st.pop();
        st.push(y / x);
    }

    static CDiv& instance() {
        static CDiv m;
        return m;
    }
private:
    CDiv() {};
};


class CPut: public IOperator {
public:
    std::stack<double>& tmp_st;
    CPut(std::stack<double>& stack)
    : tmp_st(stack) {};

    void calc(std::stack<double>& st) override {
        double x = st.top();
        st.pop();
        tmp_st.push(x);
    }

    // static CGet& instance() {
    //     static CGet m;
    //     return m;
    // }
// private:
};


class CGet: public IOperator {
public:
    std::stack<double>& tmp_st;
    CGet(std::stack<double>& stack)
    : tmp_st(stack){};

    void calc(std::stack<double>& st) override {
        double x = tmp_st.top();
        tmp_st.pop();
        st.push(x);
    }
};


class CPutGet {
public:
    std::stack<double> tmp_st;
    CPut p;
    CGet g;

    static CPutGet& instance() {
        static CPutGet m;
        return m;
    }
private:
    CPutGet() : p(tmp_st), g(tmp_st) {};
};


bool check_if_number(const std::string& word) {
    try {
        std::stod(word);
        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
}


void printStack(std::stack<double> st) {
    // Используем временный стек для вывода значений
    std::stack<double> temp;

    // Пока основной стек не пустой
    while (!st.empty()) {
        // Получаем верхний элемент
        double value = st.top();
        std::cout << value << std::endl; // Выводим значение

        // Перемещаем элемент во временный стек
        temp.push(value);
        st.pop(); // Удаляем элемент из основного стека
    }

    // Восстанавливаем оригинальный стек
    while (!temp.empty()) {
        st.push(temp.top());
        temp.pop();
    }
}


double process(auto n, std::vector<std::string> words, std::map<std::string, IOperator*>& table) {
    std::stack<double> st;
    for(size_t i = 0; i != n; ++i) {
        if (check_if_number(words[i]))
            st.push(std::stod(words[i]));
        else
            table[words[i]]->calc(st);
    }
    return st.top();
    // printStack(st);
}


int main(int argc, char* argv[]) {
    // std::cout << argc << " " << argv[1] << std::endl;
    std::map<std::string, IOperator*> op_table;
    op_table["cos"] = &CCos::instance();
    op_table["sin"] = &CSin::instance();
    op_table["exp"] = &CExp::instance();
    op_table["ln"] = &CLn::instance();
    op_table["lg"] = &CLg::instance();
    op_table["sqrt"] = &CSqrt::instance();
    op_table["pow"] = &CPow::instance();
    op_table["+"] = &CPlus::instance();
    op_table["-"] = &CMinus::instance();
    op_table["*"] = &CMult::instance();
    op_table["/"] = &CDiv::instance();
    op_table["put"] = &CPutGet::instance().p;
    op_table["get"] = &CPutGet::instance().g;

    // process(argc - 1, argv + 1, op_table);

    std::string input = argv[1];
    std::stringstream ss(input);
    std::vector<std::string> operations;
    std::string t;
    char del = ' ';

    while (getline(ss, t, del))
        operations.push_back(t);

    // std::cout << operations.size() << "\n";


    // for (size_t i = 0; i != operations.size(); ++i) {
    //     std::cout << operations[i] << "\n";
    // }

    double result = process(operations.size(), operations, op_table);
    std::cout << result << "\n";
}