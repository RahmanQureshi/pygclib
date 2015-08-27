#include <Python.h>
#include "gclibo.h"

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GCommand(GCon g, GCStringIn command, GBufOut buffer, GSize buffer_len, GSize* bytes_returned);
*/
static PyObject *
GCommand_gclib(PyObject *self, PyObject *args) 
{
  GReturn rc = 0;
  GCon con = -1;
  GCStringIn command;
  char buffer[1024]; //traffic buffer
  if (!PyArg_ParseTuple(args, "Hs", &con, (const char*) &command))
  {
    return NULL;
  }
  rc = GCommand(con, command, buffer, sizeof(buffer), 0);
  return Py_BuildValue("Hs", rc, buffer);
}

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GOpen(GCStringIn address, GCon* g);
*/
static PyObject *
GOpen_gclib(PyObject *self, PyObject *args) 
{
  GReturn rc = -1;
  GCStringIn address;
  GCon con = -1;
  if (!PyArg_ParseTuple(args, "s", &address))
  {
    return NULL;
  }
  rc = GOpen(address, &con);
  return Py_BuildValue("l H", rc, con);
}

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GClose(GCon g);
*/
static PyObject *
GClose_gclib(PyObject *self, PyObject *args) 
{
  GReturn rc = -1;
  GCon con = -1;
  if (!PyArg_ParseTuple(args, "H", &con))
  {
    return NULL;
  }
  rc = GClose(con);
  return Py_BuildValue("l", rc);
}

static PyMethodDef gclib_methods[] = {
    {"GCommand",  GCommand_gclib, METH_VARARGS, NULL},
    {"GOpen",  GOpen_gclib, METH_VARARGS, NULL},
    {"GClose",  GClose_gclib, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef gclibmodule = {
   PyModuleDef_HEAD_INIT,
   "gclib",   /* name of module */
    NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
   gclib_methods
};

PyMODINIT_FUNC
PyInit_gclib(void)
{
    return PyModule_Create(&gclibmodule);
}