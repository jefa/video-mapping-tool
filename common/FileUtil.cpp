#include "FileUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

char* FileUtil::readBinaryFile(string path){
    FILE * pFile;
    long lSize;
    size_t result;

    pFile = fopen ( path.c_str() , "rb" );
    if (pFile==NULL) {
        fputs ("File error",stderr);
        return NULL;
    }

    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    char* buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        fputs ("Memory error",stderr);
        return NULL;
    }

    result = fread (buffer, 1, lSize, pFile);
    if (result != lSize) {
        fputs ("Reading error",stderr);
        return NULL;
    }

    fclose (pFile);

    return buffer;
}

bool FileUtil::writeBinaryFile(string path, string binData){
    FILE * pFile = fopen ( path.c_str() , "wb" );   // rb = read binary, **very** important for jpgs / binary files
    if (pFile==NULL) {
        fputs ("File error",stderr);
        return false;
    }

    size_t result = fwrite (binData.c_str(), 1, binData.size(), pFile);
    cout << "\tRESULT WRITE:::: " << result << endl;
    fclose (pFile);

    return true;
}
