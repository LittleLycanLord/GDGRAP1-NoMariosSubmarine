//! Include the corresponding .hpp
//? Other .hpps or libraries are to be included in the .hpp file so
//? a .cpp file should only have 1 #include line
#include "TemplateAnnotated.hpp"

//! Use the needed namespaces
using namespace sampleNamespace;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
//? Note: The formatter will format short functions like this
SampleClass::SampleClass(int nInteger) : 
    //? Note: You can also declare primitives in the initializer list (Will clarify if we can do this to ma'am)
    dDouble(0.69f) {
    std::cout << "This is a sample class.";
}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
//? Tip: Just copy and paste the chunk of the Getters & Setters then add the
//? scope modifiers, then leverage the multiple cursors functionality of VSCode:
//? Hold Alt + Click where you need the cursors OR Up/Down arrow keys
int SampleClass::getInteger() { return this->nInteger; }
void SampleClass::setInteger(int nInteger) { this->nInteger = nInteger; }
// namespace models
