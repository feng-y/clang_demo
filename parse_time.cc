#include <optional>
#include <chrono>
#include <string>
#include <regex>

#include <gtest/gtest.h>

std::optional<int64_t> parse_duration(const std::string& s) {
    // 验证字符串是否满足格式
    std::regex validate_re(R"((\d+[dhms])+)");
    if (!std::regex_match(s, validate_re))
        return std::nullopt;

    std::chrono::seconds total(0);
    std::regex re(R"((\d+)([dhms]))");
    std::smatch match;
    for (std::string::const_iterator searchStart(s.cbegin()); std::regex_search(searchStart, s.cend(), match, re);
            searchStart = match.suffix().first) {
        if (match[2] == "d") {
            total += std::chrono::hours(std::stoi(match[1])) * 24;
        } else if (match[2] == "h") {
            total += std::chrono::hours(std::stoi(match[1]));
        } else if (match[2] == "m") {
            total += std::chrono::minutes(std::stoi(match[1]));
        } else {  // seconds
            total += std::chrono::seconds(std::stoi(match[1]));
        }
    }
    return total.count();
}

TEST(ParseDurationTest, EmptyString) {
    std::string input = "";
    auto result = parse_duration(input);
    EXPECT_EQ(result, std::nullopt);
}

TEST(ParseDurationTest, InvalidFormat) {
    std::string input = "7X12Y30Z";
    auto result = parse_duration(input);
    EXPECT_EQ(result, std::nullopt);
}

TEST(ParseDurationTest, NonDHMSCharacters) {
    std::string input = "7d12p30q";
    auto result = parse_duration(input);
    EXPECT_EQ(result, std::nullopt);
}

TEST(ParseDurationTest, ValidString) {
    std::string input = "1d23h59m59s";
    auto result = parse_duration(input);
    EXPECT_NE(result, std::nullopt);
    EXPECT_EQ(*result, 86400 + 23 * 3600 + 59 * 60 + 59);
}

TEST(ParseDurationTest, LargeValue) {
    std::string input = "9999d";
    auto result = parse_duration(input);
    EXPECT_NE(result, std::nullopt);
    EXPECT_EQ(*result, 9999L * 86400);
}

TEST(ParseDurationTest, Interruption) {
    std::string input = "1dXX2hYY3mZZ4s";
    auto result = parse_duration(input);
    EXPECT_NE(result, std::nullopt);
    EXPECT_EQ(*result, 86400 + 2 * 3600 + 3 * 60 + 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
