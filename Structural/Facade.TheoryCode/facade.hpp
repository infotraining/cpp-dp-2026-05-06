#ifndef FACADE_HPP_
#define FACADE_HPP_

#include <iostream>
#include <memory>
#include <string>

namespace EmailLib
{
    using IpAddress = std::string;
    using Port = int;
    using User = std::string;
    using Password = std::string;

    struct MessageBody
    {
        std::string body;
    };

    struct MessageTitle
    {
        std::string title;
    };

    using EmailAddress = std::string;

    class SmtpServer
    {
    public:
        bool connect(const IpAddress& address, Port port)
        {
            std::cout << "Connecting to " << address << ":" << port << "...\n";
            return true;
        }

        bool authenticate(const User& user, const Password& password)
        {
            std::cout << "Authenticating user: " << user << "\n";

            return true;
        }

        void send_email(const EmailAddress& from, const EmailAddress& to, const MessageTitle& title, const MessageBody& body)
        {
            std::cout << "Sending email...\n";
            std::cout << "From: " << from << "\n";
            std::cout << "To: " << to << "\n";
            std::cout << "Title: " << title.title << "\n";
            std::cout << "Body: " << body.body << "\n";
        }
    };
} // namespace EmailLib

namespace Facade
{
    struct Email
    {
        std::string title;
        std::string body;
    };

    class MailerService
    {
        struct MailBuilder
        {
            std::string title_;
            std::string body_;

            MailBuilder& add_title(std::string title)
            {
                title_ = std::move(title);
                return *this;
            }

            MailBuilder& add_body(std::string body)
            {
                body_ = std::move(body);
                return *this;
            }

            operator Email()
            {
                return Email{title_, body_};
            }
        };

    public:
        MailBuilder create_email()
        {
            return MailBuilder();
        }

        void send_email(std::string from, std::string to, const Email& email)
        {
            using namespace EmailLib;

            SmtpServer smtp_server;
            smtp_server.connect("124.44.33.44", 655);

            MessageBody body{email.body};
            MessageTitle title{email.title};

            smtp_server.authenticate("Jan.Kowalski", "password");
            smtp_server.send_email(from, to, title, body);
        }
    };
} // namespace Facade

#endif /*FACADE_HPP_*/
