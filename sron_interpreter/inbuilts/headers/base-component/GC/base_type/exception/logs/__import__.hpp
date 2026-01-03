#pragma once

#ifndef _IMPRT_H
#define _IMPRT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <filesystem>
#include <string_view>
#include <csignal>

#include "_flags_.hpp"
#include "../../../../../../../../sron_headers/_sron_hasher_.hpp"
#include "../../../../../../../../sron_headers/_sron_support_.hpp"
#include "../../../../../../../../sron_headers/_char_.hpp"

#if defined(_WIN64)
    #include<Windows.h>
#elif defined(__linux__)
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
#else
    #error This codebase is only made for Windows and Linux
#endif

#endif