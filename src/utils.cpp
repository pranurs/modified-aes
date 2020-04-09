#include "utils.hpp"

void leftCircularShift (int* arr, int shiftBy)
{
        std::reverse(arr, arr + shiftBy);
        std::reverse(arr + shiftBy, arr + 4);
        std::reverse(arr, arr + 4);
}


int multiply (int a, int b)
{
        int mult[8];

        mult[0] = a;

        int m = 0x1B;
        int tmp_a = a;
        int flag = 0;
        int x_i;
        int ans = 0;

        for (int i=1; i<=7; i++)
        {
                flag = 0;

                if (tmp_a & 0x80)
                        flag = 1;

                tmp_a <<= 1;
                tmp_a &= 0xFF;

                if (flag)
                        mult[i] = tmp_a ^ m;
                else
                        mult[i] = tmp_a;

                tmp_a = mult[i];
        }
        
        for (int i=0; i<=7; i++)
        {
                x_i = 1 << i;

                if (b & x_i)
                {
                        ans ^= mult[i];
                }
        }

        return ans;
}


int charToInt (char ch) 
{
        if (ch >= '0' && ch <= '9')
                return ch - '0';
        
        if (ch >= 'A' && ch <= 'F')
                return ch - 'A' + 10;

        if (ch >= 'a' && ch <= 'f')
                return ch - 'a' + 10;

        throw std::invalid_argument ("Invalid input string. Check that string is in hex format, and that it is of the proper length.");
}


void toHex (int* x)
{
        if (*x >= 0 && *x <= 9)
                *x = *x - 0 + '0';
        if (*x >= 10 && *x <= 15)
                *x = *x - 10 + 'a';
        return;
}


std::string xorHexString (std::string initial)
{
        std::string converted = "";
        int val;

        for (int i=0; i<initial.length(); i++)
        {
                val = charToInt (initial[i]);
                val ^= 0x0F;
                
                toHex (&val);

                converted += (char)(val);
        }
        
        return converted;
}


void hexStringToMatrixColumnwise (std::string text, std::vector < std::vector<int> > &state, int blockHeight)
{
        int row = 0, col = 0;

        for (int i=0; i < text.length(); i+=2)
        {
                state[row][col] = charToInt (text[i]) * 16 + charToInt (text[i+1]);

                row++;

                if (row%blockHeight == 0)
                {
                        row = 0;
                        col++;
                }
        }
}


void hexStringToMatrixBlockwise (std::string text, std::vector< std::vector<int> > &state)
{
        int row=0, col=0, k=0;

        for (int row=0; row<state.size(); row+=4)
        {
                for (int col=0; col<state[0].size(); col+=4)
                {
                        for (int i=0; i<4; i++)
                        {
                                for (int j=0; j<4; j++)
                                {
                                        state[row+i][col+j] = charToInt (text[k]) * 16 + charToInt (text[k+1]);
                                        k+=2;
                                }
                        }
                }
        }
}


std::string matrixToHexStringColumnwise (std::vector < std::vector<int> > &state)
{
        std::string converted = "";
        int temp1, temp2;

        for (int col=0; col<state[0].size(); col++)
        {
                for (int row=0; row<state.size(); row++)
                {
                        temp1 = (state[row][col] & 0xF0) >> 4;
                        temp2 = state[row][col] & 0x0F;

                        toHex (&temp1);
                        toHex (&temp2);

                        converted += (char)(temp1);
                        converted += (char)(temp2);
                }
        }

        return converted;
}


std::string matrixToHexStringBlockwise (std::vector< std::vector<int> > &state)
{
        std::string converted = "";
        int temp1, temp2;

        for (int row=0; row<state.size(); row+=4)
        {
                for (int col=0; col<state[0].size(); col+=4)
                {
                        for (int i=0; i<4; i++)
                        {
                                for (int j=0; j<4; j++)
                                {
                                        temp1 = (state[row+i][col+j] & 0xF0) >> 4;
                                        temp2 = (state[row+i][col+j] & 0x0F);

                                        toHex (&temp1);
                                        toHex (&temp2);

                                        converted += (char)(temp1);
                                        converted += (char)(temp2);
                                }
                        }
                }
        }

        return converted;
}


void buildMatrixFromTextFile (std::ifstream &file, std::vector < std::vector<int> > &state)
{
        int x;

        for(int i=0; i<state.size(); i++)
        {
                for(int j=0; j<state[0].size(); j++)
                {
                        file >> x;
                        state[i][j] = x;
                }
        } 
        file.close();
}


void buildTextFileFromMatrix (std::ofstream &file, std::vector < std::vector<int> > &state)
{
        for(int i=0; i<state.size(); i++)
        {
                for(int j=0; j<state[0].size(); j++)
                {
                        file << state[i][j] <<" ";
                }

                file << "\n";
        }
        file.close();
}
