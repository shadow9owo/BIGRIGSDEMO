#include "Logger.hpp"
#include <string>
#include <vector>
#include <raylib.h>
#include "Data.hpp"

namespace Logger
{
    static const size_t MAX_LOG_LINES = 10;
    std::vector<std::string> logbuf;

    void RenderLogger()
    {
        int lineIndex = 0;
        for (const auto &entry : logbuf)
        {
            DrawText(entry.c_str(),
                     0,
                     GetMonitorHeight(0) - 16 * (int)logbuf.size() + 16 * lineIndex,
                     16,
                     WHITE);
            lineIndex++;
        }
    }

    void AddToLoggerBuffer(const std::string &log)
    {
        logbuf.push_back(log);
        if (logbuf.size() > MAX_LOG_LINES)
            logbuf.erase(logbuf.begin());
    }
}
