#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "clipboard.hpp"
#include "console.hpp"
#include "document.hpp"
#include <memory>
#include <stack>

namespace Commands
{
    constexpr auto cmd_exit = "EXIT";
}

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

using CommandSharedPtr = std::shared_ptr<Command>;
using CommandPtr = std::unique_ptr<Command>;

class ReversibleCommand : public Command
{
public:
    virtual void undo() = 0;
    virtual std::unique_ptr<ReversibleCommand> clone() const = 0;
};

using ReversibleCommandPtr = std::unique_ptr<ReversibleCommand>;

template <typename Cmd, typename BaseCommand = ReversibleCommand>
class CloneableCommand : public BaseCommand
{
public:
    std::unique_ptr<ReversibleCommand> clone() const override
    {
        return std::make_unique<Cmd>(static_cast<Cmd const&>(*this));
    }
};

class CommandHistory
{
    std::stack<ReversibleCommandPtr> history_;

public:
    void record_last_command(ReversibleCommandPtr cmd)
    {
        history_.push(std::move(cmd));
    }

    ReversibleCommandPtr pop_last_command()
    {

        if (history_.empty())
            throw std::out_of_range("Command history is empty");
        auto last_cmd = std::move(history_.top());
        history_.pop();

        return last_cmd;
    }
};

template <typename CommandType, typename CommandBaseType = ReversibleCommand>
class ReversibleCommandBase : public CloneableCommand<CommandType, CommandBaseType>
{
    CommandHistory& history_;

public:
    ReversibleCommandBase(CommandHistory& history)
        : history_{history}
    {
    }

    void execute() final override
    {
        do_save_state();
        history_.record_last_command(this->clone());
        do_execute();
    }

    void undo() final override
    {
        do_undo();
    }

protected:
    virtual void do_save_state() = 0;
    virtual void do_execute() = 0;
    virtual void do_undo() = 0;
};

//--------------------------------------------------------------------------------
// Print command
class PrintCmd : public Command
{
public:
    PrintCmd(Document& doc, Console& console)
        : doc_{doc}
        , console_{console}
    {
    }

    void execute() override
    {
        console_.print("[" + doc_.text() + "]");
    }

private:
    Document& doc_;
    Console& console_;
};

//--------------------------------------------------------------------------------
// Clear command
class ClearCmd : public ReversibleCommandBase<ClearCmd>
{
public:
    ClearCmd(Document& doc, CommandHistory& history)
        : ReversibleCommandBase{history}
        , doc_{doc}
    {
    }

protected:
    void do_save_state() override
    {
        memento_ = doc_.create_memento();
    }

    void do_execute() override
    {
        doc_.clear();
    }

    void do_undo() override
    {
        doc_.set_memento(memento_);
    }

private:
    Document& doc_;
    Document::Memento memento_;
};

//--------------------------------------------------------------------------------
// ToUpper command
class ToUpperCmd : public ReversibleCommandBase<ToUpperCmd>
{
public:
    ToUpperCmd(Document& doc, CommandHistory& history)
        : ReversibleCommandBase{history}
        , doc_{doc}
    {
    }

protected:
    void do_save_state() override
    {
        memento_ = doc_.create_memento();
    }

    void do_execute() override
    {
        doc_.to_upper();
    }

    void do_undo() override
    {
        doc_.set_memento(memento_);
    }

private:
    Document& doc_;
    Document::Memento memento_;
};

//--------------------------------------------------------------------------------
// Paste command
class PasteCmd : public ReversibleCommandBase<PasteCmd>
{
public:
    PasteCmd(Document& doc, Clipboard& clipboard_, CommandHistory& history)
        : ReversibleCommandBase(history)
        , doc_(doc)
        , clipboard_(clipboard_)
    {
    }

protected:
    void do_save_state() override
    {
        prev_length_ = doc_.length();
    }

    void do_execute() override
    {
        doc_.add_text(clipboard_.content());
    }

    void do_undo() override
    {
        size_t count = doc_.length() - prev_length_;
        doc_.replace(prev_length_, count, "");
    }

private:
    Document& doc_;
    Clipboard& clipboard_;

    size_t prev_length_{};
};

//--------------------------------------------------------------------------------
// Undo command
class UndoCmd : public Command
{
public:
    UndoCmd(Console& console, CommandHistory& history)
        : console_{console}
        , history_(history)
    {
    }

    void execute() override
    {
        try
        {
            auto last_cmd = history_.pop_last_command();
            last_cmd->undo();
        }
        catch (const std::out_of_range&)
        {
            console_.print("Command history is empty. Nothing to undo.");
        }
    }

private:
    Console& console_;
    CommandHistory& history_;
};

//--------------------------------------------------------------------------------
// AddText command
class AddTextCmd : public ReversibleCommandBase<AddTextCmd>
{
public:
    AddTextCmd(Document& doc, Console& console, CommandHistory& history)
        : ReversibleCommandBase(history)
        , doc_{doc}
        , console_{console}
    {
    }

protected:
    void do_save_state() override
    {
        prev_length_ = doc_.length();
    }

    void do_execute() override
    {
        console_.print("Write text: ");
        auto txt = console_.get_line();
        doc_.add_text(txt);
    }

    void do_undo() override
    {
        auto count = doc_.length() - prev_length_;
        doc_.replace(prev_length_, count, "");
    }

private:
    Document& doc_;
    Console& console_;
    size_t prev_length_{};
};

//--------------------------------------------------------------------------------
// TODO - ToLower command
class ToLowerCmd
{
};

//--------------------------------------------------------------------------------
// TODO - Copy command
class CopyCmd
{
};

#endif // COMMAND_HPP
