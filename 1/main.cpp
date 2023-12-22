#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

std::unordered_map<std::string, char> SUPPORTED_TOKENS = 
{
    {"1", '1'},
    {"2", '2'},
    {"3", '3'},
    {"4", '4'},
    {"5", '5'},
    {"6", '6'},
    {"7", '7'},
    {"8", '8'},
    {"9", '9'},
    // tokens for part 2 of the day 1
    {"one", '1'},
    {"two", '2'},
    {"three", '3'},
    {"four", '4'},
    {"five", '5'},
    {"six", '6'},
    {"seven", '7'},
    {"eight", '8'},
    {"nine", '9'},
    // end part 2
};

struct Token{
    char value;
    int position;
};

std::string ConcatTwoTokens(const Token& t1, const Token& t2)
{
    return {t1.value, t2.value, '\0'};
}

auto FindTokens(std::string_view calibrationStr)
{
    std::vector<Token> tokens;

    for(auto&& token : SUPPORTED_TOKENS)
    {
        int index = 0;
        while ((index = calibrationStr.find(token.first, index)) != std::string::npos) {
            tokens.push_back(Token{token.second, index});
            index += token.first.length();
        }
    }

    std::sort(tokens.begin(), tokens.end(), [](const Token& lhs, const Token& rhs)
    {
        return lhs.position < rhs.position;
    });
    return tokens;
}

int CalibrationValue(std::string_view calibrationStr)
{
    auto tokens = FindTokens(calibrationStr);

    if(tokens.empty())
    {
        return 0;
    }

    return std::stoi(
        ConcatTwoTokens(tokens.front(), tokens.back())
        );
}

int main(int argc, char const *argv[])
{
    std::ifstream file("C:\\projects\\adventOfCode\\1\\input.txt");

    if (file.is_open()) {
        int64_t sum = 0;
        for (std::string line; std::getline(file, line);)
        {
            sum += CalibrationValue(line);
        }

        std::cout << sum << '\n';
    }

    return 0;
}
