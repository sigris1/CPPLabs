//
// Created by sigris on 08.02.2024.
//

#include "City.h"
#include "ConstantParticle.h"

class Wind{
public:
    float min = 100.0;
    float max = 0.0;
    std::string direction;
};

class Precipitation{
public:
    float precipitation_count;
    uint64_t precipitation_chance;
};

uint64_t GetCount(const std::string& days_part){
    if (days_part == kMorning){
        return 7;
    } else if (days_part == kDay){
        return 6;
    } else if (days_part == kEvening){
        return 4;
    } else {
        return 3;
    }
}

uint64_t SetPartCode(const std::string& days_part, uint64_t& position, const std::string& current){
    uint64_t count_codes = GetCount(days_part);
    uint64_t selected_code = 0;
    for (uint64_t i = 0; i < count_codes; ++i){
        uint64_t now;
        if (current[position + 1] == ',' || current[position + 1] == ']'){
            now = std::stoi(current.substr(position, 1));
            position += 2;
        } else {
            now = std::stoi(current.substr(position, 2));
            position += 3;
        }
        selected_code = std::max(now, selected_code);
    }
    return selected_code;
}

uint64_t FindWeatherByCode(uint64_t code){
    uint64_t i = 0;
    while (std::get<0>(kWeatherConditions[i]) != code){
        ++i;
    }
    return i;
}

float GetTemperature(const std::string& days_part, uint64_t& position, const std::string& current){
    uint64_t count_codes = GetCount(days_part);
    float selected_number = 0;
    for (uint64_t i = 0; i < count_codes; ++i){
        float now;
        if (current[position] == '-'){
            if (current[position + 5] == ',' || current[position + 5] == ']'){
                now = std::stof(current.substr(position, 5));
                position += 6;
            } else {
                now = std::stof(current.substr(position, 4));
                position += 5;
            }
        } else {
            if (current[position + 4] == ',' || current[position + 4] == ']'){
                now = std::stof(current.substr(position, 4));
                position += 5;
            } else {
                now = std::stof(current.substr(position, 3));
                position += 4;
            }
        }
        selected_number += now/(float)count_codes;
    }
    return selected_number;
}

float GetVisibility(const std::string& days_part, uint64_t& visibility_position, const std::string& current){
    uint64_t count_codes = GetCount(days_part);
    float selected_number = 0;
    for (uint64_t i = 0; i < count_codes; ++i){
        float now = 0;
        if (current[visibility_position + 9] == ',' || current[visibility_position + 9] == ']'){
            now = std::stof(current.substr(visibility_position, 8));
            visibility_position += 10;
        } else if (current[visibility_position + 8] == ',' || current[visibility_position + 8] == ']'){
            now = std::stof(current.substr(visibility_position, 7));
            visibility_position += 9;
        } else if (current[visibility_position + 7] == ',' || current[visibility_position + 7] == ']'){
            now = std::stof(current.substr(visibility_position, 6));
            visibility_position += 8;
        } else if (current[visibility_position + 6] == ',' || current[visibility_position + 6] == ']'){
            now = std::stof(current.substr(visibility_position, 5));
            visibility_position += 7;
        } else if (current[visibility_position + 5] == ',' || current[visibility_position + 5] == ']'){
            now = std::stof(current.substr(visibility_position, 5));
            visibility_position += 6;
        }
        selected_number += now/(float)count_codes;
    }
    return selected_number;
}

std::string CreateTemperatureString(float temperature){
    if (temperature > 10){
        return (std::to_string(temperature).substr(0, 4) + " " + kCelsiusDegree);
    } else if (temperature < -10){
        return (std::to_string(temperature).substr(0, 5) +  " " + kCelsiusDegree);
    } else if (temperature > 0 && temperature < 10){
        return (std::to_string(temperature).substr(0, 3) + " " + kCelsiusDegree);
    } else {
        return (std::to_string(temperature).substr(0, 4) + " " + kCelsiusDegree);
    }

}

