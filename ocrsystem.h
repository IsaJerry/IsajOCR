#ifndef OCRSYSTEM_H
#define OCRSYSTEM_H

#include <Python.h>
#include <Includer.h>
#include <string>

class OCRSystem
{
public:
    OCRSystem();

    void GetAcessToken(std::string id, std::string key);
    void PythonFinalInit();

private:
    //PyObject *Model;
    //PyObject *GetToken;
};

#endif // OCRSYSTEM_H
