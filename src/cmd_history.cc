#include "cmd_history.hxx"
#include <algorithm>
#include <fstream>
#include <map>

void CommandHistory::OrderCmd(std::ifstream &stream)
{
   std::vector<std::string> historyContent;
   std::string str;
   // Read the next line from File untill it reaches the end.
   while (std::getline(stream, str))
   {
      // Line contains string of length > 0 then save it in vector
      if (str.size() > 0)
         historyContent.push_back(str);
   }

   std::map<std::string, int> dup;
   std::for_each(historyContent.begin(), historyContent.end(), [&dup](const auto &val)
                 { dup[val]++; });

   std::vector<std::pair<std::string, int>> vecFromMap;
   std::for_each(dup.begin(), dup.end(), [&vecFromMap](const auto &map)
                 { vecFromMap.push_back(std::make_pair(map.first, map.second)); });
   std::sort(vecFromMap.begin(), vecFromMap.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

   for (const auto &i : vecFromMap)
   {
      commandsList.push_back(i.first);
   };
}

CommandHistory::CommandHistory(const std::string &histFile) : histFile(histFile)
{
   std::ifstream hst(histFile, std::ios::in);
   OrderCmd(hst);
}

void CommandHistory::AppendCmd(const std::string &cmd)
{
   std::ofstream hst(histFile, std::ios::out | std::ios::app);
   hst << cmd << std::endl;
   hst.close();
}
