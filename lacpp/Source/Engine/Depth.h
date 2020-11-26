#pragma once

// Z-ordering is implemented through a std::multiset
// Whenever a Renderable is added to the set, it uses the m_depth
// value to determine it's order
// Given that its internal representation is a sorted binary tree
// we don't need to sort it

// Higher depth = Rendered later on (on top of everything else)
// Lower depth  = Renderer earlier on (everything is renderer on top of this)

#define ZD_DEPTH_BACKGROUND 1
#define ZD_DEPTH_BACKGROUND_OBJECT (ZD_DEPTH_BACKGROUND+1)
#define ZD_DEPTH_ENEMY (ZD_DEPTH_BACKGROUND_OBJECT+1)
#define ZD_DEPTH_PLAYER (ZD_DEPTH_ENEMY+1)
#define ZD_DEPTH_INVENTORY (ZD_DEPTH_PLAYER+1)
#define ZD_DEPTH_DIALOGUE (ZD_DEPTH_INVENTORY+1)