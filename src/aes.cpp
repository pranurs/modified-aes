#include "aes.hpp"
#include "lookuptables.hpp"
#include "utils.hpp"


AES :: AES (int keyLength)
{
        Nb = 4;
        encrypt = 1;

        switch (keyLength)
        {
                case 128 :

                        Nk = 4;
                        Nr = 10;
                        break;

                case 192 :

                        Nk = 6;
                        Nr = 12;
                        break;

                case 256 :

                        Nk = 8;
                        Nr = 14;
                        break;

                default :

                        throw "Incorrect Key Length Chosen";

        }
}


void AES :: printStateInHex (std::vector < std::vector<int> > &state)
{
        for (int i=0; i<4; i++)
        {
                for (int j=0; j<Nb; j++)
                {
                        std::cout<<std::hex<<state[i][j]<<" ";
                }
                std::cout<<std::endl;
        }
        std::cout<<std::endl;
}


void AES :: shiftRow (std::vector < std::vector<int> > &state, int rowIndex, int shiftBy, int encrypt = 1)
{
        if(!encrypt)
                shiftBy = Nb - shiftBy;

        leftCircularShift (&state[rowIndex][0], shiftBy);
}


void AES :: keyExpansion (std::vector < std::vector<int> > &initialKey, std::vector < std::vector<int> > &expandedKey)
{
        int temp[4];
        int sRow, sCol;

        for (int col=0; col<Nk; col++)
        {
                for (int row=0; row<4; row++)
                {
                        expandedKey[row][col] = initialKey[row][col];
                }
        }

        for (int col=Nk; col<(Nk * (Nr+1)); col++)
        {
                for (int row=0; row<4; row++)
                {
                        temp[row] = expandedKey[row][col-1];
                }

                if (col%Nk == 0)
                {
                        leftCircularShift (temp, 1);

                        for (int i=0; i<4; i++)
                        {
                                sRow = temp[i] >> 4;
                                sCol = temp[i] & 0x0F;
                                temp[i] = c_sBox[sRow][sCol];
                        }

                        temp[0] ^= c_rCon[col/4 - 1];
                }

                for (int row=0; row<4; row++)
                {
                        expandedKey[row][col] = expandedKey[row][col-4] ^ temp[row];
                }
        }
}


void AES :: getCurrKey (int round, std::vector < std::vector<int> > &currKey, std::vector < std::vector<int> > &expandedKey, int encrypt = 1)
{
        if(!encrypt)
                round = Nr - round;

        for (int row=0; row<4; row++)
        {
                for(int col=0; col<Nk; col++)
                {
                        currKey[row][col] = expandedKey[row][(round * Nk) + col];
                }
        }
}


void AES :: subBytes (std::vector < std::vector<int> > &state, int encrypt = 1)
{
        int sRow, sCol;

        for (int i=0; i<4; i++)
        {
                for (int j=0; j<4; j++)
                {
                       sRow = state[i][j] >> 4;
                       sCol = state[i][j] & 0x0F;

                       if (encrypt)
                                state[i][j] = c_sBox[sRow][sCol];

                        else
                                state[i][j] = c_inverseSBox[sRow][sCol];

                }
        }

}


void AES :: originalShiftRows (std::vector < std::vector<int> > &state, int encrypt = 1)
{
        int shiftBy;

        for (int i=1; i<4; i++)
        {
                shiftBy = i;

                shiftRow (state, i, shiftBy, encrypt);
        }

}


void AES :: modifiedShiftRows (std::vector < std::vector<int> > &state, int encrypt = 1)
{
        int shiftBy;

        if (state[0][0] % 2)
        {
                // Circularly shifting second row 1 byte to the left (encryption) or right (decryption)

                shiftRow (state, 1, 1, encrypt);

                // Circularly shifting fourth row 3 bytes to the left (encryption) or right (decryption)

                shiftRow (state, 3, 3, encrypt);
        }

        else
        {
                //Circularly shifting second row 3 bytes to the right, i.e. (Nb-3) = 1 byte to the left (encryption), or 3 bytes to the left (decryption)

                shiftRow (state, 1, Nb - 3, encrypt);

                //Circularly shifting third row 2 bytes to the right, i.e. (Nb-2) = 2 bytes to the left (encryption), or 2 bytes to the left (decryption)

                shiftRow (state, 2, Nb - 2, encrypt);

        }
        
}


void AES :: mixColumns (std::vector < std::vector<int> > &state, int encrypt = 1)
{
        int newValue;
        std::vector< std::vector<int> >  newState (4, std::vector<int>(4));

        for (int col=0; col<Nb; col++)
        {
                for (int colEntry=0; colEntry<4; colEntry++)
                {
                        newValue = 0;

                        for (int row=0; row<4; row++)
                        {
                                // std::cout<<std::hex<<c_forwardMatrix[colEntry][row]<<" * "<<state[row][col]<<"\n";
                                if (encrypt)
                                        newValue ^= multiply (c_forwardMatrix[colEntry][row], state[row][col]);

                                else
                                        newValue ^= multiply (c_inverseMatrix[colEntry][row], state[row][col]);
                        }

                        // std::cout<<"-------"<<"\n";

                        newState[colEntry][col] = newValue;
                }
        }

        for (int i=0; i<4; i++)
        {
                for (int j=0; j<4; j++)
                {
                        state[i][j] = newState[i][j];
                }
        }

}


