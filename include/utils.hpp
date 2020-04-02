#ifndef UTILS_H

        #define UTILS_H

                #include <stdexcept>
                #include <string>
                #include <vector>
                #include <algorithm>

                void leftCircularShift (int* arr, int shiftBy);

                int multiply (int a, int b);

                int charToInt (char ch);

                void toHex (int* x);

                void hexStringToMatrix (std::string plaintext, std::vector < std::vector<int> > &state, int blockHeight);

                std::string matrixToHexString (std::vector < std::vector <int> > &state);
        

#endif
