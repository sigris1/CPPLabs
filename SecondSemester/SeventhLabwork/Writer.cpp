//
// Created by sigris on 08.02.2024.
//

#include "Writer.h"
#include "iostream"
#include "ConstantParticle.h"

void AddCellBorder(std::string& returned){
    for (uint64_t i = 0; i < kCellBorderLength; ++i){
        returned += kHorizontal;
    }
}

void AddFullBorderLine(bool top, std::string& returned){
    if(top){
        returned += kTopLeftAngle;
        for (uint64_t i = 0; i < kCellCount; ++i){
            AddCellBorder(returned);
            if (i < kLastCellNumber){
                returned += kIncompleteBotIntersection;
            } else {
                returned += kTopRightAngle;
            }
        }
    } else {
        returned += kBotLeftAngle;
        for (uint64_t i = 0; i < kCellCount; ++i){
            AddCellBorder(returned);
            if (i < kLastCellNumber){
                returned += kIncompleteTopIntersection;
            } else {
                returned += kBotRightAngle;
            }
        }
    }
    returned += "\n";
}

void AddDelimiterLine(std::string& returned){
    returned += kIncompleteRightIntersection;
    for (uint64_t i = 0; i < kCellCount; ++i){
        AddCellBorder(returned);
        if (i < kLastCellNumber){
            returned += kIntersection;
        } else {
            returned += kIncompleteLeftIntersection;
        }
    }
    returned += "\n";
}

void AddDaysParts(std::string& returned){
    for (uint64_t i = 0; i < kCellCount; ++i){
        returned += kVertical;
        if (i == 0) {
            for (uint64_t j = 0; j < kEmptyChars; ++j) {
                returned += " ";
            }
            returned += kMorning;
            for (uint64_t j = 0; j < kEmptyChars + 1; ++j) {
                returned += " ";
            }
        } else if (i == 1) {
            for (uint64_t j = 0; j < kEmptyChars + 2; ++j) {
                returned += " ";
            }
            returned += kDay;
            for (uint64_t j = 0; j < kEmptyChars + 3; ++j) {
                returned += " ";
            }
        } else if (i == 2) {
            for (uint64_t j = 0; j < kEmptyChars; ++j) {
                returned += " ";
            }
            returned += kEvening;
            for (uint64_t j = 0; j < kEmptyChars + 1; ++j) {
                returned += " ";
            }
        } else {
            for (uint64_t j = 0; j < kEmptyChars + 1; ++j) {
                returned += " ";
            }
            returned += kNight;
            for (uint64_t j = 0; j < kEmptyChars + 2; ++j) {
                returned += " ";
            }
        }
    }
    returned += kVertical + "\n";
}

std::string Forecast(const City& city){
    std::string returned = "";
    for (uint64_t days_number = 0; days_number < city.day_count; ++days_number){
        returned += ("Forecast for " + city.dates[days_number] + " in " + city.name + "\n");
        AddFullBorderLine(true, returned);
        AddDaysParts(returned);
        AddDelimiterLine(returned);
        for (uint64_t string_number = 0; string_number < kStringCount; ++string_number){
            for (uint64_t cell_number = 0; cell_number < kCellCount; ++cell_number){
                returned += kVertical;
                returned += (city.weathers[kCellCount * days_number + cell_number].picture[string_number] + " ");
                if (city.weathers[kCellCount * days_number + cell_number].weather_information[string_number].length() < kMaxEmptyChars) {
                    returned += city.weathers[kCellCount * days_number + cell_number].weather_information[string_number];
                    uint64_t n = 0;
                    while(n + city.weathers[kCellCount * days_number + cell_number].weather_information[string_number].length() < kMaxEmptyChars){
                        returned += " ";
                        ++n;
                    }
                    if (string_number == 1) {
                        returned += " ";
                    } else if (string_number == 2){
                        returned += "  ";
                    }
                } else {
                    uint64_t n = 0;
                    while(n < kMaxEmptyChars - 1){
                        returned += city.weathers[kCellCount * days_number + cell_number].weather_information[string_number][n];
                        ++n;
                    }
                    returned += " ";
                }
            }
            returned += (kVertical + "\n");
        }
        AddFullBorderLine(false, returned);
        returned += "\n";
    }
    return returned;
}


