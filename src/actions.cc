#include "actions.hxx"
#include "str2.hxx"
#include <algorithm>
#include <locale>

std::string BangActions::Bang(const std::string &bang, const std::string &str)
{
   std::string result;
   try
   {
      const auto &action = actions.at(trimmed(bang));
      result = action.function(str);
   }
   catch (const std::out_of_range &err)
   {
      throw std::out_of_range("No existe la funcion interna: " + bang);
   };

   return result;
}

std::string BangActions::BangChain(const std::string &bang, const std::string &str)
{
   std::string result = str;
   for (const auto &b : strSplit(bang, "|"))
   {
      result = Bang(b, result);
   }
   return result;
}

std::string BangActions::Help()
{
   std::string buff;
   for (const auto &b : actions)
   {
      buff += b.first + ":\n      " + b.second.description + "\n\n";
   }
   return buff;
}

std::string BangActions::words2lines(const std::string str)
{
   std::string buff = str;
   size_t pos;
   while ((pos = buff.find(" ")) != std::string::npos)
      buff[pos] = '\n';
   return buff;
}

std::string BangActions::lines2words(const std::string str)
{
   std::string buff = str;
   size_t pos;
   while ((pos = buff.find("\n")) != std::string::npos)
      buff[pos] = ' ';
   return buff;
}

std::string BangActions::sort(const std::string str)
{
   auto lines = strSplit(str, "\n");
   std::sort(lines.begin(), lines.end());
   return IterJoin(lines.begin(), lines.end(), "\n");
}

std::string BangActions::lower(const std::string str)
{
   std::string text;
   std::for_each(str.begin(), str.end(), [&text](const auto &a)
                 { text.push_back(std::tolower(a)); });
   return text;
};

std::string BangActions::upper(const std::string str)
{
   std::string text;
   std::for_each(str.begin(), str.end(), [&text](const auto &a)
                 { text.push_back(std::toupper(a)); });
   return text;
};

std::string BangActions::title(const std::string str)
{
   std::string text;
   bool last = true;
   for (const char &c : str)
   {
      text.push_back(last ? std::toupper(c) : std::tolower(c));
      last = std::isspace(c);
   }
   return text;
}