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
                {
                        mult[i] = tmp_a ^ m;
                }
                else
                {
                        mult[i] = tmp_a;
                }
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

        throw std::invalid_argument ("Invalid input string.");
}


void toHex (int* x)
{
        if (*x >= 0 && *x <= 9)
                *x = *x - 0 + '0';
        if (*x >= 10 && *x <= 15)
        {
                *x = *x - 10 + 'a';
        }
        return;
}


void hexStringToMatrix (std::string plaintext, std::vector < std::vector<int> > &state, int blockHeight)
{
        int row = 0, col = 0;

        for (int i=0; i < plaintext.length(); i+=2)
        {
                state[row][col] = charToInt (plaintext[i]) * 16 + charToInt (plaintext[i+1]);

                row++;

                if (row%blockHeight == 0)
                {
                        row = 0;
                        col++;
                }
        }
}

std::string matrixToHexString (std::vector < std::vector<int> > &state)
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