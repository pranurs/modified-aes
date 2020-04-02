#include "aes.hpp"
#include "lookuptables.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>

void buildMatrixFromTextFile (std::ifstream &file, std::vector < std::vector<int> > &state)
{
        int x;

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        file >> x;
                        state[i][j] = x;
                }
        } 

        file.close();
}

void buildTextFileFromMatrix (std::ofstream &file, std::vector < std::vector<int> > &state)
{
        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        file << state[i][j] <<" ";
                }

                file << "\n";
        }

        file.close();
}

int main()
{
        // std::string message = "0123456789abcdeffedcba9876543210";

        std::string key = "1234567890d9e3452cb7add6af7f6798";

        AES obj = AES (128);

        std::vector < std::vector<int> > state1 (128, std::vector<int> (128));
        std::vector < std::vector<int> > state2 (128, std::vector<int> (128));
        std::vector < std::vector<int> > state3 (128, std::vector<int> (128));

        std::ifstream myfile1, myfile2, myfile3;

        myfile1.open("Text_Files/Mickey/Original/mickey1.txt");
        myfile2.open("Text_Files/Mickey/Original/mickey2.txt");
        myfile3.open("Text_Files/Mickey/Original/mickey3.txt");

        std::ofstream encfile1 ("Text_Files/Mickey/MAES/Encrypted/mickeyMAES1.txt");
        std::ofstream encfile2 ("Text_Files/Mickey/MAES/Encrypted/mickeyMAES2.txt");
        std::ofstream encfile3 ("Text_Files/Mickey/MAES/Encrypted/mickeyMAES3.txt");

        std::ofstream decfile1 ("Text_Files/Mickey/MAES/Decrypted/mickeyMDec1.txt");
        std::ofstream decfile2 ("Text_Files/Mickey/MAES/Decrypted/mickeyMDec2.txt");
        std::ofstream decfile3 ("Text_Files/Mickey/MAES/Decrypted/mickeyMDec3.txt");
        
        buildMatrixFromTextFile (myfile1, state1);
        buildMatrixFromTextFile (myfile2, state2);
        buildMatrixFromTextFile (myfile3, state3);

        std::string imagestring1 = matrixToHexString(state1);
        std::string imagestring2 = matrixToHexString(state2);
        std::string imagestring3 = matrixToHexString(state3);

        // std::cout<<"ENCRYPTING...\n\n";

        std::string ciphertext1 = obj.encryptMessage (imagestring1, key, 1);
        std::string ciphertext2 = obj.encryptMessage (imagestring2, key, 1);
        std::string ciphertext3 = obj.encryptMessage (imagestring3, key, 1);

        // std::cout<<"Coded length : "<<ciphertext.length()<<"\n\n\n";

        hexStringToMatrix (ciphertext1, state1, 128);
        hexStringToMatrix (ciphertext2, state2, 128);
        hexStringToMatrix (ciphertext3, state3, 128);

        // std::cout<<state1.size()<<" "<<state1[0].size()<<"\n";

        // Storing encrypted files

        buildTextFileFromMatrix (encfile1, state1);
        buildTextFileFromMatrix (encfile2, state2);
        buildTextFileFromMatrix (encfile3, state3);

        // std::cout<<"DECRYPTING...\n\n";

        std::string decoded1 = obj.decryptCipher (ciphertext1, key, 1);
        std::string decoded2 = obj.decryptCipher (ciphertext2, key, 1);
        std::string decoded3 = obj.decryptCipher (ciphertext3, key, 1);

        hexStringToMatrix (decoded1, state1, 128);
        hexStringToMatrix (decoded2, state2, 128);
        hexStringToMatrix (decoded3, state3, 128);

        // Storing decrypted files

        buildTextFileFromMatrix (decfile1, state1);
        buildTextFileFromMatrix (decfile2, state2);
        buildTextFileFromMatrix (decfile3, state3);
        
        return 0;
}