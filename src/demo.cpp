#include "aes.hpp"
#include "lookuptables.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>

/**
 * @brief Encrypts the text file stored in specified location, and 
 * saves the encrypted text file as per the specified output path.
 *
 * @param obj Instance of the AES class
 * @param key Key used for encryption and decryption 
 * @param inputFilePath Specifies the location of input text file
 * @param outputFilePath Specifies the location of output text file
 * @param method Technique to be used for encryption. May be: AES, MAES, SMAES (Our proposed method)
 * @param imageHeight Height of image in pixels
 * @param imageWidth Width of image in pixels
 */
void saveEncryptedTextFile (AES obj, std::string key, std::string inputFilePath, std::string outputFilePath, std::string method = "AES", int imageHeight = 0, int imageWidth = 0)
{
        std::ifstream input;
        input.open (inputFilePath);
        
        std::ofstream output (outputFilePath);

        std::vector < std::vector<int> > state (imageHeight, std::vector<int> (imageWidth));

        buildMatrixFromTextFile (input, state);

        std::string imagestring = matrixToHexStringBlockwise (state);
        std::string ciphertext;

        if (method == "AES")
                ciphertext = obj.encryptMessage (imagestring, key, 0);
        else if (method == "MAES")
                ciphertext = obj.encryptMessage (imagestring, key, 1);
        else
                ciphertext = obj.proposedEncryptMessage (imagestring, key, imageHeight, imageWidth, 1);

        hexStringToMatrixBlockwise (ciphertext, state);

        buildTextFileFromMatrix (output, state);
}

/**
 * @brief Decrypts the text file stored in specified location, and 
 * saves the decrypted text file as per the specified output path.
 *
 * @param obj Instance of the AES class
 * @param key Key used for encryption and decryption 
 * @param inputFilePath Specifies the location of input text file
 * @param outputFilePath Specifies the location of output text file
 * @param method Technique to be used for decryption. May be: AES, MAES, SMAES (Our proposed method)
 * @param imageHeight Height of image in pixels
 * @param imageWidth Width of image in pixels
 */
void saveDecryptedTextFile (AES obj, std::string key, std::string inputFilePath, std::string outputFilePath, std::string method = "AES", int imageHeight = 0, int imageWidth = 0)
{
        std::ifstream input;
        input.open (inputFilePath);
        
        std::ofstream output (outputFilePath);

        std::vector < std::vector<int> > state (imageHeight, std::vector<int> (imageWidth));

        buildMatrixFromTextFile (input, state);

        std::string ciphertext = matrixToHexStringBlockwise (state);
        std::string decoded;

        if (method == "AES")
                decoded = obj.decryptCipher (ciphertext, key, 0);
        else if (method == "MAES")
                decoded = obj.decryptCipher (ciphertext, key, 1);
        else
                decoded = obj.proposedDecryptCipher (ciphertext, key, imageHeight, imageWidth, 1);

        hexStringToMatrixBlockwise (decoded, state);

        buildTextFileFromMatrix (output, state);
}

int main()
{
        /// Driver function
        
        /// Supply a 128-bit key
        std::string key = "01020304010203040102030401020304";

        AES obj = AES (128);

        /*
        // Simple Text AES Encryption-Decryption
        //---------------------------------------

        std::string message = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

        std::string ciphertext = obj.encryptMessage (message, key, 0);
        std::string decoded = obj.decryptCipher (ciphertext, key, 0);

        std::cout<<"ORIGINAL MESSAGE: "<<message<<"\n";
        std::cout<<"ENCRYPTED: "<<ciphertext<<"\n";
        std::cout<<"DECRYPTED: "<<decoded<<"\n";
        */
        
        /// Edit filepaths, filenames and method as needed

        // Penguin
        saveEncryptedTextFile (obj, key, "Text_Files/Penguin/Original/penguin1.txt", "Text_Files/Penguin/AES/Encrypted/penguinAES1.txt", "AES", 512, 512);
        saveDecryptedTextFile (obj, key, "Text_Files/Penguin/AES/Encrypted/penguinAES1.txt", "Text_Files/Penguin/AES/Decrypted/penguinDec1.txt", "AES", 512, 512);

        /*
        // Lena
        saveEncryptedTextFile (obj, key, "Text_Files/Lena/Original/imagelena.txt", "Text_Files/Lena/AES/Encrypted/lenaAES1.txt", "AES", 128, 128);
        saveDecryptedTextFile (obj, key, "Text_Files/Lena/AES/Encrypted/lenaAES1.txt", "Text_Files/Lena/AES/Decrypted/lenaDec1.txt", "AES", 128, 128);

        // Mickey
        saveEncryptedTextFile (obj, key, "Text_Files/Mickey/Original/mickey1.txt", "Text_Files/Mickey/AES/Encrypted/mickeyAES1.txt", "AES", 128, 128);
        saveDecryptedTextFile (obj, key, "Text_Files/Mickey/AES/Encrypted/mickeyAES1.txt", "Text_Files/Mickey/AES/Decrypted/mickeyDec1.txt", "AES", 128, 128);
        saveEncryptedTextFile (obj, key, "Text_Files/Mickey/Original/mickey2.txt", "Text_Files/Mickey/AES/Encrypted/mickeyAES2.txt", "AES", 128, 128);
        saveDecryptedTextFile (obj, key, "Text_Files/Mickey/AES/Encrypted/mickeyAES2.txt", "Text_Files/Mickey/AES/Decrypted/mickeyDec2.txt", "AES", 128, 128);
        saveEncryptedTextFile (obj, key, "Text_Files/Mickey/Original/mickey3.txt", "Text_Files/Mickey/AES/Encrypted/mickeyAES3.txt", "AES", 128, 128);
        saveDecryptedTextFile (obj, key, "Text_Files/Mickey/AES/Encrypted/mickeyAES3.txt", "Text_Files/Mickey/AES/Decrypted/mickeyDec3.txt", "AES", 128, 128);
        */

        return 0;
}