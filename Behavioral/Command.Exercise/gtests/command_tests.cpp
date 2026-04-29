#include <algorithm>

#include <gtest/gtest.h>

#include "command.hpp"
#include "document.hpp"
#include "mocks/mock_clipboard.hpp"
#include "mocks/mock_console.hpp"

using namespace ::testing;

struct CommandTests : ::testing::Test
{
    Document doc{"abc"};
    NiceMock<MockConsole> mq_console;
};

struct PrintCmd_Execute : CommandTests
{
};

TEST_F(PrintCmd_Execute, PrintsDocumentInConsole)
{
    PrintCmd print_cmd{doc, mq_console};

    EXPECT_CALL(mq_console, print("[abc]")).Times(1);

    print_cmd.execute();
}
//-----------------------------------------------------------------

struct ReversibleCmdTests : CommandTests
{
    CommandHistory cmd_history;
};

struct ClearCmd_Execute : ReversibleCmdTests
{
    ClearCmd clear_cmd;

    ClearCmd_Execute()
        : clear_cmd{doc, cmd_history}
    {
    }
};

TEST_F(ClearCmd_Execute, ClearsDocument)
{
    clear_cmd.execute();

    ASSERT_THAT(doc.text(), StrEq(""));
}

struct ClearCmd_Undo : ClearCmd_Execute
{
    void SetUp() override
    {
        clear_cmd.execute();
    }
};

TEST_F(ClearCmd_Undo, RestoresDocumentState)
{
    auto last_cmd = cmd_history.pop_last_command();
    last_cmd->undo();

    ASSERT_THAT(doc.text(), StrEq("abc"));
}

//-----------------------------------------------------------------

struct AddTextCmd_Execute : ReversibleCmdTests
{
    AddTextCmd add_text_cmd;

    AddTextCmd_Execute()
        : add_text_cmd{doc, mq_console, cmd_history}
    {
    }

    void SetUp() override
    {
        ON_CALL(mq_console, print(_)).WillByDefault(Return());
        EXPECT_CALL(mq_console, get_line()).WillOnce(Return("def"));
    }
};

TEST_F(AddTextCmd_Execute, GetsTextFromConsoleAndAddsToDocument)
{
    add_text_cmd.execute();

    ASSERT_EQ(doc.text(), "abcdef");
}

TEST_F(AddTextCmd_Execute, CommandIsStoredInHistory)
{
    add_text_cmd.execute();

    auto saved_cmd = cmd_history.pop_last_command();

    ASSERT_EQ(typeid(*saved_cmd), typeid(AddTextCmd));
}

//-----------------------------------------------------------------

struct AddTextCmd_Undo : AddTextCmd_Execute
{
    void SetUp() override
    {
        AddTextCmd_Execute::SetUp();

        add_text_cmd.execute();
    }
};

TEST_F(AddTextCmd_Undo, RestoresDocumentState)
{
    auto last_cmd = cmd_history.pop_last_command();
    last_cmd->undo();

    ASSERT_THAT(doc.text(), StrEq("abc"));
}

//-----------------------------------------------------------------

struct ToUpperCmd_Execute : ReversibleCmdTests
{
    ToUpperCmd to_upper_cmd{doc, cmd_history};
};

TEST_F(ToUpperCmd_Execute, ConvertsDocumentCaseToUpper)
{
    to_upper_cmd.execute();

    ASSERT_THAT(doc.text(), StrEq("ABC"));
}

struct ToUpperCmd_Undo : ToUpperCmd_Execute
{
};

TEST_F(ToUpperCmd_Undo, RestoresDocumentState)
{
    to_upper_cmd.execute();

    auto last_cmd = cmd_history.pop_last_command();
    last_cmd->undo();

    ASSERT_THAT(doc.text(), StrEq("abc"));
}

//-----------------------------------------------------------------

struct PasteCmd_Execute : ReversibleCmdTests
{
    NiceMock<MockClipboard> mq_clipboard;
    PasteCmd paste_cmd{doc, mq_clipboard, cmd_history};
};

TEST_F(PasteCmd_Execute, ClipboardContentIsRetrieved)
{
    EXPECT_CALL(mq_clipboard, content()).Times(1).WillOnce(Return("def"));
    paste_cmd.execute();
}

TEST_F(PasteCmd_Execute, ClipboardContentIsConcatenatedToDocument)
{
    ON_CALL(mq_clipboard, content()).WillByDefault(Return("def"));
    paste_cmd.execute();

    ASSERT_THAT(doc.text(), StrEq("abcdef"));
}

//-----------------------------------------------------------------

struct PasteCmd_Undo : PasteCmd_Execute
{
};

TEST_F(PasteCmd_Undo, DocumentStateIsRestored)
{
    ON_CALL(mq_clipboard, content()).WillByDefault(Return("def"));
    paste_cmd.execute();
    ASSERT_THAT(doc.text(), StrEq("abcdef"));

    auto last_cmd = cmd_history.pop_last_command();

    last_cmd->undo();
    ASSERT_THAT(doc.text(), StrEq("abc"));
}

//-----------------------------------------------------------------

struct UndoCmd_Execute : CommandTests
{
    CommandHistory cmd_history;

    UndoCmd undo_cmd{mq_console, cmd_history};
};

struct MockReversibleCommand : ReversibleCommand
{
    MOCK_METHOD0(execute, void());
    MOCK_METHOD0(undo, void());
    MOCK_CONST_METHOD0(clone, ReversibleCommandPtr());
};

TEST_F(UndoCmd_Execute, PopsLastCommandFromHistory)
{
    auto mq_cmd = std::make_unique<MockReversibleCommand>();
    EXPECT_CALL(*mq_cmd, undo()).Times(1).WillOnce(Return());

    cmd_history.record_last_command(std::move(mq_cmd));

    undo_cmd.execute();
}