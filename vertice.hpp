#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <string>

class Vertice {
   private:
      std::string label;
      int id;
      
   public:
      Vertice();
      Vertice(const std::string &);
      Vertice(int);
      Vertice(const std::string &, int);
      ~Vertice();

      void setLabel(std::string);
      void setId(int);

      std::string getLabel() const;
      int getId() const;

      void show() const;
};

#endif // !VERTICE_HPP