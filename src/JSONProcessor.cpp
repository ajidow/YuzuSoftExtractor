#include "JSONProcessor.h"

std::string JSONProcessor::readfile(const char* filename)
{
    FILE* fp = std::fopen(filename, "rb");
    if (!fp)
    {
        std::cout << "Open file failed!   " << "file:" << filename << std::endl;
        return "";
    }

    char* buf = new char[1024 * 1024];
    int n = fread(buf, 1, 1024 * 1024, fp);
    fclose(fp);

    std::string res;
    if (n >= 0)
    {
        res.append(buf, 0, n);
    }
    delete[]buf;
    return res;
}