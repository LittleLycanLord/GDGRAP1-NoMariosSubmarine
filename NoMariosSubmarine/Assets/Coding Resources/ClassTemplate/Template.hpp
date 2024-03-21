#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "vector"

namespace sampleNamespace {
class SampleClass {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    int nInteger;
    unsigned int uUnsigned;
    bool bBoolean;
    float fFloat;
    double dDouble;
    std::vector<int> vecIntegers;
    std::string strString;
    int aIntegerArray[69];
    int* pPointer;

    //? If no given Hungarian notation, assume C
    // SampleClass CSampleClass;
    sf::Time tTime;
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    SampleClass(int nInteger);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
    int getInteger();
    void setInteger(int nInteger);
};
}  // namespace sampleNamespace