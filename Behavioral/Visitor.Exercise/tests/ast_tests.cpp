#include "ast.hpp"
#include "visitors.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace AST;
using namespace AST::helpers;

TEST_CASE("expression evaluator visitor", "[ast]")
{
    ExpressionEvaluator evaluator;

    SECTION("integer")
    {
        auto expr = integer(4);
        expr->accept(evaluator);

        REQUIRE(evaluator.result() == 4);
    }

    SECTION("addition")
    {
        auto expr = add(integer(1), integer(2));
        expr->accept(evaluator);

        REQUIRE(evaluator.result() == 3);
    }

    SECTION("multiplication")
    {
        auto expr = multiply(integer(2), integer(3));
        expr->accept(evaluator);

        REQUIRE(evaluator.result() == 6);
    }

    SECTION("composite expression")
    {
        auto expr = add(integer(3), multiply(integer(2), integer(5)));

        expr->accept(evaluator);

        REQUIRE(evaluator.result() == 13);
    }
}

TEST_CASE("printing visitor")
{
    // TODO - uncomment tests

    // PrintingVisitor visitor;

    // SECTION("integer")
    // {
    //     auto expr = integer(4);
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "4");
    // }

    // SECTION("addition")
    // {
    //     auto expr = add(integer(1), integer(2));
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(1 + 2)");
    // }

    // SECTION("multiplication")
    // {
    //     auto expr = multiply(integer(2), integer(3));
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(2 * 3)");
    // }

    // SECTION("composite expression")
    // {
    //     auto expr = add(integer(3), multiply(integer(2), integer(5)));

    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(3 + (2 * 5))");
    // }
}
