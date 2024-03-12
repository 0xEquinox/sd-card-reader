#include <vector.hpp>

StringList::StringList() : capacity(10), size(0){
    array = new String[capacity];
}

// Add element to the end of the array
void StringList::add(const String& element) {
    if (size == capacity) {
        // Resize the array if it's full
        capacity *= 2;
        String* newArray = new String[capacity];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[size++] = element;
}

// Get element at index
String& StringList::get(int index) {
    if (index < 0 || index >= size) {
        // Handle out of range index
        Serial.println("Index out of range");
        while (1) {} // Halt program
    }
    return array[index];
}

// Get the current size of the array
int StringList::getSize() const {
    return size;
}