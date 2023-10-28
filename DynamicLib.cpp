#include "DynamicLib.h"
using namespace std;

DynamicLibLoader::DynamicLibLoader(const string &libPath) {
    handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle) {
        cerr << "Lib not found. Error: " << dlerror() << endl;
        throw runtime_error("Library not found");
    }
    dlerror();
    encrypt_ptr = nullptr;
    decrypt_ptr = nullptr;
}

DynamicLibLoader::~DynamicLibLoader() {
    if (handle) {
        dlclose(handle);
    }
}

void* DynamicLibLoader::getFunction(const string &funcName) {
    void* func_ptr = dlsym(handle, funcName.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << funcName << " function not found. Error: " << dlsym_error << endl;
        throw runtime_error(funcName + " function not found.");
    }
    return func_ptr;
}