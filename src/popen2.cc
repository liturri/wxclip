#include "popen2.hxx"
#include <unistd.h>

int PopenStrFilter::WriterProc(const std::string &writeBuffer)
{
   auto writerPid = fork();
   if (writerPid < 0)
      return writerPid;
   if (writerPid == 0)
   {
      close(readFD);
      write(writeFD, &writeBuffer[0], writeBuffer.size());
      close(writeFD);
      exit(0);
   }
   close(writeFD);
   return writerPid;
}

int PopenStrFilter::Run(const std::string &writeBuffer)
{
   int fd_read[2], fd_write[2];
   if (pipe(fd_read))
      return -1;
   if (pipe(fd_write))
      return -1;
   auto procPid = fork();

   if (procPid < 0)
      return procPid;

   if (procPid == 0) // child
   {
      close(fd_write[1]);
      dup2(fd_write[0], 0);
      close(fd_read[0]);
      dup2(fd_read[1], 1);
      execl("/bin/sh", "sh", "-c", cmd.c_str(), nullptr);
      perror("execl");
      _exit(99);
   }
   close(fd_write[0]);
   close(fd_read[1]);

   writeFD = fd_write[1];
   readFD = fd_read[0];

   WriterProc(writeBuffer);
   return 0;
}

std::string PopenStrFilter::Read()
{
   char tmpBuffer[1024];
   size_t readBytes;
   std::string buffer;

   while ((readBytes = ::read(readFD, tmpBuffer, sizeof(tmpBuffer))))
   {
      buffer += std::string(tmpBuffer, readBytes);
   }
   close(readFD);
   return buffer;
}
