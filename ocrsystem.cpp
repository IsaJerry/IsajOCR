#include "ocrsystem.h"

OCRSystem::OCRSystem()
{
}

void OCRSystem::GetAcessToken(std::string id, std::string key)
{
    Py_SetPythonHome(L"D:/python");
    Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')");
        PyObject *Model = PyImport_ImportModule("get");
        PyObject *GetToken = PyObject_GetAttrString(Model, "getAcessToken");
        //PyObject *args = PyTuple_New(2);
        //PyObject *args = Py_BuildValue("(ss)", id.c_str(), key.c_str());
        //PyTuple_SetItem(args, 0, Py_BuildValue("s", id.c_str());
        //PyTuple_SetItem(args, 1, Py_BuildValue("s", key.c_str());
        PyObject *ret = PyObject_CallObject(GetToken, NULL);
        std::string e;
        PyArg_Parse(ret, "s", &e);
        qDebug()<<e;
    Py_Finalize();
}

void OCRSystem::PythonFinalInit()
{

}
