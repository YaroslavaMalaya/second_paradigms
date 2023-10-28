#include "fileWriterReader.h"

const size_t chunk_size = 128;

string FileReader::read(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("File not found: " + filePath);
    }

    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    string content;
    content.reserve(fileSize);
    vector<char> buffer(chunk_size);
    while (fileSize > 0) {
        size_t chunkSize = min(chunk_size, fileSize);
        file.read(buffer.data(), chunkSize);
        content.append(buffer.begin(), buffer.begin() + chunkSize);
        fileSize -= chunkSize;
    }
    return content;
}

void FileWriter::write(const string& filePath, const string& content) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing: " + filePath);
    }

    for(size_t i = 0; i < content.size(); i += chunk_size) {
        size_t chunkSize = min(chunk_size, content.size() - i);
        file.write(content.data() + i, chunkSize);
    }
}