std::string CreateVisibilityString(float visibility){
    if (visibility > 10000){
        return (std::to_string(visibility).substr(0, 2) + " " + kKilometres);
    } else if (visibility > 1000) {
        return (std::to_string(visibility).substr(0, 1) + " " + kKilometres);
    } else if (visibility > 100) {
        return ("0." + std::to_string(visibility).substr(1, 1) + " " + kKilometres);
    } else if (visibility > 10) {
        return ("0.0" + std::to_string(visibility).substr(2, 1) + " " + kKilometres);
    } else {
        return ("0.00" + std::to_string(visibility).substr(3, 1) + " " + kKilometres);
    }
}

std::string CreatePrecipitationString(Precipitation precipitation){
    return (std::to_string(precipitation.precipitation_count).substr(0, 3) + " " + kMillimetres + ' ' + '|' + ' ' + std::to_string(precipitation.precipitation_chance) + '%');
}

Wind GetWind(const std::string& days_part, const std::string& current, uint64_t& direction_position, uint64_t& position){
    uint64_t count_codes = GetCount(days_part);
    uint64_t angle = 0;
    float max = 0.0;
    float min = 100.0;
    for (uint64_t i = 0; i < count_codes; ++i){
        float now;
        if (current[position + 4] == ',' || current[position + 4] == ']'){
            now = std::stof(current.substr(position, 4));
            position += 5;
        } else {
            now = std::stof(current.substr(position, 3));
            position += 4;
        }
        if (max < now){
            max = now;
        }
        if (min > now){
            min = now;
        }
        if (current[direction_position + 3] == ',' || current[direction_position + 3] == ']') {
             angle += std::stoi(current.substr(direction_position, 3));
        } else if (current[direction_position + 2] == ',' || current[direction_position + 2] == ']'){
            angle += std::stoi((current.substr(direction_position, 2))) + 360;
        } else if (current[direction_position + 1] == ',' || current[direction_position + 1] == ']'){
            angle += std::stoi((current.substr(direction_position, 1))) + 360;
        }
        angle = angle/count_codes;
    }
    angle %= kDegreeInCircle;
    Wind now;
    now.max = max;
    now.min = min;
    if (angle < 23){
        now.direction = kWindDirection[0];
    } else if (angle < 67){
        now.direction = kWindDirection[1];
    } else if (angle < 112){
        now.direction = kWindDirection[2];
    } else if (angle < 157){
        now.direction = kWindDirection[3];
    } else if (angle < 202){
        now.direction = kWindDirection[4];
    } else if (angle < 247){
        now.direction = kWindDirection[5];
    } else if (angle < 292){
        now.direction = kWindDirection[6];
    } else if (angle < 337){
        now.direction = kWindDirection[7];
    } else {
        now.direction = kWindDirection[0];
    }
    return now;
}

Precipitation GetPrecipitation(const std::string& days_part, const std::string& current, uint64_t& chance_position, uint64_t& position){
    uint64_t count_codes = GetCount(days_part);
    uint64_t chance = 0;
    float count = 0;
    for (uint64_t i = 0; i < count_codes; ++i){
        float now;
        if (current[position + 5] == ',' || current[position + 5] == ']'){
            now = std::stof(current.substr(position, 5));
            position += 6;
        } else {
            now = std::stof(current.substr(position, 4));
            position += 5;
        }
        if (current[chance_position + 2] == ',' || current[chance_position + 2] == ']'){
            chance += std::stoi((current.substr(chance_position, 2)));
        } else if (current[chance_position + 1] == ',' || current[chance_position + 1] == ']'){
            chance += std::stoi((current.substr(chance_position, 1)));
        }
        count += now/count_codes;
        chance += chance/(kPercent * count_codes);
    }
    Precipitation precipitation;
    precipitation.precipitation_chance = chance;
    precipitation.precipitation_count = count;
    return precipitation;
}

std::string CreateWindString(const Wind& wind){
    std::string now = wind.direction;
    now += " ";
    if (wind.min > 10){
        now += std::to_string(wind.min).substr(0, 2);
    } else {
        now += std::to_string(wind.min).substr(0, 1);
    }
    now += "-";
    if (wind.max > 10){
        now += std::to_string(wind.max).substr(0, 2);
    } else {
        now += std::to_string(wind.max).substr(0, 1);
    }
    now += " " + kKilometresPerHours;
    return now;
}

