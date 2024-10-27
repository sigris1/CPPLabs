#pragma once

#include "HammingEncoder.h"
#include "../HamArc/parser/ArgParser.h"
#include "Archive.h"

void Write(ArgumentParser::ArgParser& parser, const std::string& file_path, std::ofstream& file, EncodedParameters& parameters );