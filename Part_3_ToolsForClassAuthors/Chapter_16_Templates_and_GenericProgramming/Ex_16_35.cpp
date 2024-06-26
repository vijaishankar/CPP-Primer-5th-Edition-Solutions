/************************************************************************************************************************************************************
 * @file Ex_16_35.cpp
 * @brief Exercise 16.35: Which, if any, of the following calls are errors? If the call is legal, what is the type of
 *  T? If the call is not legal, what is the problem?
 * template <typename T> T calc(T, int);
 * template <typename T> T fcn(T, T);
 * double d; float f; char c;
 * (a) calc(c, ’c’); (b) calc(d, f);
 * (c) fcn(c, ’c’); (d) fcn(d, f);
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * template <typename T> T calc(T, int);    
 * template <typename T> T fcn(T, T);       
 * double d; float f; char c;           
 * (a) calc(c, ’c’);  //  legal : T is char
 * (b) calc(d, f);    //  legal : T is double, calc template is used with T as double deduced from 1st argument, and as the parameter is not defined by template type
 *                    //         normal arithmatic conversion happens .                            
 * (c) fcn(c, ’c’);   //  legal : T is char
 * (d) fcn(d, f);     //  illegal : arguments types are different double and float, arithmatic conversions don't happen for
 *                    //            deducing template parameters.
 * 
 *************************************************************************************************************************************************************/

