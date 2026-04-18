#pragma once

#include <map>
#include <string>

namespace Tests
{
    class DialogueTests
    {
    public:
        DialogueTests() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                (this->*testFunction)();
            }
        }

    private:

        using TestMap = std::map<std::string, void (DialogueTests::*)(void)>;
        TestMap m_testMap =
        {
            {"dialogue tests", &DialogueTests::dialogueTests},
            {"dialogue sanity tests", &DialogueTests::dialogueSanityTests}
        };

        void dialogueTests();
        void dialogueSanityTests();
    };


};