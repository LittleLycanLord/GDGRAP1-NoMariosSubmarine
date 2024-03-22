#pragma once

namespace managers {
class Template {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
    //! ╔═══════════════════╗
    //! ║ SINGLETON CONTENT ║
    //! ╚═══════════════════╝
private:
    static Template* P_SHARED_INSTANCE;

private:
    Template();
    Template(const Template&);
    Template& operator=(const Template&);

public:
    static Template* getInstance();
};
}  // namespace managers