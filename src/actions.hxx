#pragma once

#include <functional>
#include <map>
#include <string>

class BangAction
{
public:
   std::string description;
   std::function<std::string(const std::string)> function;
};

class BangActions
{

protected:
   std::map<std::string, BangAction> actions{
       {"lower",
        {"Convierte a minusculas todas las letras", lower}},
       {"upper",
        {"Convierte a mayusculas todas las letras", upper}},
       {"title",
        {"Convierte a solo la primera letra de cada palabra en mayuscula todas las demas a minusculas", title}},
       {"words2lines",
        {"Crea una linea por cada palabra", words2lines}},
       {"w2l",
        {"Alias de: words2lines", words2lines}},
       {"lines2words",
        {"Convierte lineas en palabras separadas por un espacio", lines2words}},
       {"l2w",
        {"Alias de: lines2words", lines2words}},
       {"sort",
        {"Ordena lineas alfabeticamente", sort}},
       {"uniq",
        {"Borra lineas sucesivas repetidas", uniq}},
       {"csv2lines",
        {"Crea una linea por cada palabra separada por coma", csv2lines}},
       {"c2l",
        {"Alias de: csv2lines", csv2lines}},
       {"lines2csv",
        {"Convierte lineas en palabras separadas por coma", lines2csv}},
       {"l2c",
        {"Alias de: lines2csv", lines2csv}}

   };
   static std::string words2lines(const std::string str);
   static std::string csv2lines(const std::string str);
   static std::string lines2words(const std::string str);
   static std::string lines2csv(const std::string str);
   static std::string sort(const std::string str);
   static std::string lower(const std::string str);
   static std::string upper(const std::string str);
   static std::string title(const std::string str);
   static std::string uniq(const std::string str);

public:
   std::string Bang(const std::string &bang, const std::string &str);
   std::string BangChain(const std::string &bang, const std::string &str);
   std::string Help();
};
