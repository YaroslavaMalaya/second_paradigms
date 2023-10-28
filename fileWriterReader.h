#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

class FileReader {
public:
    static string read(const string& filePath);
};

class FileWriter {
public:
    static void write(const string& filePath, const string& content);
};