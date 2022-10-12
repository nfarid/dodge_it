
#include "util/project_info.hpp"

#include <iostream>

int main(int argc, char** argv) {
    for(int i=0; i<argc; ++i)
        std::cout<<argv[i]<<std::endl;
    std::cout<<Util::projectName()<<std::endl;
    std::cout<<Util::projectVersion()<<std::endl;
    return 0;
}
