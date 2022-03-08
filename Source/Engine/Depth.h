#pragma once

// Z-ordering is implemented through a std::multiset
// Whenever a Renderable is added to the set, it uses the m_depth
// value to determine it's order
// Given that its internal representation is a sorted binary tree
// we don't need to sort it

// Higher depth = Rendered later on (on top of everything else)
// Lower depth  = Renderer earlier on (everything is renderer on top of this)

namespace Zelda
{
    enum ZOrdering
    {
        // Background tiles
        ZD_DEPTH_BACKGROUND = 1,
        // Background objects
        ZD_DEPTH_BACKGROUND_OBJECT,
        // Enemies
        ZD_DEPTH_ENEMY,
        // Player
        ZD_DEPTH_PLAYER,
        // Inventory
        ZD_DEPTH_INVENTORY,
        // Worldmap
        ZD_DEPTH_WORLDMAP,
        // Dialogue
        ZD_DEPTH_DIALOGUE
    };
}