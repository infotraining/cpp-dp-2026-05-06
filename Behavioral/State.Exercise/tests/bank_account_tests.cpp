#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <string>

#include "bank_account.hpp"

using namespace std;
using namespace Bank;

class BankAccountStatusBuilder
{
    int id_;
    double balance_;
    std::string state_;

public:
    BankAccountStatusBuilder(int id)
        : id_{id}
        , balance_{0.0}
        , state_{"normal"}
    {
    }

    BankAccountStatusBuilder& with_balance(double balance)
    {
        balance_ = balance;

        return *this;
    }

    BankAccountStatusBuilder& with_state(const std::string& state)
    {
        state_ = state;

        return *this;
    }

    std::string status() const
    {
        return "BankAccount #" + std::to_string(id_) + "; State: " + state_ + "; Balance: " + std::to_string(balance_);
    }
};

TEST_CASE("BankAccount in initial state", "[init]")
{
    BankAccount ba{1};

    SECTION("id is assigned")
    {
        REQUIRE(ba.id() == 1);
    }

    SECTION("balance is zero")
    {
        REQUIRE(ba.balance() == 0);
    }

    SECTION("account is in normal state")
    {
        BankAccountStatusBuilder status_bld{1};

        REQUIRE(ba.status() == status_bld.status());
    }
}

SCENARIO("BankAccount in normal state")
{
    GIVEN("BankAccount in normal state")
    {
        BankAccount ba{1};
        ba.deposit(100);

        WHEN("making a deposit")
        {
            ba.deposit(100);

            THEN("balance is increased")
            {
                REQUIRE(ba.balance() == 200.0);
            }

            AND_THEN("status is normal")
            {
                BankAccountStatusBuilder sb{1};

                REQUIRE(ba.status() == sb.with_balance(200.0).with_state("normal").status());
            }
        }

        WHEN("withdrawing an amount lower than balance")
        {
            ba.withdraw(50.0);

            THEN("balance is updated")
            {
                REQUIRE(ba.balance() == 50.0);
            }

            AND_THEN("status is unchanged")
            {
                BankAccountStatusBuilder sb{1};

                REQUIRE(ba.status() == sb.with_balance(50.).with_state("normal").status());
            }
        }

        WHEN("withdrawing an amount exceeding balance")
        {
            ba.withdraw(200.0);

            THEN("balance is updated")
            {
                REQUIRE(ba.balance() == -100.0);
            }

            AND_THEN("status is changed to overdraft")
            {
                BankAccountStatusBuilder sb{1};

                REQUIRE(ba.status() == sb.with_balance(-100.0).with_state("overdraft").status());
            }
        }

        WHEN("paying interest rates")
        {
            ba.pay_interest();

            THEN("interest rates are added to balance")
            {
                REQUIRE(ba.balance() == 105.0);
            }
        }
    }
}

SCENARIO("BankAccount in overdraft state")
{
    GIVEN("BankAccount in overdraft state")
    {
        BankAccount ba{1};
        ba.withdraw(100);

        BankAccountStatusBuilder sb{1};
        REQUIRE(ba.status() == sb.with_balance(-100.0).with_state("overdraft").status());

        WHEN("making a deposit smaller than debt")
        {
            ba.deposit(50);

            THEN("balance is increased")
            {
                REQUIRE(ba.balance() == -50.0);
            }

            AND_THEN("status is unchanged")
            {
                REQUIRE(ba.status() == sb.with_balance(-50.0).with_state("overdraft").status());
            }
        }

        WHEN("making a deposit larger than debt")
        {
            ba.deposit(200.0);

            THEN("balance is updated")
            {
                REQUIRE(ba.balance() == 100.0);
            }

            AND_THEN("status is changed to normal")
            {
                REQUIRE(ba.status() == sb.with_balance(100.).with_state("normal").status());
            }
        }

        WHEN("withdrawing an amount")
        {
            THEN("exception is thrown")
            {
                REQUIRE_THROWS_WITH(ba.withdraw(1.0), "Insufficient funds for account #1");
            }
        }

        WHEN("paying interest rates")
        {
            ba.pay_interest();

            THEN("interest rates are subrtracted from balance")
            {
                REQUIRE(ba.balance() == Catch::Approx(-115.0));
            }
        }
    }
}