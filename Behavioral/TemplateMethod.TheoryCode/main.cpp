#include "template_method.hpp"

using namespace std;


void login_user(const User& user, AuthenticationService& authentication_service)
{
    if (authentication_service.login(user))
        std::cout << user.username << " logged in...\n";
    else
        std::cout << user.username << " NOT logged in...\n";
}

int main()
{
    User user{"Jan Kowalski", "jan.kowalski@email.com", "+48 800-22-33-22"};

    DefaultAuthenticationService sms_auth_service;
    login_user(user, sms_auth_service);

    std::cout << "\n";

    MailerAuthenticationService email_auth_service;
    login_user(user, email_auth_service);
};


/* 

Example:

- https://github.com/google/googletest/blob/master/googletest/include/gtest/gtest.h
- https://github.com/google/googletest/blob/master/googletest/src/gtest.cc

*/