#pragma once

#define CHECK(VALUE) do {if (!(VALUE)) {std::cout << "Failed: " << __FILE__ << '(' << __LINE__ << ')' << " false" << std::endl;} } while (0);

#define CHECK_EQUAL(ACTUAL, EXPECTED) do {if (!((ACTUAL) == (EXPECTED))) { std::cout << "Failed: " << __FILE__ << '(' << __LINE__ << ')' << " Expected " << (EXPECTED) << " but got " << (ACTUAL) << '\n'; }} while (0)
