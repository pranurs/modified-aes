#ifndef AES_H

        #define AES_H

        #include<iostream>
        #include<string>
        #include<algorithm>
        #include<vector>

        class AES
        {
                public:

                        AES (int keyLength = 128);

                        std::string encryptMessage (std::string plaintext, std::string key, int modifiedAES);
                        
                        std::string decryptCipher (std::string ciphertext, std::string key, int modifiedAES);

                private:

                        int Nk; /// Number of columns (words) in the key block
                        int Nb; /// Number of columns (words) in an AES block
                        int Nr; /// Number of rounds performed by the algorithm
                        int encrypt; /// Indicator variable storing whether encryption of a message, or decryption of a ciphertext, is to be performed

                        void printStateInHex (std::vector < std::vector<int> > &state);

                        void shiftRow (std::vector < std::vector<int> > &state, int rowIndex, int shiftBy, int encrypt);
                        
                        void keyExpansion (std::vector < std::vector<int> > &initialKey, std::vector < std::vector<int> > &expandedKey);
                        
                        void getCurrKey (int round, std::vector < std::vector<int> > &currKey, std::vector < std::vector<int> > &expandedKey, int encrypt);
                        
                        void subBytes (std::vector < std::vector<int> > &state, int encrypt);

                        void originalShiftRows (std::vector < std::vector<int> > &state, int encrypt);

                        void modifiedShiftRows (std::vector < std::vector<int> > &state, int encrypt);

                        void mixColumns (std::vector < std::vector<int> > &state, int encrypt);

                        void addRoundKey (std::vector < std::vector<int> > &state, std::vector < std::vector<int> > &roundKey, int encrypt);

                        void transform (std::vector < std::vector<int> >  &state, std::vector < std::vector<int> > &initialKey, int encrypt);

                        void modifiedTransform (std::vector < std::vector<int> >  &state, std::vector < std::vector<int> > &initialKey, int encrypt);
        };

#endif
