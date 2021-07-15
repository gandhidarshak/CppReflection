/*

MIT License

Copyright (c) 2020 Darshak Gandhi

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
/**
 * @file CppReflection.h
 * @brief This library defines macros to reflect on Cpp * Variables/Data-structures/Objects.
 * @author Darshak Gandhi
 * @version 1.0
 * @date 2019-11-04
 */

#ifndef CppReflection_h_
#define CppReflection_h_

#include <iostream>
#include <string>
#include <array>
#include <tuple>
#include <sstream>
#include <algorithm>
#include <type_traits>

/**
 * @brief Macro to call reflect with mode = List, each variable/sub-var is printed in new lines.
 */
#define CppReflectAsList(...) CppReflection::reflect(CppReflection::List, #__VA_ARGS__, __VA_ARGS__)

/**
 * @brief Macro to call reflect with mode = CSV, to print variables in comma separated way
 */
#define CppReflectAsCSV(...) CppReflection::reflect(CppReflection::CSV, #__VA_ARGS__, __VA_ARGS__)

/**
 * @brief Macro to call reflect with mode that was set using last *As* macros. 
 */
#define CppReflect(...) CppReflection::reflect(CppReflection::mode, #__VA_ARGS__, __VA_ARGS__)

/**
 * @brief Name-space to encompass each struct/variable/functions for * CppReflection library
 */
namespace CppReflection {

   /**
    * @brief Unnamed namespace to hide all the helper struct/variable/functions from outside.
    */
   namespace { 

      /**
       * @brief Defines modes that can be used to change output of reflection
       */
      enum modeList { List=0, CSV, ModeCount};

      /**
       * @brief Static variable inside namespace to store current mode being used
       */
      static modeList mode = List;

      /**
       * @brief Static depth variable to keep track of indentation that need to
       * be printed while printing any line as per depth of the sub-variable
       * that we are printing.
       */
      static int depth = -1;

      /**
       * @brief typedef to define delimiters depending on mode.
       */
      typedef std::array<std::string, ModeCount> delimList;

      /**
       * @brief Delimiter to be printed before variable-value pair.
       *
       * @return delimiter string
       */
      auto beginDelim = [&](){ 
         static const delimList delims = { "\t", "" };
         std::string ret = ""; auto loopCtr = depth;
         while(loopCtr--) ret += delims.at(mode); 
         return ret;};

      /**
       * @brief Delimiter to be printed between variable-value pair.
       *
       * @return delimiter string
       */
      auto middleDelim = [&](){ 
         static const delimList delims = { " = ", " , " };
         return delims.at(mode);};

      /**
       * @brief Delimiter to be printed after variable-value pair.
       *
       * @return delimiter string
       */
      auto endDelim = [&](){ 
         static const delimList delims = { "\n", " , " };
         return delims.at(mode);};

      /**
       * @brief Increment static variable depth
       */
      auto incrDepth = [&]() { depth++ ;};

      /**
       * @brief Decrement static variable depth
       */
      auto decrDepth = [&]() { depth-- ;};

      /**
       * @brief Struct to encapsulate constexpr traits of a datatype w.r.t a * stream
       *
       * @tparam TStream stream on which we are trying to print the variable
       * @tparam T datatype of the variable
       */
      template<typename TStream, typename T>
         struct stream_var {
            private:

