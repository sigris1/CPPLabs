//
// Created by sigris on 08.02.2024.
//

#pragma once

#include "cpr/cpr.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Weather {
public:
    std::vector<std::string> picture;
    std::vector<std::string> weather_information;
};

class City {
public:
    std::string name;
    std::string country;
    std::string latitude;
    std::string longitude;
    uint64_t day_count = 3;
    std::string api_key;
    std::vector<std::string> dates;
    std::vector<Weather> weathers;

    void GetCityCoordinates();

    void FillVectorWithWeathers();

    void GetWeatherConditions();

private:
    void SetWeather(uint64_t code, uint64_t number);
    void SetPictureAndName(const std::string& current, uint64_t& position);
    void SetTemperature(const std::string& current, uint64_t& position);
    void SetWind(const std::string& current, uint64_t& direction_position, uint64_t& position);
    void SetVisibility(const std::string& current, uint64_t& visibility_position);
    void SetPrecipitation(const std::string& current, uint64_t& chance_position, uint64_t& position);

    void SetDates(const std::string& current, uint64_t position);
};
