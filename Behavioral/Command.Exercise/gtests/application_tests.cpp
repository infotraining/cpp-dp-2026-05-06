#include "gmock/gmock.h"

#include "application.hpp"
#include "mocks/mock_command.hpp"
#include "mocks/mock_console.hpp"
#include <memory>

using namespace ::testing;

class ApplicationTests : public Test
{
};

struct ApplicationTests_MainLoop : ApplicationTests
{
    NiceMock<MockConsole> mq_console;
    Application app{mq_console};
    std::shared_ptr<MockCommand> mq_cmd;

    void SetUp() override
    {
        mq_cmd = std::make_shared<NiceMock<MockCommand>>();

        app.add_command("cmd", mq_cmd);
    }
};

TEST_F(ApplicationTests_MainLoop, GetsLineFromInput)
{
    EXPECT_CALL(mq_console, get_line()).WillOnce(Return(Commands::cmd_exit));

    app.run();
}

TEST_F(ApplicationTests_MainLoop, ShowsPromptForCommand)
{
    InSequence s;

    EXPECT_CALL(mq_console, print(Messages::msg_prompt)).Times(1);
    EXPECT_CALL(mq_console, get_line()).Times(1).WillOnce(Return(Commands::cmd_exit));

    app.run();
}

TEST_F(ApplicationTests_MainLoop, ExitBreaksALoop)
{
    EXPECT_CALL(mq_console, get_line()).WillOnce(Return(Commands::cmd_exit));
    EXPECT_CALL(mq_console, get_line())
        .Times(3)
        .WillRepeatedly(Return("cmd"))
        .RetiresOnSaturation();

    app.run();
}

TEST_F(ApplicationTests_MainLoop, ExecutesCommands)
{
    EXPECT_CALL(*mq_cmd, execute());
    EXPECT_CALL(mq_console, get_line())
        .Times(2)
        .WillOnce(Return("cmd"))
        .WillOnce(Return(Commands::cmd_exit));

    app.run();
}

TEST_F(ApplicationTests_MainLoop, UnknownCommandPrintsErrorMesssage)
{
    const std::string cmd = "UNKNOWN";
    const std::string expected_msg = Messages::msg_unknown_cmd + cmd;

    EXPECT_CALL(mq_console, print(_)).WillRepeatedly(Return());
    EXPECT_CALL(mq_console, print(expected_msg)).Times(1).RetiresOnSaturation();        

    InSequence seq;
    EXPECT_CALL(mq_console, get_line()).WillOnce(Return(cmd));
    EXPECT_CALL(mq_console, get_line()).WillOnce(Return(Commands::cmd_exit));
    
    app.run();
}
