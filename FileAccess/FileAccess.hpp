#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class FileAccess {

    int fd;
    FILE *fp;
    char *mode;

    char * fileName;
    
    public:

    FileAccess(const char* fileName,const char* mode);

    int readFile(char* buf, int bufSize);

    int writeFile(char* buf, int bufSize = 0, bool append = 1);

    int copyTo(FileAccess toFile);

    int emptyFile();

    FILE * getFilePointer();

    ssize_t fileSize();

    void closeFile();

    void toConsole();

    void commandToFile();

    //enum wrtie {}

};