#ifndef __mine_engine_utilities_hpp__
#define __mine_engine_utilities_hpp__

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace MineEngine
{
    enum LogLevel
    {
        INFO,
        ERROR
    };

    inline std::string toString()
    {
        return std::string();
    }

    template <typename T>
    inline std::string toString(T value)
    {
        std::stringstream sstr;
        sstr << value;
        return sstr.str();
    }

    inline std::string toStrings()
    {
        return toString();
    }

    template <typename T, typename... Ts>
    inline std::string toStrings(T arg, Ts... args)
    {
        return toString(arg) + toStrings(args...);
    }

    template <typename T>
    std::string toStringHex(T value)
    {
        std::stringstream sstr;
        sstr << "0x" << std::hex << value << std::dec;
        return sstr.str();
    }

    std::string getLevel(LogLevel level)
    {
        std::string result;

        switch (level)
        {
        case LogLevel::INFO:
            result = "INFO";
            break;

        case LogLevel::ERROR:
            result = "ERROR";
            break;

        default:
            result = toString(level);
            break;
        }

        return result;
    }

    template <typename... Ts>
    void log(LogLevel level, Ts... args)
    {
        std::cout << "[" << getLevel(level) << "]" << toStrings(args...) << std::endl;
    }

    template <typename... Ts>
    void logi(Ts... args)
    {
        log(LogLevel::INFO, args...);
    }

    template <typename... Ts>
    void loge(Ts... args)
    {
        log(LogLevel::ERROR, args...);
    }

    std::string loadStringFromStream(std::istream &is)
    {
        std::stringstream sstr;
        std::string temp;
        try
        {
            while (getline(is, temp))
            {
                sstr << temp << std::endl;
            }
        }
        catch (const std::istream::failure error)
        {
            loge(error.what());
        }
        return sstr.str();
    }

    std::string loadStringFromFile(std::string filename)
    {
        std::ifstream fin;
        fin.open(filename);
        if (fin.fail())
        {
            loge("Unable to open file:\"", filename, "\"");
            return std::string();
        }
        std::string result = loadStringFromStream(fin);
        fin.close();
        return result;
    }

    std::vector<std::string> splitToStringArray(std::string data)
    {
        std::stringstream sstr;
        sstr << data;

        std::vector<std::string> result;
        std::string temp;

        while (sstr >> temp)
        {
            result.push_back(temp);
        }

        return result;
    }
} // namespace MineEngine

#endif