               /**
                * @brief  TStream_ type has a << operator 
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::declval<TStream_>().operator<<(std::declval<T_>()), bool())
                  test_ltlt1(int) 
                  { return true; };

               /**
                * @brief  TStream_ type doesn't have a << operator 
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_ltlt1(...) 
                  { return false; };

               /**
                * @brief  std::<< operator works with TStream_ type and T_ * type
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(operator<<(std::declval<TStream_&>(), std::declval<T_>()), bool())
                  test_ltlt2(int) 
                  { return true; };

               /**
                * @brief  std::<< operator doesn't work with TStream_ type and T_ * type
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_ltlt2(...) 
                  { return false; };


               /**
                * @brief class T_ has an API called reflect
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::declval<T_>().reflect(), bool())
                  test_reflectAPI(int) 
                  { return true; };

               /**
                * @brief class T_ doesn't have an API called reflect
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_reflectAPI(...) 
                  { return false; };


               /**
                * @brief T_ type has a begin() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::declval<T_>().begin(), bool())
                  test_begin(int) 
                  { return true; };

               /**
                * @brief T_ type doesn't have a begin() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_begin(...) 
                  { return false; };

               /**
                * @brief T_ type has a end() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::declval<T_>().end(), bool())
                  test_end(int) 
                  { return true; };

               /**
                * @brief T_ type doesn't have a end() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_end(...) 
                  { return false; };

               /**
                * @brief T_ type has a size() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::declval<T_>().size(), bool())
                  test_size(int) 
                  { return true; };

               /**
                * @brief T_ type doesn't have a size() API
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_size(...) 
                  { return false; };

               /**
                * @brief T_ is a tuple type (std::tuple, std::pair, etc..)
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  decltype(std::tuple_size<T_>::value, bool())
                  test_tuple(int) 
                  { return true; };

               /**
                * @brief T_ is not a tuple type (std::tuple, std::pair, etc..)
                */
               template<typename TStream_, typename T_>
                  static constexpr 
                  bool
                  test_tuple(...) 
                  { return false; };



            public:
               static constexpr bool has_size = test_size<TStream, T>(int());
               static constexpr bool has_begin = test_begin<TStream, T>(int());
               static constexpr bool has_end = test_end<TStream, T>(int());
               static constexpr bool has_ltlt = ( test_ltlt1<TStream, T>(int()) || 
                                                  test_ltlt2<TStream, T>(int()));
               static constexpr bool has_reflect = test_reflectAPI<TStream, T>(int());
               static constexpr bool is_container = ( !has_ltlt && 
                                                       has_size && 
                                                       has_begin && 
                                                       has_end );
               static constexpr bool is_tuple = ( test_tuple<TStream, T>(int()) &&
                                                       !is_container ) ;
               static constexpr bool not_printable = !( is_container || 
                                                        has_ltlt || 
                                                        has_reflect || 
                                                        is_tuple );
         };

