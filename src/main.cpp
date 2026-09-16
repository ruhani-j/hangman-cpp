#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace
{

    const std::vector<std::string> WORDS = {
        "compiler", "keyboard", "mountain", "database", "network",
        "terminal", "function", "variable", "pointer", "algorithm"};

    const std::vector<std::string> STAGES = {
        "  +---+\n  |   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n========="};

    std::string display_word(const std::string &word, const std::unordered_set<char> &guessed)
    {
        std::string display;
        for (const char letter : word)
        {
            display += guessed.find(letter) != guessed.end() ? letter : '_';
            display += ' ';
        }
        return display;
    }

    std::string display_guessed(const std::unordered_set<char> &guessed)
    {
        std::vector<char> letters(guessed.begin(), guessed.end());
        std::sort(letters.begin(), letters.end());
        std::ostringstream display;
        for (std::size_t index = 0; index < letters.size(); ++index)
        {
            if (index > 0)
            {
                display << ' ';
            }
            display << letters[index];
        }
        return display.str();
    }

    void render_game(const std::string &word, const std::unordered_set<char> &guessed, int misses)
    {
        const int misses_remaining = static_cast<int>(STAGES.size()) - 1 - misses;
        std::cout << "\n+===============================================+\n"
                  << "|                  H A N G M A N              |\n"
                  << "+===============================================+\n"
                  << STAGES[misses] << "\n\n"
                  << "+-----------------------------------------------+\n"
                  << "| Word:           " << display_word(word, guessed) << "\n"
                  << "| Misses remaining: " << misses_remaining << "\n"
                  << "| Guessed letters: " << (guessed.empty() ? "none" : display_guessed(guessed)) << "\n"
                  << "+-----------------------------------------------+\n";
    }

    bool solved(const std::string &word, const std::unordered_set<char> &guessed)
    {
        return std::all_of(word.begin(), word.end(), [&guessed](char letter)
                           { return guessed.find(letter) != guessed.end(); });
    }

    char read_guess()
    {
        std::string input;
        while (true)
        {
            std::cout << "\nEnter a letter [a-z] > ";
            if (!std::getline(std::cin, input))
            {
                return '\0';
            }
            if (input.size() == 1 && std::isalpha(static_cast<unsigned char>(input[0])))
            {
                return static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));
            }
            std::cout << "Enter one letter.\n";
        }
    }

}

int main()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<std::size_t> distribution(0, WORDS.size() - 1);
    const std::string word = WORDS[distribution(generator)];
    std::unordered_set<char> guessed;
    int misses = 0;

    std::cout << "\nWelcome to Hangman! Guess the word before the drawing is complete.\n";
    while (misses < static_cast<int>(STAGES.size()) - 1 && !solved(word, guessed))
    {
        render_game(word, guessed, misses);
        const char guess = read_guess();
        if (guess == '\0')
        {
            return EXIT_FAILURE;
        }
        if (!guessed.insert(guess).second)
        {
            std::cout << "You already guessed that letter.\n";
        }
        else if (word.find(guess) == std::string::npos)
        {
            ++misses;
            std::cout << "No match.\n";
        }
        else
        {
            std::cout << "Good guess.\n";
        }
    }

    if (solved(word, guessed))
    {
        std::cout << "\nYou won! The word was " << word << ".\n";
        return EXIT_SUCCESS;
    }
    std::cout << '\n'
              << STAGES.back() << "\nYou lost. The word was " << word << ".\n";
    return EXIT_SUCCESS;
}
