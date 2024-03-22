#include "Template.hpp"

using namespace sampleNamespace;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
SampleClass::SampleClass(int nInteger) : dDouble(0.69f) {
    std::cout << "This is a sample class.";
}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
int SampleClass::getInteger() { return this->nInteger; }
void SampleClass::setInteger(int nInteger) { this->nInteger = nInteger; }
// namespace models
