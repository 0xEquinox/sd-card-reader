#include <Arduino.h>
#pragma once

class StringList {
private:
    String* array;
    int capacity;
    int size;

public:
    // Constructor
    StringList();

    // Add element to the end of the array
    void add(const String& element);

    // Get element at index
    String& get(int index);

    // Get the current size of the array
    int getSize() const;
};

