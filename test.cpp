#include "CppReflection.h"
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <list>

class Foo {
   private:
      long int a;
      double b;
      char c;
   public:
      Foo () 
      {
         a = 21.21e4;
         b = 1.0120e-9;
         c = '&';
      }
      std::string reflect()  const
      {
         return CppReflect(a,b,c);
      }
};

int main()
{
   bool var0 = true;
   int var1 = 101;
   int* p_var1 = &var1;
   float var2 = 1.01;
   std::string var3 = "Hello";
   char const *var4 = "World";
   std::vector<int> var5 = {3,5,7};
   std::list<float> var6 = {3.1,5.2,7.3};
   std::map<std::string, int> var7 = {{"One", 1},{"Two", 2}, {"Three", 3}};
   std::set<std::array<int,3>> var8 = {{51,52,53}, {61,62,63}, {71,72,73}};
   auto var9 = std::make_tuple ("United States", "California", "San Franscisco", 94115);
   Foo var10;

   std::cout << "Output of CppReflectAsList : " << std::endl;
   std::cout << CppReflectAsList(var0, var1 , p_var1, *p_var1, var2 , var3 , var4 , var5 , var6 , var7, var8, var9, var10) << std::endl;
   std::cout << "Output of CppReflectAsCsv : " << std::endl;
   std::cout << CppReflectAsCSV(var0, var1 , p_var1, *p_var1, var2 , var3 , var4 , var5 , var6 , var7, var8, var9, var10) << std::endl;
   return 0;
}
