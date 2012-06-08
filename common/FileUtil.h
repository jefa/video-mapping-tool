#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <string>

using namespace std;

class FileUtil
{
    public:
        FileUtil();
        virtual ~FileUtil();
		static char* readBinaryFile(string path);
        static bool writeBinaryFile(string path, string binData);

};

#endif // FILEUTIL_H