      //------------------------------------------------------------------------
      // Declaration
      //------------------------------------------------------------------------
      /**
       * @brief print variable that has an API named reflect
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::has_reflect, void>::type
         _processNameValue(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief print variable that has << operator defined
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::has_ltlt, void>::type
         _processNameValue(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief print variable of tuple type - terminating condition function.
       */
      template<typename T, std::size_t N = 0>
         typename std::enable_if< N == std::tuple_size<T>::value, void>::type
         reflectTuple(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief print variable of tuple type - incrementally print next elements.
       */
      template<typename T, std::size_t N = 0>
         typename std::enable_if< N < std::tuple_size<T>::value, void>::type
         reflectTuple(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief print variable of tuple type 
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::is_tuple, void>::type
         _processNameValue(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief print container variable 
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::is_container, void>::type
         _processNameValue(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief If an unsupported variable is used, SFINAE will invoke this API.
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::not_printable, void>::type
         _processNameValue(std::ostringstream& oBuffer, const std::string& varT, const T& t);

      /**
       * @brief terminating condition function when all variables are completed.
       */
      void _reflect(std::ostringstream& oBuffer, std::string nameStr);

      /**
       * @brief Pick one variable and print it, call recursively to print all variables
       */
      template<typename T, typename... TRest>
         void _reflect(std::ostringstream& oBuffer, std::string nameStr,
                       const T& t, const TRest&... tRest);

      //------------------------------------------------------------------------
      // Definition 
      //------------------------------------------------------------------------
      /**
       * @brief print variable that has an API named reflect
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::has_reflect, void>::type
         _processNameValue(std::ostringstream& oBuffer, 
                           const std::string& varT, const T& t)
         {
            oBuffer << beginDelim() << varT << " ( Object )" << endDelim() ;
            oBuffer << t.reflect();
         }

      /**
       * @brief print variable that has << operator defined
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::has_ltlt, void>::type
         _processNameValue(std::ostringstream& oBuffer, 
                           const std::string& varT, const T& t)
         {
            oBuffer << beginDelim() << varT << middleDelim() << t << endDelim() ;
         }

      /**
       * @brief print variable of tuple type - terminating condition function.
       */
      template<typename T, std::size_t N = 0>
         typename std::enable_if< N == std::tuple_size<T>::value, void>::type
         reflectTuple(std::ostringstream& oBuffer, 
                      const std::string& varT, const T& t)
         {
            (void) oBuffer; (void) varT; (void) t;
         }

      /**
       * @brief print variable of tuple type - incrementally print next elements.
       */
      template<typename T, std::size_t N = 0>
         typename std::enable_if< N < std::tuple_size<T>::value, void>::type
         reflectTuple(std::ostringstream& oBuffer, 
                      const std::string& varT, const T& t)
         {
            // std::get has to have a const at compile time !!!!
            // Iterating over tuple is an interesting problem
            std::string varTElem = varT + "[" + std::to_string(N) + "]";
            auto t_N = std::get<N>(t);
            _processNameValue(oBuffer, varTElem, t_N); 
            reflectTuple<T,N+1>(oBuffer, varT, t);
         }

      /**
       * @brief print variable of tuple type 
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::is_tuple, void>::type
         _processNameValue(std::ostringstream& oBuffer, 
                           const std::string& varT, const T& t)
         {
            oBuffer << beginDelim() << varT << " ( Tuple with " 
               << std::tuple_size<T>::value << " elements )" << endDelim() ;
            incrDepth();
            reflectTuple(oBuffer, varT, t);
            decrDepth();
         }

      /**
       * @brief print container variable 
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::is_container, void>::type
         _processNameValue(std::ostringstream& oBuffer, 
                           const std::string& varT, const T& t)
         {
            oBuffer << beginDelim() << varT << " ( Container with " 
               << t.size() << " elements )" << endDelim() ;
            incrDepth();
            int i = 0;
            for(auto it = t.begin(); it != t.end(); it++)
            {
               std::string varTElem = varT + "[" + std::to_string(i) + "]";
               _processNameValue(oBuffer, varTElem, (*it)); 
               i++;
            }
            decrDepth();
         }

      /**
       * @brief If an unsupported variable is used, SFINAE will invoke this API.
       */
      template<typename T>
         typename std::enable_if<stream_var<std::ostringstream, T>::not_printable, void>::type
         _processNameValue(std::ostringstream& oBuffer, 
                           const std::string& varT, const T& t)
         {
            (void) t;
            oBuffer << beginDelim() << varT <<" can't be printed. \n ";
         }

      /**
       * @brief terminating condition function when all variables are completed.
       */
      void _reflect(std::ostringstream& oBuffer,
                    std::string nameStr)
      {
         // below statements are to avoid having compiler unused warnings
         (void) oBuffer; (void) nameStr;
         return;
      }

      /**
       * @brief Pick one variable and print it, call recursively to print all variables
       */
      template<typename T, typename... TRest>
         void _reflect(std::ostringstream& oBuffer, 
                       std::string nameStr,
                       const T& t, const TRest&... tRest)
         {
            std::string varT = nameStr, varTRest = "", ret = "";

            auto pos = nameStr.find(',');
            if(pos != std::string::npos)
            {
               varT = nameStr.substr(0,pos);
               varTRest = nameStr.substr(pos+1);
            }

            varT.erase(std::remove(varT.begin(), varT.end(), ' '), varT.end());

            _processNameValue(oBuffer, varT, t);
            _reflect(oBuffer, varTRest, tRest...);
         }
   } // End of unnamed namespace

   /**
    * @brief reflect given list of variables.
    *
    * @param modeArg - mode set from macro
    * @param nameStr - "string" representation of all variables passed to macro
    * @param t - first variable passed to macro
    * @param tRest - all rest of the variables passed to macro
    *
    * @return 
    */
   template<typename T, typename... TRest>
      std::string reflect(const modeList modeArg, 
                          std::string nameStr,
                          const T& t, const TRest&... tRest)
      {
         incrDepth();
         mode = modeArg;
         std::ostringstream oBuffer;
         oBuffer << std::boolalpha;
         _reflect(oBuffer, nameStr, t, tRest...);
         decrDepth();
         std::string ret = oBuffer.str();
         return ret;
      }
}

#endif // CppReflection_h_
