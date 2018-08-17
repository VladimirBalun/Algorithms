#include <iostream>

std::string encrypt(const std::string& text, size_t key)
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

std::string dencrypt(const std::string& text, size_t key)
{
    std::string dencryptedText = text;
    for (auto& symbol : dencryptedText)
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
    return dencryptedText;
}

int main()
{
    size_t key = 2;
    std::string text = "Test text...";

    std::string encryptedText = encrypt(text, key);
    std::string dencryptedText = dencrypt(text, key);

    std::cout << encryptedText << std::endl;
    std::cout << encryptedText << std::endl;

    return EXIT_SUCCESS;
}
