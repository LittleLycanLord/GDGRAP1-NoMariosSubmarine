//! Don't Forget this in Every .hpp file #SayGoodbyeToHeaderGuards
#pragma once
//! Careful with the include paths
//? If you copy and paste an include line, it might disappear right away
//? it's because the formatter will automatically remove duplicates so just
// press the allmighty Ctrl + Z
#include "SFML/Graphics.hpp"
#include "iostream"
#include "vector"

//? Take note of the capitalization/cases.

namespace sampleNamespace {
class SampleClass {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    //? FOR SOME REASON, Ma'am don't want default values here...?
    int nInteger;
    unsigned int uUnsigned;  // Size_t's are also unsigned ints but made for the
                             // std namespace
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
    //? Have the parameters same as the attributes
    SampleClass(int nInteger);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
    //? Ma'am said it's fine to have duplicate access modifiers for the sake of
    // formatting
public:
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
    //? Ma'am prefers that we do
    // get
    // set
    // get
    // set
    //? Than
    // get
    // get
    // set
    // set
public:
    int getInteger();
    //? Have the parameter same as the attribute
    void setInteger(int nInteger);
};
}  // namespace sampleNamespace