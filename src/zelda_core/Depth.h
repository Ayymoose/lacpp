#pragma once

// Z-ordering is implemented through a std::multiset
// Whenever a Renderable is added to the set, it uses the m_depth
// value to determine it's order
// Given that its internal representation is a sorted binary tree
// we don't need to sort it

// Higher depth = Rendered later on (on top of everything else)
// Lower depth  = Renderer earlier on (everything is renderer on top of this)

namespace zelda::core
{
enum class ZOrdering
{
    BACKGROUND = 1,
    BACKGROUND_OBJECT,
    ENEMY,
    PLAYER,
    INVENTORY,
    WORLDMAP,
    DIALOGUE
};
} // namespace zelda::core