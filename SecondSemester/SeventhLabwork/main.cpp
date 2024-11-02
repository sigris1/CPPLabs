//
// Created by sigris on 07.02.2024.
//

#include "City.h"
#include "iostream"
#include "Writer.h"
#include "fstream"
#include "clocale"
#include <nlohmann/json.hpp>
#include "ConstantParticle.h"
#include <ctime>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "unistd.h"

using json = nlohmann::json;

ftxui::Component ftxui::CatchEvent	(
        Component 	child,
        std::function<bool(Event event)> on_event
);

std::string GetWeatherForecast(json data,uint64_t number, uint64_t added_days){
    City city;
    city.name = data["name"].get<std::vector<std::string>>()[number];
    city.day_count = data["days_count"].get<std::vector<uint64_t>>()[number] + added_days;
    city.api_key = data["api-key"].get<std::string>();
    city.GetCityCoordinates();
    city.FillVectorWithWeathers();
    city.GetWeatherConditions();
    return Forecast(city);
}

void ForecastProcess(json data){
    uint64_t city_index = 0;
    uint64_t waiting_time = data["waiting_time"].get<uint64_t>();
    uint64_t number = 0;
    uint64_t added_days = 0;
    std::cout << GetWeatherForecast(data, number, added_days);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    auto renderer = ftxui::Renderer([] {return ftxui::text("Forecast");});
    auto component = CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('n')){
            ++city_index;
            if (city_index > data["name"].get<std::vector<std::string>>().size()){
                std::cout << "Wrong city";
                return false;
            }
            std::cout << GetWeatherForecast(data, city_index, added_days);
            added_days = 0;
            return false;
        } else if (event == ftxui::Event::Character('p')){
            --city_index;
            if (city_index < 0){
                std::cout << "Wrong city";
                return false;
            }
            std::cout << GetWeatherForecast(data, city_index, added_days);
            added_days = 0;
            return false;
        } else if (event == ftxui::Event::Character('+')){
            ++added_days;
            if (added_days > 16){
                std::cout << "Wrong city";
                return false;
            }
            std::cout << GetWeatherForecast(data, city_index, added_days);
            return false;
        } else if (event == ftxui::Event::Character('-')){
            --added_days;
            if (added_days < 1){
                std::cout << "Wrong city";
                return false;
            }
            std::cout << GetWeatherForecast(data, city_index, added_days);
            return false;
        } else if (event == ftxui::Event::Character('\x1b')){
            return true;
        }
        return true;
    });
    screen.Loop(component);
}

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()){
        std::cerr << "Wrong file path";
    }
    json data = json::parse(file);
    ForecastProcess(data);
    return 0;
}