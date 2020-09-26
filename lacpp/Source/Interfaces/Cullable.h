#pragma once

// CullableParent is responsible for doing culling on CullableChild
// It will release the memory for a CullableChild (as it owns it)
class CullableParent
{
public:
    virtual void cull() noexcept = 0;
};

// CullableChild will return true on cull() if it needs to have it's memory released
class CullableChild
{
public:
    virtual bool cull() noexcept = 0;
};