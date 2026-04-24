#pragma once

#include "Singleton.h"

#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

namespace zelda
{

class Logger : public engine::Singleton<Logger>
{
public:
    enum class Mask : uint32_t
    {
        NONE = 0x0,
        ERROR = 0x1,
        INFO = 0x2,
        WARNING = 0x4
    };

    Logger()
        : m_mask(std::to_underlying(Mask::NONE))
        , m_output(&std::cout)
    {
        *m_output << timestamp() << ' ' << '[' << 'I' << ']' << ' ' << "---Application started---" << '\n';
    }

    ~Logger()
    {
        *m_output << timestamp() << ' ' << '[' << 'I' << ']' << ' ' << "---Application terminated---" << '\n';
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    // Attempt to open path for append logging.
    // Falls back to stdout and prints a warning if the file cannot be opened.
    void setOutputFile(const std::filesystem::path& path)
    {
        m_file.open(path, std::ios::app);
        if (m_file.is_open())
        {
            m_output = &m_file;
            *m_output << timestamp() << ' ' << '[' << 'I' << ']' << ' ' << "---Application started---" << '\n';
        }
        else
        {
            *m_output << timestamp() << ' ' << '[' << 'W' << ']' << ' ' << "Cannot open " << path.c_str() << '\n';
        }
    }

    // Log format: YYYY-MM-DD HH:MM:SS [X] message
    // where X is I (info), E (error) or W (warning)
    template <Mask M>
    void log(const std::string& message)
    {
        if (!(m_mask & std::to_underlying(M)))
        {
            if constexpr (M == Mask::ERROR)
                *m_output << timestamp() << " [E] " << message << '\n';
            else if constexpr (M == Mask::INFO)
                *m_output << timestamp() << " [I] " << message << '\n';
            else if constexpr (M == Mask::WARNING)
                *m_output << timestamp() << " [W] " << message << '\n';
            else
                *m_output << timestamp() << " [?] " << message << '\n';
        }
    }

    void setMask(uint32_t mask) { m_mask = mask; }
    [[nodiscard]] uint32_t getMask() const { return m_mask; }

private:
    [[nodiscard]] static std::string timestamp()
    {
        const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
        return std::format("{:%Y-%m-%d %H:%M:%S}", now);
    }

    uint32_t m_mask;
    std::ofstream m_file;
    std::ostream* m_output;
};

} // namespace zelda
