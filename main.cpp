#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <unordered_map>
#include <memory>

enum Color {
    ROUGE = 0,
    JAUNE,
    BLEU,
    ORANGE,
    VERT,
    NOIR,
    UNDIFINED = -1
};

const static std::unordered_map<char, Color> vec = {{'R', Color::ROUGE}, {'J', Color::JAUNE}, {'B', Color::BLEU}, {'O', Color::ORANGE}, {'V', Color::VERT}, {'N', Color::NOIR}};
const static short NB_COLOR = 6;
const static short NB_PIONS = 4;
const static short NB_TURNS = 10;

const Color           findColor(const char c) {
    for (auto &i : vec) {
        if (i.first == c)
            return i.second;
    }
    std::cerr << "Color " << c << " Unknown" << std::endl;
    return Color::UNDIFINED;
}

std::shared_ptr<std::vector<Color>> checkCmd(std::string const &str) {

    std::shared_ptr<std::vector<Color>> pions = std::make_shared<std::vector<Color>>();
    short j = 0;
    Color c;

    pions->resize(NB_PIONS);
    for (auto i : str) {
        c = findColor(toupper(i));
        for (short k = 0; k < j; k++) {
            {
                if (c == Color::UNDIFINED || c == (*pions)[k]) {
                    std::cerr << "Undeffined color or more than one equals color" << std::endl;
                    return nullptr;
                }
            }
        }
        (*pions)[j++] = c;
    }
    return pions;
}

bool        containsColor(std::vector<Color> const &tab, const Color &c) {
    for (auto &i : tab) {
        if (i == c)
            return true;
    }
    return false;
}

bool        findCorrect(std::shared_ptr<std::vector<Color>> const &input, std::vector<Color> const &to_find, std::string const &buff) {
    short   correct = 0;
    short   wrongPlace = 0;

    for (short i = 0; i < input->size(); i++) {
        if ((*input)[i] == to_find[i])
            correct++;
        else if (containsColor(to_find, (*input)[i]))
            wrongPlace++;
    }
    std::cout << buff << " | " << correct << " | " << wrongPlace << " | ";
    if (correct == NB_PIONS)
        return true;
    return false;
}

int main() {
    std::vector<Color> pions;
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<Color> to_find;
    std::string buff;
    std::shared_ptr<std::vector<Color>> input;
    bool        win = false;

    for (int i = 0; i < NB_COLOR; i++)
        pions.push_back((Color)i);
    std::shuffle(pions.begin(), pions.end(), g);
    for (int i = 0; i < NB_PIONS; i++)
        to_find.push_back(pions[i]);
    for (int i = 0; i < NB_TURNS; i++) {
        std::cout << "Your Turn to play choose 4 Colors like NBJV" << std::endl;
        std::getline(std::cin, buff);
        while (buff.size() != NB_PIONS || (input = checkCmd(buff)) == nullptr) {
            if (std::cin.eof())
                exit(-1);
            std::cerr << "Wrong Command please try again buff size " << buff.size() << std::endl;
            std::getline(std::cin, buff);
        }
        if ((win = findCorrect(input, to_find, buff))) {
            std::cout << i << "/" << NB_TURNS << std::endl;
            std::cout << "Bravo vous avez gagné en " << i + 1 << std::endl;
            break;
        } else
            std::cout << i + 1<< "/" << NB_TURNS << std::endl;
    }
    if (!win)
        std::cout << "Try again :)" << std::endl;
    return 0;
}