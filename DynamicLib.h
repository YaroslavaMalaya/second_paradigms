#include <dlfcn.h>
#include <string>
#include <iostream>
using namespace std;

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);


class DynamicLibLoader {
public:
    DynamicLibLoader(const string &libPath);
    ~DynamicLibLoader();

    void* getFunction(const std::string &funcName);

private:
    void* handle;
    encrypt_ptr_t encrypt_ptr;
    decrypt_ptr_t decrypt_ptr;
};

class CaesarCipher {
public:
    CaesarCipher(const string& libPath) {
        libLoader = make_unique<DynamicLibLoader>(libPath);
        encrypt_ptr = (encrypt_ptr_t)libLoader->getFunction("encrypt");
        decrypt_ptr = (decrypt_ptr_t)libLoader->getFunction("decrypt");
    }

    char* encrypt(char* text, int key) {
        char* result = encrypt_ptr(text, key);
        return result;
    }

    char* decrypt(char* text, int key) {
        char* result = decrypt_ptr(text, key);
        return result;
    }

private:
    unique_ptr<DynamicLibLoader> libLoader;
    encrypt_ptr_t encrypt_ptr;
    decrypt_ptr_t decrypt_ptr;
};
