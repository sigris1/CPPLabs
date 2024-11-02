//
// Created by sigris on 08.02.2024.
//

#pragma once
#include "City.h"

void AddCellBorder(std::string& returned);

void AddFullBorderLine(bool top, std::string& returned);

void AddDelimiterLine(std::string& returned);

void AddDaysParts(std::string& returned);

std::string Forecast(const City& city);
