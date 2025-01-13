#include <iostream> 
#include <vector> 
#include <fstream> 
#include <string> 
 
 
int main(int argc, char* argv[]) { 
    std::ifstream ifile(argv[1]);
    std::vector<std::string> vec_str; 
    std::string tmpstr;
    auto max_length = 0;

    while(std::getline(ifile, tmpstr)) { 
        vec_str.push_back(tmpstr);
        if (tmpstr.size() > max_length) {
            max_length = tmpstr.size();
        }
    }
    ifile.close(); 

    for (size_t i = 0; i != max_length; ++i) { 
        for (const auto &str : vec_str) { 
            if (i < str.size()) 
                std::cout << str[i]; 
            else 
                std::cout << ' ';
        } 
        std::cout << std::endl; 
    }
}