void City::FillVectorWithWeathers() {
    for (uint64_t i = 0; i < kCellCount * day_count; ++i){
        Weather now;
        weathers.emplace_back(now);
    }
}

void City::SetWeather(uint64_t code, uint64_t number){
    weathers[number].weather_information.emplace_back(std::get<1>(kWeatherConditions[code]));
    weathers[number].picture = std::get<2>(kWeatherConditions[code]);
}

void City::GetCityCoordinates() {
    cpr::Response information = cpr::Get(cpr::Url{kCityURL},
                               cpr::Header{{"X-Api-Key", api_key}},
                               cpr::Parameters{{"name", name}});
    std::string current = (std::string)(information.text);
    uint64_t position = 0;
    uint64_t checked_char = 0;
    while(checked_char != 6){
        if (current[position] != '"'){
            ++position;
        } else {
            ++position;
            ++checked_char;
        }
    }
    position += 2;
    uint64_t first = position;
    while(current[position] != ','){
        ++position;
    }
    latitude = current.substr(first, position - first);
    while (current[position] != ':'){
        ++position;
    }
    position += 2;
    first = position;
    while(current[position] != ','){
        ++position;
    }
    longitude = current.substr(first, position - first);
    while (current[position] != ':'){
        ++position;
    }
    position += 3;
    first = position;
    while(current[position] != '"'){
        ++position;
    }
    country = current.substr(first, position - first);
}

void City::SetDates(const std::string& current, uint64_t position){
    std::string first_date = current.substr(position + 2, kDateLength);
    dates.emplace_back(first_date);
    for (uint64_t i = 0; i < day_count - 1; ++i){
        position += kHoursInDay * kSkippedCharsCount - 1;
        std::string now = current.substr(position + 2, kDateLength);
        dates.emplace_back(now);
    }
}

void City::SetPictureAndName(const std::string& current, uint64_t& position) {
    for (uint64_t i = 0; i < day_count; ++i) {
        uint64_t code_position = 0;
        while (code_position < 4) {
            if (current[position] != ',') {
                ++position;
            } else {
                ++code_position;
                ++position;
            }
        }
        SetWeather(FindWeatherByCode(SetPartCode(kMorning, position, current)), kCellCount * i);
        SetWeather(FindWeatherByCode(SetPartCode(kDay, position, current)), kCellCount * i + 1);
        SetWeather(FindWeatherByCode(SetPartCode(kEvening, position, current)), kCellCount * i + 2);
        SetWeather(FindWeatherByCode(SetPartCode(kNight, position, current)), kCellCount * i + 3);
    }
}

void City::SetTemperature(const std::string &current, uint64_t &position){
    for (uint64_t i = 0; i < day_count; ++i){
        uint64_t code_position = 0;
        while (code_position < 4){
            if (current[position] != ','){
                ++position;
            } else {
                ++code_position;
                ++position;
            }
        }
        weathers[kCellCount * i].weather_information.emplace_back(CreateTemperatureString(GetTemperature(kMorning, position, current)));
        weathers[kCellCount * i + 1].weather_information.emplace_back(CreateTemperatureString(GetTemperature(kDay, position, current)));
        weathers[kCellCount * i + 2].weather_information.emplace_back(CreateTemperatureString(GetTemperature(kEvening, position, current)));
        weathers[kCellCount * i + 3].weather_information.emplace_back(CreateTemperatureString(GetTemperature(kNight, position, current)));
    }
}

void City::SetWind(const std::string& current, uint64_t& direction_position, uint64_t& position){
    for (uint64_t i = 0; i < day_count; ++i){
        uint64_t code_position = 0;
        while (code_position < 4){
            if (current[position] != ','){
                ++position;
            } else {
                ++code_position;
                ++position;
            }
        }
        weathers[kCellCount * i].weather_information.emplace_back(CreateWindString(GetWind(kMorning, current, direction_position, position)));
        weathers[kCellCount * i + 1].weather_information.emplace_back(CreateWindString(GetWind(kDay, current, direction_position, position)));
        weathers[kCellCount * i + 2].weather_information.emplace_back(CreateWindString(GetWind(kEvening, current, direction_position, position)));
        weathers[kCellCount * i + 3].weather_information.emplace_back(CreateWindString(GetWind(kNight, current, direction_position, position)));
    }
}

