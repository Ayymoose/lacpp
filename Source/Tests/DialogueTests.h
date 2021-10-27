#pragma once

#include "Testable.h"
#include "Dialogue.h"

#include <map>
#include <string>

namespace Testable
{

class DialogueTests : public TestUnit
{
public:
    constexpr DialogueTests() = default;

    using DialogueTestsMap = const std::map<std::string, void (DialogueTests::*)(void)>;
    void runTests() override;

private:

    DialogueTestsMap m_tests =
    {
        {"dialogue max characters test", &DialogueTests::maxCharactersTest},
        {"dialogue every character test", &DialogueTests::everyCharacterTest},
        {"dialogue question test", &DialogueTests::questionTest},
        {"dialogue heart test", &DialogueTests::heartTest},
        {"dialogue position test", &DialogueTests::positionTest},
        {"dialogue colour test", &DialogueTests::colourTest},
    };

    void everyCharacterTest() noexcept;
    void maxCharactersTest() noexcept;
    void questionTest() noexcept;
    void heartTest() noexcept;
    void positionTest() noexcept;
    void colourTest() noexcept;
};

};