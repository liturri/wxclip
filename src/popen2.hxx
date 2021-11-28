#pragma once

#include <string>

class PopenStrFilter
{
protected:
   std::string cmd;
   int readFD, writeFD;

private:
   int WriterProc(const std::string &writeBuffer);

public:
   PopenStrFilter(const std::string &cmd) : cmd(cmd){};
   int Run(const std::string &writeBuffer);
   std::string Read();
   // void run(const std::vector<char> &writeBuffer);
};
