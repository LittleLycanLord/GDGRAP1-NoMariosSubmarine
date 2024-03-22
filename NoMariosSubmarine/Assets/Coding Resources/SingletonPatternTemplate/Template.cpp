#include "Template.hpp"

using namespace managers;
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
//! ╔═══════════════════╗
//! ║ SINGLETON CONTENT ║
//! ╚═══════════════════╝
Template* Template::P_SHARED_INSTANCE = NULL;
Template::Template(){};
Template::Template(const Template&) {}
Template* Template::getInstance() {
    if (P_SHARED_INSTANCE == NULL) P_SHARED_INSTANCE = new Template();
    return P_SHARED_INSTANCE;
}
// namespace models
