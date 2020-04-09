/**
 * @file utils.hpp
 * @brief contains utility functions used in AES operations, or for conversion between matrix, string, and file 
 * @author pranurs
 */

#ifndef UTILS_H

        #define UTILS_H

                #include <stdexcept>
                #include <string>
                #include <vector>
                #include <algorithm>
                #include <fstream>

                /**
                 * @brief Shifts input array circularly to the left by the specified number of places
                 *
                 * @param[out] arr Array to be shifted
                 * @param[in] shiftBy The number of places by which array is to be shifted
                 */
                void leftCircularShift (int* arr, int shiftBy);

                /**
                 * @brief Performs multiplication in GF(2^8)
                 *
                 * @param a Operand for multiplication in GF(2^8)
                 * @param b Operand for multiplication in GF(2^8) 
                 * @returns Result of multiplication in GF(2^8)
                 */
                int multiply (int a, int b);

                /**
                 * @brief Converts hexadecimal number represented as a character to decimal integer format
                 *
                 * @param ch Hexadecimal character to be converted
                 * @returns Decimal integer after conversion
                 */
                int charToInt (char ch);

                /**
                 * @brief Converts an integer from 0-15 into its equivalent hexadecimal form
                 *
                 * @param[out] x Integer to be converted into hexadecimal form
                 */
                void toHex (int* x);

                /**
                 * @brief Returns the input hexadecimal string by performing a XOR operation with 1, for 
                 * each of its bits. Thus, it "inverts" the input string.
                 *
                 * @param initial String to be inverted by performing XOR
                 * @returns The inverted final string
                 */
                std::string xorHexString (std::string initial);
                
                /**
                 * @brief Converts input hexadecimal string to a matrix, columns filled first
                 *
                 * @param[in] text Input hexadecimal string
                 * @param[out] state Matrix to be filled
                 * @param blockHeight Column height of matrix
                 */
                void hexStringToMatrixColumnwise (std::string text, std::vector< std::vector<int> > &state, int blockHeight);

                /**
                 * @brief Converts input hexadecimal string to a matrix, blocks of 128 bits (4x4) filled first
                 *
                 * @param[in] text Input hexadecimal string
                 * @param[out] state Matrix to be filled
                 */
                void hexStringToMatrixBlockwise (std::string text, std::vector< std::vector<int> > &state);

                /**
                 * @brief Converts input matrix into hexadecimal string, columns of matrix appended first
                 * after conversion
                 *
                 * @param state Matrix to be converted
                 * @returns Final hexadecimal string
                 */
                std::string matrixToHexStringColumnwise (std::vector< std::vector <int> > &state);

                /**
                 * @brief Converts input matrix into hexadecimal string, blocks of 128 bits (4x4) of matrix appended 
                 * first after conversion
                 *
                 * @param state Matrix to be converted
                 * @returns Final hexadecimal string
                 */
                std::string matrixToHexStringBlockwise (std::vector< std::vector <int> > &state);

                /**
                 * @brief Builds matrix from a text file
                 *
                 * @param[in] file Text file to be used for construction the matrix
                 * @param[out] state Matrix that stores information in the text file
                 */
                void buildMatrixFromTextFile (std::ifstream &file, std::vector < std::vector<int> > &state);

                /**
                 * @brief Stores input matrix as a text file
                 *
                 * @param[in] state Matrix to be stored
                 * @param[out] file File in which matrix is stored
                 */
                void buildTextFileFromMatrix (std::ofstream &file, std::vector < std::vector<int> > &state);

#endif
