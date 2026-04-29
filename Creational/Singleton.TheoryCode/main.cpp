#include "singleton.hpp"
#include <iostream>

using namespace std;

int main()
{
    Singleton::instance().do_something();

    Singleton& singleObject = Singleton::instance();
    singleObject.do_something();
}
