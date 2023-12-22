#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#define PART1 false

void FindFewestNumber(std::string setStr, int32_t& maxRed, int32_t& maxGreen, int32_t& maxBlue)
{
    while( !setStr.empty() )
    {
        std::size_t cursor = setStr.find(',');

        std::string valueColorStr;
        std::size_t eraseCount = 0;
        if(cursor != std::string::npos)
        {
            valueColorStr = setStr.substr(0,cursor);
            eraseCount = cursor + 2;
        }
        else
        {
            valueColorStr = setStr;
            eraseCount = setStr.size();
        }
        std::size_t cursor2 = valueColorStr.find(' ');
        std::string valueStr = valueColorStr.substr(0,cursor2);
        std::string colorStr = valueColorStr.substr(cursor2+1);

        uint32_t value = std::stoi(valueStr);

        if( colorStr == "red" &&  value > maxRed)
        {
            maxRed = value;
        }
        else if( colorStr == "green" &&  value > maxGreen)
        {
            maxGreen = value;
        }
        else if( colorStr == "blue" &&  value > maxBlue)
        {
            maxBlue = value;
        }

        setStr.erase(0, eraseCount);
    }
}

bool IsSetPossible(std::string setStr, uint32_t red, uint32_t green, uint32_t blue)
{
    while( !setStr.empty() )
    {
        std::size_t cursor = setStr.find(',');

        std::string valueColorStr;
        std::size_t eraseCount = 0;
        if(cursor != std::string::npos)
        {
            valueColorStr = setStr.substr(0,cursor);
            eraseCount = cursor + 2;
        }
        else
        {
            valueColorStr = setStr;
            eraseCount = setStr.size();
        }
        std::size_t cursor2 = valueColorStr.find(' ');
        std::string valueStr = valueColorStr.substr(0,cursor2);
        std::string colorStr = valueColorStr.substr(cursor2+1);

        uint32_t comparedValue = (colorStr == "red") ? red : ((colorStr == "green") ? green : blue); 

        if( std::stoi(valueStr) > comparedValue )
        {
            return false;
        }
        setStr.erase(0, eraseCount);
    }

    return true;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("C:\\projects\\adventOfCode\\2\\input.txt");

    uint32_t red = 12;
    uint32_t green = 13;
    uint32_t blue = 14;

    if (file.is_open()) {
        std::size_t sum = 0;
        for (std::string line; std::getline(file, line);)
        {
            // find game
            std::size_t cursor = line.find(':');
            std::string gameStr = line.substr(0,cursor);
            uint32_t gameId = std::stoi(gameStr.erase(0,5));

            // remove "Game X: "
            line.erase(0, cursor + 2);
#if PART1
            bool possibleGame = true;
#else
            int32_t maxRed = 0, maxGreen = 0, maxBlue = 0;
#endif
            while( !line.empty() )
            {
                cursor = line.find(';');

                std::string setStr;
                std::size_t eraseCount = 0;
                if(cursor != std::string::npos)
                {
                    setStr = line.substr(0,cursor);
                    eraseCount = cursor + 2;
                }
                else
                {
                    setStr = line;
                    eraseCount = line.size();
                }
#if PART1
                if(!IsSetPossible(line.substr(0,cursor), red, green, blue))
                {
                    possibleGame = false;
                    break;
                }
#else  
                FindFewestNumber(line.substr(0,cursor), maxRed, maxGreen, maxBlue);
#endif 
                line.erase(0, eraseCount);
            }

#if PART1
            if(possibleGame)
            {
                sum += gameId;
            }
#else
            sum += maxRed * maxGreen * maxBlue;
#endif 
        }

        std::cout << sum << '\n';
    }

    return 0;
}
