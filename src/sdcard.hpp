#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "vector.hpp"

#pragma once
void listFiles(String dirPath);

#pragma once
void readFile(fs::FS &fs, const char * path);

#pragma once
StringList listAudioFiles(String dirPath, StringList fileList);