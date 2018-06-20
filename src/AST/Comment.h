#pragma once

#include "Basic/Location.h"
#include <string>

namespace elma {

enum class CommentKind {
    Block,
    Line,
};

class Comment final : public std::enable_shared_from_this<Comment> {
private:
    Location location;
    CommentKind kind;
    std::string text;

public:
    Comment(Location loc, CommentKind kind, const std::string& text);

    Location getLocation() const;

    CommentKind getKind() const;

    std::string getText() const;

    std::string dump() const;
};

} // namespace elma
