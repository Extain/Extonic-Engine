#pragma once
#include <fstream>
#include <string>
#include <time.h>

namespace Extonic {
    namespace Util
    {
        std::string loadFileAsString(std::string filePath)
        {
            std::ifstream ifs(filePath);
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            return content;
        }

        // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
        const std::string CurrentDateTime()
        {
            time_t     now = time(NULL);
            struct tm  tstruct;
            char       buf[80];
            localtime_s(&tstruct, &now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
            return buf;
        }
    };
}