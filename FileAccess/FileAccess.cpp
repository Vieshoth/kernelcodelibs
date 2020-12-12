#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "FileAccess.hpp"

using namespace std;

FileAccess::FileAccess(const char* fileName,const char* mode){

    this->mode = (char *)malloc(sizeof(mode));
    strcpy(this->mode, mode);

    this->fileName = (char *)malloc(sizeof(fileName));
    strcpy(this->fileName, fileName);

    if(fp = fopen(fileName, mode))
    {
        printf("File name: %s, creation: successful\n", fileName);
    }
    else
    {
        printf("File name: %s, creation: failed\n", fileName);
    }
    
}

ssize_t FileAccess::fileSize(){

    ssize_t lSize;
    fseek (fp , 0 , SEEK_END); // move the file pointer to end of the file
    lSize = ftell (fp); 
    rewind (fp);

    return lSize ; //cout << "fileSize: " <<lSize <<endl; 
    
}

int FileAccess::readFile(char* buf, int bufSize){

    int numRead, count = 0;

    fseek (fp , 0 , SEEK_SET);

    //printf("insie readfile mode: %s, %d", this->mode, strcmp(this->mode, "r"));

    if (!strcmp(this->mode, "r")|| !strcmp(this->mode, "r+")|| !strcmp(this->mode, "w+"))
    {
        // while (!feof(fp)) // to read file 
        // { 
           numRead = fread(buf, bufSize, 1, fp); 
        //   cout << "numRead" << numRead << endl;
        // } 
    }
    else
    {
        printf("No read file permission\n");
    }
    
    return numRead;

}

int FileAccess::writeFile(char* buf, int bufSize, bool append ){

    int numWrite;
    if(!append)
        fseek (fp , 0 , SEEK_SET);

    //printf("insie writeFile111 size: %d", bufSize);

    if(!bufSize)
        bufSize = sizeof(buf);

    if (strcmp(this->mode, "w") || strcmp(this->mode, "w+"))
    {
        if((numWrite = fwrite(buf, bufSize, 1, fp) == 1))
            printf("File write success\n");
        else
            printf("File write failure\n");
    }
    else
    {
        printf("No write file permission\n");
    }     

    return numWrite;
}


FILE * FileAccess::getFilePointer(){
    return this->fp;
}

void FileAccess::closeFile(){
    fclose(fp);
}
    
int FileAccess::copyTo(FileAccess toFile){

    int fileSize = this->fileSize();
    char * buf = (char * )malloc(fileSize);
    if(fread(buf, fileSize, 1, fp)){
        toFile.writeFile(buf, fileSize, 0);
        return true;
    }

    return false;
}

int FileAccess::emptyFile(){
    if(fp = freopen(NULL, "w+", fp))
        return 1;
    else
    {
        return 0;
    }
    
}

void FileAccess::toConsole(){

    int numRead, bufSize = 1024;
    char buf[bufSize]={0};

    fseek (fp , 0 , SEEK_SET);

    if (!strcmp(this->mode, "r")|| !strcmp(this->mode, "r+") || !strcmp(this->mode, "w+"))
    {

        while (!feof(fp)) // to read file 
        { 
            fread(buf, bufSize, 1, fp); 
            cout << buf << endl;
        } 

    }
    else
    {
        printf("No read file permission\n");
    }
    
    //return numRead;
}

void FileAccess::commandToFile(){

    char str[1024];
    fgets (str, 1024, stdin); 
    fputs(str, fp);
}