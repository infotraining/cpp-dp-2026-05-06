#include "facade.hpp"

void sending_email_without_facade()
{
    using namespace EmailLib;

    SmtpServer smtp_server;
    smtp_server.connect("124.44.33.44", 655);

    MessageBody body{"Nobody expects the Spanish Inqusition"};
    MessageTitle title{"No facade"};

    smtp_server.authenticate("Jan.Kowalski", "password");
    smtp_server.send_email("admin@infotraining.pl", "user@infotraining.pl", title, body);
}

void sending_email_using_facade()
{
    using namespace Facade;

    MailerService mailer;

    Email email = mailer.create_email()
                    .add_title("Facade")
                    .add_body("And now something completely different");

    mailer.send_email("admin@infotraining.pl", "user@infotraining.pl", email);
}

int main()
{
    sending_email_without_facade();

    std::cout << "\n-------------\n";

    sending_email_using_facade();
}
