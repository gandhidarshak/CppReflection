# CppReflection
Library to enable easy reflection of any Cpp variables/objects/data-structures.

### Motivation
Every C++ programmer writes easy to use std::cout statements for quick debugging of values of the different type of objects when debugger is not handy or has a relatively larger loading time. By default, C++ does not support reflection. This means besides printing value of a variable, one would also have to print the name of variable as string to make sense of what is being printed (e.g. `std::cout << "Var1" << Var1 << std::endl;`).

The issue becomes more complicated, when one wants reflect on various different type of variables. It is still manageable, if the different variables have operator `ostream <<` for them. But in case of STL data structures and most class objects, this operator is often not overloaded to dump to ostreams. In such scenarios, even just to reflect a variable, one often has to write verbose code.

This project discusses a easy/intuitive to use library that I wrote to resolve the above issue in style. The library is written very compactly (~200 lines) using concepts like [SFINAE](https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error), [Stringizing Operator](https://docs.microsoft.com/en-us/cpp/preprocessor/stringizing-operator-hash?view=vs-2019), [Variadic Macros](https://docs.microsoft.com/en-us/cpp/preprocessor/variadic-macros?view=vs-2019)and [Variadic Functions](https://en.wikipedia.org/wiki/Variadic_function). It can handle almost all simple data-types (e.g. char, int, float, string, ...), derived data-types (e.g. customized string/number classes), Container Data types (e.g. array, vector, set, map, unordered_set, unordered_map, list, ...), collections (e.g. pair, tuples, ...), and even properly defined classes that have a 'reflect' API defined in them. Using the Reflection functionality is as simple as calling a macro and passing all the variables that need to be reflected in arguments regardless of their count/type. Please see [test.cpp](https://github.com/gandhidarshak/CppReflection/blob/master/test.cpp) file for a better example of the usage. 

### Dependencies
The code is tested on Linux/Windows-Cygwin gcc-6.2.0. However, It should work on any recent C++ compilers that supports C++ 14 or above. I have purposefully avoided dependencies on special purpose  libraries like Boost to make it self sufficient and easy to use. 

### Installation 
Installation is quite simple, just download the [CppReflection.h](https://github.com/gandhidarshak/CppReflection/blob/master/CppReflection.h) file from git hub and keep it in a location which is accessible from your project.  

### Usage
Include CppReflection.h file in your C++ code. The file defines 3 macros that facilitates 3 modes of Variable reflection.
1.  CppReflectAsList(Var1, Var2, Var3) - This will return a string which will have Var1/2/3 names and value in 3 lines separated by a newline charecter like a list.
2.  CppReflectAsCSV(Var1, Var2, Var3) - This will return a string which will have Var1/2/3 names and value in 1 line separated by a commas like a CSV format.
3.  CppReflect(Var1, Var2, Var3) - This will use the last mode that was set using one of the previous two commands and return the string. This is mainly to write 'reflect' APIs in any class for which we want reflection.

### Example
File [test.cpp](https://github.com/gandhidarshak/CppReflection/blob/master/test.cpp) describes a simple usage of CppReflect* macros by using var0 to var10 of variety of data types. The terminal output for the test.cpp is like below.

   // std::cout << CppReflectAsList(var0, var1 , p_var1, *p_var1, var2 , var3 , var4 , var5 , var6 , var7, var8, var9, var10) << std::endl;
   
   var0 = true
   var1 = 101
   p_var1 = 0x7ffec49a8c38
   *p_var1 = 101
   var2 = 1.01
   var3 = Hello
   var4 = World
   var5 ( Container with 3 elements )
   	var5[0] = 3
   	var5[1] = 5
   	var5[2] = 7
   var6 ( Container with 3 elements )
   	var6[0] = 3.1
   	var6[1] = 5.2
   	var6[2] = 7.3
   var7 ( Container with 3 elements )
   	var7[0] ( Tuple with 2 elements )
   		var7[0][0] = One
   		var7[0][1] = 1
   	var7[1] ( Tuple with 2 elements )
   		var7[1][0] = Three
   		var7[1][1] = 3
   	var7[2] ( Tuple with 2 elements )
   		var7[2][0] = Two
   		var7[2][1] = 2
   var8 ( Container with 3 elements )
   	var8[0] ( Container with 3 elements )
   		var8[0][0] = 51
   		var8[0][1] = 52
   		var8[0][2] = 53
   	var8[1] ( Container with 3 elements )
   		var8[1][0] = 61
   		var8[1][1] = 62
   		var8[1][2] = 63
   	var8[2] ( Container with 3 elements )
   		var8[2][0] = 71
   		var8[2][1] = 72
   		var8[2][2] = 73
   var9 ( Tuple with 4 elements )
   	var9[0] = United States
   	var9[1] = California
   	var9[2] = San Franscisco
   	var9[3] = 94115
   var10 ( Object )
   	a = 212100
   	b = 1.012e-09
   	c = &
   
   // std::cout << CppReflectAsCSV(var0, var1 , p_var1, *p_var1, var2 , var3 , var4 , var5 , var6 , var7, var8, var9, var10) << std::endl;
   
   var0 , true , var1 , 101 , p_var1 , 0x7ffec49a8c38 , *p_var1 , 101 , var2 , 1.01 , var3 , Hello , var4 , World , var5 ( Container with 3 elements ) , var5[0] , 3 , var5[1] , 5 , var5[2] , 7 , var6 ( Container with 3 elements ) , var6[0] , 3.1 , var6[1] , 5.2 , var6[2] , 7.3 , var7 ( Container with 3 elements ) , var7[0] ( Tuple with 2 elements ) , var7[0][0] , One , var7[0][1] , 1 , var7[1] ( Tuple with 2 elements ) , var7[1][0] , Three , var7[1][1] , 3 , var7[2] ( Tuple with 2 elements ) , var7[2][0] , Two , var7[2][1] , 2 , var8 ( Container with 3 elements ) , var8[0] ( Container with 3 elements ) , var8[0][0] , 51 , var8[0][1] , 52 , var8[0][2] , 53 , var8[1] ( Container with 3 elements ) , var8[1][0] , 61 , var8[1][1] , 62 , var8[1][2] , 63 , var8[2] ( Container with 3 elements ) , var8[2][0] , 71 , var8[2][1] , 72 , var8[2][2] , 73 , var9 ( Tuple with 4 elements ) , var9[0] , United States , var9[1] , California , var9[2] , San Franscisco , var9[3] , 94115 , var10 ( Object ) , a , 212100 , b , 1.012e-09 , c , & , 
```
### Sharing is caring!

Please feel free to IM me with your suggestions and feedback about the idea!

### License

CppReflection library uses the MIT license. See [LICENSE](https://github.com/gandhidarshak/CppReflection/blob/master/LICENSE.md) for more details.
