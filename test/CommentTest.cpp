#include "AST/Comment.h"

#include "catch.hpp"

using namespace elma;

namespace {
std::string trimComment(CommentKind kind, const std::string& s)
{
    auto comment = std::make_shared<Comment>(Location{}, kind, s);
    return comment->getText();
}
} // end of anonymous namespace

TEST_CASE("comments", "[parser]")
{
    SECTION("comment")
    {
        REQUIRE(trimComment(CommentKind::Line, "// Hello world!") == "Hello world!");
        REQUIRE(trimComment(CommentKind::Line, "//// Hello world! \t  \t ") == "// Hello world!");
        REQUIRE(trimComment(CommentKind::Block, "/* Hello world! \t  \t */") == "Hello world!");
        REQUIRE(trimComment(CommentKind::Block, "/* Hello \t \nworld! \t */") == "Hello\nworld!");
    }
}
