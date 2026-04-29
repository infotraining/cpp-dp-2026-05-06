#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace Bank
{
    class InsufficientFunds : public std::runtime_error
    {
        const int id_;

    public:
        InsufficientFunds(const std::string& msg, int id)
            : std::runtime_error{msg}
            , id_{id}
        {
        }

        int id() const
        {
            return id_;
        }
    };

    // TODO: Refactor this code using State Pattern

    enum AccountState
    {
        overdraft,
        normal
    };

    class BankAccount
    {
        int id_;
        double balance_;
        AccountState state_;

    protected:
        void update_account_state()
        {
            if (balance_ < 0)
                state_ = overdraft;
            else
                state_ = normal;
        }

        void set_balance(double amount)
        {
            balance_ = amount;
        }

    public:
        BankAccount(int id)
            : id_(id)
            , balance_(0.0)
            , state_(normal)
        {
        }

        void withdraw(double amount)
        {
            assert(amount > 0);

            if (state_ == overdraft)
            {
                throw InsufficientFunds{"Insufficient funds for account #" + std::to_string(id_), id_};
            }
            else // state_ == normal
            {
                balance_ -= amount;

                update_account_state();
            }
        }

        void deposit(double amount)
        {
            assert(amount > 0);

            balance_ += amount;

            update_account_state();
        }

        void pay_interest()
        {
            if (state_ == overdraft)
                balance_ += balance_ * 0.15;
            else
                balance_ += balance_ * 0.05;
        }

        std::string status() const
        {
            std::stringstream strm;
            strm << "BankAccount #" << id_ << "; State: ";

            if (state_ == overdraft)
                strm << "overdraft; ";
            else
                strm << "normal; ";

            strm << "Balance: " << std::to_string(balance_);

            return strm.str();
        }

        double balance() const
        {
            return balance_;
        }

        int id() const
        {
            return id_;
        }
    };
}

#endif
