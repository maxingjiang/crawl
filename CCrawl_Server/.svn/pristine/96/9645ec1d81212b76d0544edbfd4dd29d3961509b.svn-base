/**g++ -o callpy callpy.cpp -I/usr/include/python2.6 -L/usr/lib64/python2.6/config -lpython2.6**/  

#include "callpy.h"

CallPy::CallPy()
{
	Py_Initialize();
}

CallPy::~CallPy()
{
	 Py_Finalize();
}

int CallPy::unicode2uft8(const string &src, string &desk)
{
    // 添加当前路径
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./../lib/')");

    PyObject *pName = NULL, *pModule = NULL, *pDict = NULL, *pClass = NULL, *pInstance = NULL, *result = NULL;

    // 载入名为pytest的脚本
    pName = PyString_FromString("CPPcallpy");
    pModule = PyImport_Import(pName);
    if (!pModule)
    {
        printf("can't find CPPcallpy.py");
        return -1;
    }
    pDict = PyModule_GetDict(pModule);
    if (!pDict)
    {
        return -1;
    }

    pClass = PyDict_GetItemString(pDict, "CallPy"); //通过字典属性获取模块中的类
    pInstance = PyInstance_New(pClass,NULL,NULL);//实例化获取的类

    result = PyObject_CallMethod(pInstance,(char*)"unicode2utf8", (char*)"(s)", (char*)src.c_str());
	char* body=NULL;
    PyArg_Parse(result, "s", &body); //将python类型的返回值转换为c/c++类型
    desk = body;
//    Py_DECREF(pName);
//    Py_DECREF(pModule);
//    Py_DECREF(pDict);
//    Py_DECREF(pClass);
//    Py_DECREF(pInstance);
//    Py_DECREF(result);

	return 0;
}