void AES :: addRoundKey (std::vector < std::vector<int> > &state, std::vector < std::vector<int> > &roundKey, int encrypt = 1)
{
        for (int i=0; i<4; i++)
        {
                for (int j=0; j<Nb; j++)
                {
                        state[i][j] ^= roundKey[i][j];
                }
        }

}


void AES :: transform (std::vector < std::vector<int> > &state, std::vector < std::vector<int> > &initialKey, int encrypt = 1)
{
        std::vector < std::vector<int> > expandedKey (4, std::vector<int> (Nk * (Nr+1)));
        std::vector < std::vector<int> > currKey (4, std::vector<int> (4));

        keyExpansion (initialKey, expandedKey);

        getCurrKey (0, currKey, expandedKey, encrypt);
        addRoundKey (state, currKey, encrypt);

        int round = 1;

        while (round < 10)
        {
                // std::cout<<"entered "<<round<<"\n";
                getCurrKey (round, currKey, expandedKey, encrypt);

                subBytes (state, encrypt);


                originalShiftRows (state, encrypt);

                mixColumns (state, encrypt);

                // std::cout<<"ROUND = "<<round<<"\n";

                if(!encrypt)
                        mixColumns (currKey, encrypt);

                addRoundKey (state, currKey, encrypt);

                round++;
        }

        getCurrKey (round, currKey, expandedKey, encrypt);

        subBytes (state, encrypt);

        originalShiftRows (state, encrypt);

        addRoundKey (state, currKey, encrypt);

}

void AES :: modifiedTransform (std::vector < std::vector<int> > &state, std::vector < std::vector<int> > &initialKey, int encrypt = 1)
{
        std::vector < std::vector<int> > expandedKey (4, std::vector<int> (Nk * (Nr+1)));
        std::vector < std::vector<int> > currKey (4, std::vector<int> (4));

        keyExpansion (initialKey, expandedKey);

        getCurrKey (0, currKey, expandedKey, encrypt);
        addRoundKey (state, currKey, encrypt);

        int round = 1;

        while (round < 10)
        {
                // std::cout<<"entered "<<round<<"\n";
                getCurrKey (round, currKey, expandedKey, encrypt);

                if(encrypt)
                {
                        subBytes (state, encrypt);

                        modifiedShiftRows (state, encrypt);

                }
                else
                {
                        modifiedShiftRows (state, encrypt);

                        subBytes (state, encrypt);
                }
                
                mixColumns (state, encrypt);

                // std::cout<<"ROUND = "<<round<<"\n";

                if(!encrypt)
                        mixColumns (currKey, encrypt);

                addRoundKey (state, currKey, encrypt);

                round++;
        }

        getCurrKey (round, currKey, expandedKey, encrypt);

        if(encrypt)
        {
                subBytes (state, encrypt);

                modifiedShiftRows (state, encrypt);
        }
        else
        {
                modifiedShiftRows (state, encrypt);

                subBytes (state, encrypt);
        }
        

        addRoundKey (state, currKey, encrypt);

}

std::string AES :: encryptMessage (std::string plaintext, std::string key, int modifiedAES = 0)
{
        std::vector < std::vector<int> > initialKey (4, std::vector<int> (Nk));
        
        hexStringToMatrix (key, initialKey, 4);
        
        encrypt = 1;

        std::string encryptedString = "";

        for (int i=0; i < plaintext.length(); i+=32)
        {
                std::vector < std::vector<int> > state (4, std::vector<int> (Nb));

                hexStringToMatrix (plaintext.substr(i,32), state, 4);

                if (modifiedAES)
                        modifiedTransform (state, initialKey, encrypt);
                
                else
                        transform (state, initialKey, encrypt);

                encryptedString += matrixToHexString (state);
        }

        return encryptedString;
}


std::string AES :: decryptCipher (std::string ciphertext, std::string key, int modifiedAES = 0)
{
        std::vector < std::vector<int> > initialKey (4, std::vector<int> (Nk));
        
        hexStringToMatrix (key, initialKey, 4);
        
        encrypt = 0;

        std::string decryptedString = "";

        for (int i=0; i < ciphertext.length(); i+=32)
        {
                std::vector < std::vector<int> > state (4, std::vector<int> (Nb));

                hexStringToMatrix (ciphertext.substr(i,32), state, 4);

                if (modifiedAES)
                        modifiedTransform (state, initialKey, encrypt);
                
                else
                        transform (state, initialKey, encrypt);

                decryptedString += matrixToHexString (state);
        }

        return decryptedString;
}









