#ifndef DEPTH_H
#define DEPTH_H

// Z-ordering is implemented through a std::multiset
// Whenever a Renderable is added to the set, it uses the m_depth
// value to determine it's order
// Given that its internal representation is a sorted binary tree
// we don't need to sort it

// Higher depth = Rendered later on (on top of everything else)
// Lower depth  = Renderer earlier on (everything is renderer on top of this)

#define BACKGROUND_DEPTH 1
#define BACKGROUND_OBJECT_DEPTH (BACKGROUND_DEPTH+1)
#define PLAYER_DEPTH (BACKGROUND_OBJECT_DEPTH+1)
#define INVENTORY_DEPTH (PLAYER_DEPTH+1)


#endif // DEPTH_H
