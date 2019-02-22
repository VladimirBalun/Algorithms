#include <cctype>
#include <string>
#include <cstdint>
#include <iostream>

std::string encrypt(const std::string& text, std::uint8_t key)
{
    std::string encryptedText = text;
    for (auto& symbol : encryptedText)
    {
        if (std::isupper(symbol))
        {
            symbol = static_cast<char>((symbol + key) <= 'Z' ?
                (symbol + key) :
                (symbol + key) - ('Z' - 'A' + 1));
        }
        if (std::islower(symbol))
        {
            symbol = static_cast<char>((symbol + key) <= 'z' ?
                (symbol + key) :
                (symbol + key) - ('z' - 'a' + 1));
        }
    }
    return encryptedText;
}

std::string decrypt(const std::string& text, std::uint8_t key)
{
    std::string decryptedText = text;
    for (auto& symbol : decryptedText)
    {
        if (std::isupper(symbol))
        {
            symbol = static_cast<char>((symbol - key) >= 'A' ?
                (symbol - key) :
                (symbol - key) + ('Z' - 'A' + 1));
        }
        if (std::islower(symbol))
        {
            symbol = static_cast<char>((symbol - key) >= 'a' ?
                (symbol - key) :
                (symbol - key) + ('z' - 'a' + 1));
        }
    }
    return decryptedText;
}

int main()
{
    const std::uint8_t key = 2;
    const std::string text = "Test text...";
    const std::string encryptedText = encrypt(text, key);
    const std::string decryptedText = decrypt(encryptedText, key);

    std::cout << "Source text: " << text << std::endl;
    std::cout << "Encrypted text: " << encryptedText << std::endl;
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return EXIT_SUCCESS;
}