void City::SetVisibility(const std::string& current, uint64_t& visibility_position){
    for (uint64_t i = 0; i < day_count; ++i){
        uint64_t code_position = 0;
        while (code_position < 4){
            if (current[visibility_position] != ','){
                ++visibility_position;
            } else {
                ++code_position;
                ++visibility_position;
            }
        }
        weathers[kCellCount * i].weather_information.emplace_back(CreateVisibilityString(GetVisibility(kMorning, visibility_position, current)));
        weathers[kCellCount * i + 1].weather_information.emplace_back(CreateVisibilityString(GetVisibility(kDay, visibility_position, current)));
        weathers[kCellCount * i + 2].weather_information.emplace_back(CreateVisibilityString(GetVisibility(kEvening, visibility_position, current)));
        weathers[kCellCount * i + 3].weather_information.emplace_back(CreateVisibilityString(GetVisibility(kNight, visibility_position, current)));
    }
}

void City::SetPrecipitation(const std::string& current, uint64_t& chance_position, uint64_t& position){
    for (uint64_t i = 0; i < day_count; ++i){
        uint64_t code_position = 0;
        while (code_position < 4){
            if (current[position] != ','){
                ++position;
            } else {
                ++code_position;
                ++position;
            }
        }
        weathers[kCellCount * i].weather_information.emplace_back(CreatePrecipitationString(GetPrecipitation(kMorning, current, chance_position, position)));
        weathers[kCellCount * i + 1].weather_information.emplace_back(CreatePrecipitationString(GetPrecipitation(kDay, current, chance_position, position)));
        weathers[kCellCount * i + 2].weather_information.emplace_back(CreatePrecipitationString(GetPrecipitation(kEvening, current, chance_position, position)));
        weathers[kCellCount * i + 3].weather_information.emplace_back(CreatePrecipitationString(GetPrecipitation(kNight, current, chance_position, position)));
    }
}

void City::GetWeatherConditions() {
    cpr::Response information = cpr::Get(cpr::Url{kWeatherForecastURL},
                                cpr::Parameters{{"latitude", latitude}, {"longitude", longitude}, {"hourly", kInformationForForecast}, {"forecast_days", std::to_string(day_count)}});
    std::string current = information.text;
    uint64_t position = 0;
    while (current[position] != '['){
        ++position;
    }
    SetDates(current, position);
    while (current[position] != '['){
        ++position;
    }
    uint64_t temperature_position = position + 2;
    while(current[temperature_position] != '['){
        ++temperature_position;
    }
    ++temperature_position;
    uint64_t pos = 0;
    ++position;
    while (pos < kSkippingBlocks){
        if (current[position] != '['){
            ++position;
        } else {
            ++pos;
            ++position;
        }
    }
    SetPictureAndName(current, position);
    SetTemperature(current, temperature_position);
    while(current[temperature_position] != '['){
        ++temperature_position;
    }
    uint64_t precipitation_position = temperature_position;
    uint64_t visibility_position = precipitation_position;
    uint64_t chance_position = precipitation_position + 1;
    ++precipitation_position;
    while (current[precipitation_position] != '['){
        ++precipitation_position;
    }
    ++precipitation_position;
    pos = 0;
    ++visibility_position;
    while (pos < 3) {
        if (current[visibility_position] == '[') {
            ++pos;
            ++visibility_position;
        } else {
            ++visibility_position;
        }
    }
    pos = 0;
    while (pos < 2){
        if (current[position] != '['){
            ++position;
        } else {
            ++pos;
            ++position;
        }
    }
    uint64_t direction_position = position + 2;
    while (current[direction_position] != '['){
        ++direction_position;
    }
    SetWind(current, direction_position, position);
    SetVisibility(current, visibility_position);
    SetPrecipitation(current, chance_position, precipitation_position);
}
