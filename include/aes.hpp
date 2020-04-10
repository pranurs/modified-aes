/** 
 * @file aes.hpp
 * @brief contains a class AES for performing encryption and decryption using AES, MAES, and SMAES (proposed)
 * @author pranurs
 */
 
#ifndef AES_H

        #define AES_H

        #include<iostream>
        #include<string>
        #include<algorithm>
        #include<vector>

        /** 
         * @brief A Class used to perform AES, MAES, and SMAES (proposed) on the input object. 
         */
        class AES
        {
                public:

                        /**
                         * @brief Constructor to initialize private variables
                         */
                        AES (int keyLength = 128);

                        /**
                         * @brief Encrypts input hexadecimal string using AES or MAES
                         * 
                         * @param plaintext Input message hexadecimal string
                         * @param key Hexadecimal key used for encryption
                         * @param modifiedAES Indicator variable for MAES
                         * @returns Encrypted hexadecimal string
                         */
                        std::string encryptMessage (std::string plaintext, std::string key, int modifiedAES);

                        /**
                        * @brief Decrypts the input hexadecimal string using AES or MAES
                        * 
                        * @param ciphertext Input hexadecimal string
                        * @param key Hexadecimal key used for encryption
                        * @param modifiedAES Indicator variable for MAES
                        * @returns Decrypted hexadecimal string
                        */ 
                        std::string decryptCipher (std::string ciphertext, std::string key, int modifiedAES);

                        /**
                        * @brief Encrypts the input hexadecimal string using SMAES (our proposed method)
                        * 
                        * @param plaintext Input hexadecimal string
                        * @param key Hexadecimal key used for encryption
                        * @param imageHeight Height of input image in pixels
                        * @param imageWidth Width of input image in pixels
                        * @param modifiedAES Indicator variable for MAES
                        * @returns Encrypted hexadecimal string
                        */
                        std::string proposedEncryptMessage (std::string plaintext, std::string key, int imageHeight, int imageWidth, int modifiedAES);

                        /**
                        * @brief Decrypts the input hexadecimal string using SMAES (our proposed method)
                        * 
                        * @param ciphertext Input hexadecimal string
                        * @param key Hexadecimal key used for encryption
                        * @param imageHeight Height of input image in pixels
                        * @param imageWidth Width of input image in pixels
                        * @param modifiedAES Indicator variable for MAES
                        * @returns Decrypted hexadecimal string
                        */
                        std::string proposedDecryptCipher (std::string ciphertext, std::string key, int imageHeight, int imageWidth, int modifiedAES);

                private:

                        int Nk; /// Number of columns (words) in the key block
                        int Nb; /// Number of columns (words) in an AES block
                        int Nr; /// Number of rounds performed by the algorithm
                        int encrypt; /// Indicator variable storing whether encryption of a message, or decryption of a ciphertext, is to be performed

                        /**
                         * @brief Shifts the specified row of the state matrix
                         * 
                         * @param[out] state State matrix on which shift is to be performed
                         * @param[in] rowIndex Index of row to be shifted
                         * @param[in] shiftBy Number of places by which row is to be shifted left in a circular way
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void shiftRow (std::vector < std::vector<int> > &state, int rowIndex, int shiftBy, int encrypt);
                        
                        /**
                         * @brief Performs keyExpansion on the input key as per AES
                         * 
                         * @param[out] expandedKey Matrix with keys for all rounds after performing keyExpansion
                         * @param[in] initialKey Input key
                         */ 
                        void keyExpansion (std::vector < std::vector<int> > &initialKey, std::vector < std::vector<int> > &expandedKey);
                        
                        /**
                         * @brief Obtains the key required for the current round of encryption/decryption
                         * 
                         * @param[out] currKey Stores the current key required
                         * @param[in] round Current round number
                         * @param[in] expandedKey Matrix with keys for all rounds after performing keyExpansion
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void getCurrKey (int round, std::vector < std::vector<int> > &currKey, std::vector < std::vector<int> > &expandedKey, int encrypt);
                        
                        /**
                         * @brief Performs subBytes operation on the state matrix
                         * 
                         * @param[out] state State matrix
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void subBytes (std::vector < std::vector<int> > &state, int encrypt);

                        /**
                         * @brief Performs the original shiftRows operation as per AES, on the state matrix
                         * 
                         * @param[out] state State matrix on which shiftRows is to be performed
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void originalShiftRows (std::vector < std::vector<int> > &state, int encrypt);

                        /**
                         * @brief Performs the modified shiftRows operation as per MAES, on the state matrix
                         * 
                         * @param[out] state State matrix on which modified shiftRows is to be performed
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void modifiedShiftRows (std::vector < std::vector<int> > &state, int encrypt);

                        /**
                         * @brief Performs the mixColumns operation as per AES, on the state matrix
                         * 
                         * @param[out] state State matrix on which mixColumns is to be performed
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void mixColumns (std::vector < std::vector<int> > &state, int encrypt);

                        /**
                         * @brief Performs the addRoundKey operation as per AES, on the state matrix
                         * 
                         * @param[out] state State matrix on which addRoundKey is to be performed
                         * @param[in] roundKey Key to be used for addRoundKey operation, resulting in XORing the key with the state matrix
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void addRoundKey (std::vector < std::vector<int> > &state, std::vector < std::vector<int> > &roundKey, int encrypt);

                        /**
                         * @brief Performs the rounds of encryption or decryption of the AES algorithm 
                         * 
                         * @param[out] state State matrix on which AES encryption or decryption is to be performed
                         * @param[in] initialKey Key used for encryption or decryption
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void transform (std::vector < std::vector<int> >  &state, std::vector < std::vector<int> > &initialKey, int encrypt);

                        /**
                         * @brief Performs the rounds of encryption or decryption of the MAES algorithm 
                         * 
                         * @param[out] state State matrix on which MAES encryption or decryption is to be performed
                         * @param[in] initialKey Key used for encryption or decryption
                         * @param[in] encrypt Indicator variable for encryption/decryption
                         */
                        void modifiedTransform (std::vector < std::vector<int> >  &state, std::vector < std::vector<int> > &initialKey, int encrypt);

                        /**
                         * @brief Shuffles the final output of the MAES algorithm to give the final SMAES (proposed) output
                         * 
                         * @details Shuffles blocks of 4x4 in a metablock of size 64x64 pixels
                         * Shuffling is done as per the lookup tables c_sBox and c_inverseSBox used in AES itself, to ensure robustness
                         * 
                         * @param initial Hexadecimal string (output of MAES) to be shuffled
                         * @param imageHeight Height of image in pixels
                         * @param imageWidth Width of image in pixels
                         * @param shuffle Indicator variable for shuffling/unshuffling
                         * @returns Final shuffled hexadecimal string which is the output of SMAES
                         */
                        std::string shuffleMatrix (std::string initial, int imageHeight, int imageWidth, int shuffle);
        };

#endif
