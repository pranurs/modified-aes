#include "aes.hpp"
#include "lookuptables.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>


int main()
{
        // std::string message = "0123456789abcdeffedcba9876543210";
        std::string key = "1234567890d9e3452cb7add6af7f6798";
        // std::string bigMessage = "";
        AES obj = AES (128);
        // std::cout<<message<<"\n";

        std::vector < std::vector<int> > state1 (128, std::vector<int> (128));
        std::vector < std::vector<int> > state2 (128, std::vector<int> (128));
        std::vector < std::vector<int> > state3 (128, std::vector<int> (128));


        std::ifstream myfile1, myfile2, myfile3;
        myfile1.open("mickey1.txt");
        myfile2.open("mickey2.txt");
        myfile3.open("mickey3.txt");

        std::ofstream encfile1 ("mickeyMAES1.txt");
        std::ofstream encfile2 ("mickeyMAES2.txt");
        std::ofstream encfile3 ("mickeyMAES3.txt");


        std::ofstream decfile1 ("mickeyMDec1.txt");
        std::ofstream decfile2 ("mickeyMDec2.txt");
        std::ofstream decfile3 ("mickeyMDec3.txt");
        

        int x;
        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        myfile1>>x;
                        state1[i][j] = x;
                }
        } 

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        myfile2>>x;
                        state2[i][j] = x;
                }
        } 

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        myfile3>>x;
                        state3[i][j] = x;
                }
        } 

        myfile1.close();
        myfile2.close();
        myfile3.close();


        std::string imagestring1 = matrixToHexString(state1);
        std::string imagestring2 = matrixToHexString(state2);
        std::string imagestring3 = matrixToHexString(state3);

        // std::cout<<"ENCRYPTING...\n\n";
        std::string ciphertext1 = obj.encryptMessage (imagestring1, key, 0);
        std::string ciphertext2 = obj.encryptMessage (imagestring2, key, 0);
        std::string ciphertext3 = obj.encryptMessage (imagestring3, key, 0);

        // std::cout<<"Coded length : "<<ciphertext.length()<<"\n\n\n";

        hexStringToMatrix (ciphertext1, state1, 128);
        hexStringToMatrix (ciphertext2, state2, 128);
        hexStringToMatrix (ciphertext3, state3, 128);


        // std::cout<<state1.size()<<" "<<state1[0].size()<<"\n";

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        encfile1 << state1[i][j] <<" ";
                }

                encfile1 << "\n";
        }

        encfile1.close();

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        encfile2 << state2[i][j] <<" ";
                }

                encfile2 << "\n";
        }

        encfile2.close();

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        encfile3 << state3[i][j] <<" ";
                }

                encfile3 << "\n";
        }

        encfile3.close();



        // std::cout<<"DECRYPTING...\n\n";
        std::string decoded1 = obj.decryptCipher (ciphertext1, key, 0);
        std::string decoded2 = obj.decryptCipher (ciphertext2, key, 0);
        std::string decoded3 = obj.decryptCipher (ciphertext3, key, 0);

        hexStringToMatrix (decoded1, state1, 128);
        hexStringToMatrix (decoded2, state2, 128);
        hexStringToMatrix (decoded3, state3, 128);

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        decfile1 << state1[i][j] <<" ";
                }

                decfile1 << "\n";
        }

        decfile1.close();

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        decfile2 << state2[i][j] <<" ";
                }

                decfile2 << "\n";
        }

        decfile2.close();

        for(int i=0; i<128; i++)
        {
                for(int j=0; j<128; j++)
                {
                        decfile3 << state3[i][j] <<" ";
                }

                decfile3 << "\n";
        }

        decfile3.close();


        return 0;
}