#pragma once
#include <string>
#include <vector>

class CommandHistory
{
private:
   std::string histFile;
   std::vector<std::string> commandsList;

public:
   CommandHistory(const std::string &histFile);
   void AppendCmd(const std::string &cmd);

   const std::vector<std::string> GetCommandsList() const { return commandsList; };

protected:
   void OrderCmd(std::ifstream &stream);
};