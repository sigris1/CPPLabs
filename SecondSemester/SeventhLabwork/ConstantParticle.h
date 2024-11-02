//
// Created by sigris on 07.02.2024.
//
#pragma once
#include "tuple"
#include <utility>
#include "string"


const uint64_t kCellBorderLength = 30;
const uint64_t kLastCellNumber = 3;
const uint64_t kCellCount = 4;
const uint64_t kStringCount = 5;
const uint64_t kMaxEmptyChars = 16;
const uint64_t kEmptyChars = 11;
const uint64_t kDateLength = 10;
const uint64_t kSkippedCharsCount = 24;
const uint64_t kHoursInDay = 23;
const uint64_t kDegreeInCircle = 360;
const uint64_t kPercent = 100;
const uint64_t kSleepingTime = 4;
const uint64_t kSkippingBlocks = 4;

const std::vector<std::string> kClearSky = {
        "  \\     /    ",
        "   . — .     ",
        "— (     ) —  ",
        "   ` — `     ",
        "  /     \\    "
};
const std::vector<std::string> kMainlyClearSky = {
        "  \\     /    ",
        "   . — .     ",
        "— (  .————.  ",
        "   _(_._(_`) ",
        " /(_._(_._)_)"
};
const std::vector<std::string> kPartlyCloudy =  {
        "             ",
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "             "
};
const std::vector<std::string> kOvercast = {
        "  .——————,   ",
        " (__.—————.  ",
        "(__(__._(_`) ",
        " (__._(_._)_)",
        "             "
};
const std::vector<std::string> kFog = {
        "             ",
        "  — _ — _ —  ",
        "  — _ — _ —  ",
        "  — _ — _ —  ",
        "             "
};
const std::vector<std::string> kRimeFog = {
        "             ",
        "  *— _*— _ —*",
        "  —*_ —*_ *— ",
        "  *— _*— _ —*",
        "             "
};
const std::vector<std::string> kLightDrizzle = {
        "  \\  /       ",
        "— (  .————.  ",
        "  _(_._(_`)  ",
        "/(_._(_._)_) ",
        "   '  '  '   "
};
const std::vector<std::string> kModerateDrizzle = {
        "  \\  /       " ,
        "— (  .————.  ",
        "  _(_._(_`)  ",
        "/(_._(_._)_) ",
        " ' ' ' ' ' ' "
};
const std::vector<std::string> kDenseDrizzle = {
        "  \\  /       ",
        "— (  .————.  ",
        "  _(_._(_`)  ",
        "/(_._(_._)_) ",
        " ''''''''''' "
};
const std::vector<std::string> kLightFreezingDrizzle = {
        "  \\  /       " ,
        "— (  .————.  ",
        "  _(_._(_`)  ",
        "/(_._(_._)_) ",
        "   '* '* '*  "
};
const std::vector<std::string> kDenseFreezingDrizzle = {
        "  \\  /       ",
        "— (  .————.  ",
        "  _(_._(_`)  ",
        "/(_._(_._)_) ",
        " '*'*'*'*'*' "
};
const std::vector<std::string> kSlightRain = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  /   /   /  ",
        "             "
};
const std::vector<std::string> kModerateRain = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  /   /   /  ",
        " /   /   /   "
};
const std::vector<std::string> kHeavyRain = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " / , / , / , ",
        "/ , / , / ,  "
};
const std::vector<std::string> kSlightFreezingRain = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  / * / * /  ",
        "             "
};
const std::vector<std::string> kHeavyFreezingRain = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " / * / * / * ",
        "/ * / * / *  "
};
const std::vector<std::string> kSlightSnowfall = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  *   *   *  ",
        "             "
};
const std::vector<std::string> kModerateSnowfall = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  *   *   *  ",
        " *   *   *   "
};
const std::vector<std::string> kHeavySnowfall = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " * * * * * * ",
        "* * * * * *  "
};
const std::vector<std::string> kSnowGrains = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  * . * . * .",
        " * . * . * . "
};
const std::vector<std::string> kSlightRainShower = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  |   |   |  ",
        "             "
};
const std::vector<std::string> kModerateRainShower = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  |   |   |  ",
        "  |   |   |  "
};
const std::vector<std::string> kViolentRainShower = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  |,|,|,|,|,|",
        "  |,|,|,|,|,|"
};
const std::vector<std::string> kSlightSnowShower = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  *   *   *  ",
        "  *   *   *  "
};
const std::vector<std::string> kHeavySnowShower = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " * * * * * * ",
        " * * * * * * "
};
const std::vector<std::string> kThunderstorm = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        "  / ⚡ / ⚡ / ⚡",
        " / ⚡ / ⚡ / ⚡ "
};
const std::vector<std::string> kThunderstormWithSlightHail = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " /⚡°/⚡°/⚡°/⚡°",
        "/⚡ /⚡ /⚡ /⚡  "
};
const std::vector<std::string> kThunderstormWithHeavyHail = {
        "    .—————.  ",
        "  _(__._(_`) ",
        " (__._(_._)_)",
        " /⚡°/⚡°/⚡°/⚡°",
        "/⚡°/⚡°/⚡°/⚡° "
};
const std::vector<std::tuple<uint64_t , std::string, std::vector<std::string>>> kWeatherConditions = {
        {0, "Clear sky", kClearSky},
        {1, "Mainly clear sky", kMainlyClearSky},
        {2, "Partly cloudy", kPartlyCloudy},
        {3, "Overcast", kOvercast},
        {45, "Fog", kFog},
        {48, "Rime fog", kRimeFog},
        {51, "Light drizzle", kLightDrizzle},
        {53, "Moderate drizzle", kModerateDrizzle},
        {55, "Dense drizzle", kDenseDrizzle},
        {56, "Light freezing drizzle", kLightFreezingDrizzle},
        {57, "Dense freezing drizzle", kDenseFreezingDrizzle},
        {61, "Slight rain", kSlightRain},
        {63, "Moderate rain", kModerateRain},
        {65, "Heavy rain", kHeavyRain},
        {66, "Light freezing rain", kSlightFreezingRain},
        {67, "Heavy freezing rain", kHeavyFreezingRain},
        {71, "Slight snowfall", kSlightSnowfall},
        {73, "Moderate snowfall", kModerateSnowfall},
        {75, "Heavy snowfall", kHeavySnowfall},
        {77, "Snow grains", kSnowGrains},
        {80, "Slight rain shower", kSlightRainShower},
        {81, "Moderate rain shower", kModerateRainShower},
        {82, "Violent rain shower", kViolentRainShower},
        {85, "Slight snow shower", kSlightSnowShower},
        {86, "Heavy snow shower", kHeavySnowShower},
        {95, "Thunderstorm", kThunderstorm},
        {96, "Thunderstorm with slight hail", kThunderstormWithSlightHail},
        {99, "Thunderstorm with heavy hail", kThunderstormWithHeavyHail}
};
const std::vector<std::string> kWindDirection = {"↑", "↗", "→", "↘", "↓", "↙", "←", "↖"};
const std::string kMorning = "Morning";
const std::string kDay = "Day";
const std::string kEvening = "Evening";
const std::string kNight = "Night";
const std::string kHorizontal = "─";
const std::string kVertical = "│";
const std::string kIntersection = "┼";
const std::string kIncompleteRightIntersection = "├";
const std::string kIncompleteLeftIntersection = "┤";
const std::string kIncompleteTopIntersection = "┴";
const std::string kIncompleteBotIntersection = "┬";
const std::string kTopRightAngle = "┐";
const std::string kTopLeftAngle = "┌";
const std::string kBotRightAngle = "┘";
const std::string kBotLeftAngle = "└";
const std::string kKilometresPerHours = "km/h";
const std::string kCelsiusDegree = "ºC";
const std::string kKilometres = "km";
const std::string kMillimetres = "mm";
const std::string kCityURL = "https://api.api-ninjas.com/v1/city";
const std::string kWeatherForecastURL = "https://api.open-meteo.com/v1/forecast";
const std::string kInformationForForecast = "temperature_2m,precipitation_probability,precipitation,weather_code,visibility,wind_speed_10m,wind_direction_10m";


