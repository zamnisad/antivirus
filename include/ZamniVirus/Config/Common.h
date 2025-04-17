#pragma once

#include <filesystem>
#include <sstream>

#define min(a,b) (((a) < (b)) ? (a) : (b))

static constexpr char RESET[]     = "\033[0m";
static constexpr char RED[]       = "\033[31m";
static constexpr char GREEN[]     = "\033[32m";
static constexpr char YELLOW[]    = "\033[33m";
static constexpr char BLUE[]      = "\033[34m";
static constexpr char CYAN[]      = "\033[36m";
static constexpr char BOLDWHITE[] = "\033[1m\033[37m";

namespace fs = std::filesystem;

/*
    Green - for cool results
    Red - for errors
    Yellow - for warnings
    Cyan - for just info
    Blue - for scanning and input
*/
/*
    [VIR] - virus info
    [SCN] - scanning info
    [INF] - just info
    [BEG] - start info
    [END] - end info
    [LOG] - log info
    [WRN] - warning info
    [QRN] - quarantine info
    [ERR] - error info
    [DIR] - directory info
*/