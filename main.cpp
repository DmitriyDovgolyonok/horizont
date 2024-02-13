#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(std::vector<std::string>& lines) = 0;
};

class RemoveWordCommand : public Command
{
public:
    RemoveWordCommand(const std::string& word) : word_to_remove_(word) {}

    void execute(std::vector<std::string>& lines) override
    {
        for (auto& line : lines)
        {
            size_t pos;
            while ((pos = line.find(word_to_remove_)) != std::string::npos)
                line.erase(pos, word_to_remove_.length());
        }
    }

private:
    std::string word_to_remove_;
};

class SortCommand : public Command
{
public:
    void execute(std::vector<std::string>& lines) override
    {
        for(std::string& line : lines)
        {
            std::stringstream ss(line);
            std::vector<std::string> words;
            std::string word;

            std::copy(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>(), std::back_inserter(words));
            std::sort(words.begin(), words.end(), [](const std::string& str1, const std::string& str2) {
                std::string lowerStr1;
                std::transform(str1.begin(), str1.end(), std::back_inserter(lowerStr1), [](u_char c) {
                    return std::tolower(c);
                });

                std::string lowerStr2;
                std::transform(str2.begin(), str2.end(), std::back_inserter(lowerStr2), [](u_char c) {
                    return std::tolower(c);
                });

                return lowerStr1 < lowerStr2;
            });
            std::stringstream sorted_ss;
            std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(sorted_ss, " "));
            line = sorted_ss.str();
        }
    }
};


bool processInput(int argc, char* argv[], std::string& input_file_name, std::string& output_file_name, std::string& word)
{
    const std::string help = "Usage: " + std::string(argv[0]) + " [options][paths...]\n"
                                                                "Options:\n"
                                                                "    -i <file>     Input file\n"
                                                                "    -o <file>     Output file\n"
                                                                "    -w <word>     Word to remove\n"
                                                                "    -h            Display help\n";

    if (argc != 7 || std::string(argv[1]) == "-h")
    {
        std::cerr << help;
        return false;
    }

    for(int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-i")
            input_file_name = argv[++i];
        else if (std::string(argv[i]) == "-o")
            output_file_name = argv[++i];
        else if (std::string(argv[i]) == "-w")
            word = argv[++i];
    }

    return true;
}


int main(int argc, char* argv[])
{
    std::string input_file_name;
    std::string output_file_name;
    std::string word;
    if (!processInput(argc, argv, input_file_name, output_file_name, word))
        return 1;

    std::ifstream inputFile(input_file_name);
    if(!inputFile)
    {
        std::cerr << "Error: Unable to open input file: " << input_file_name << std::endl;
        return 1;
    }

    std::ofstream outputFile(output_file_name);
    if (!outputFile)
    {
        std::cerr << "Error: Unable to create output file: " << output_file_name << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(inputFile, line))
        lines.push_back(line);

    RemoveWordCommand removeWordCommand(word);
    SortCommand sortCommand;

    removeWordCommand.execute(lines);

    sortCommand.execute(lines);

    for(const auto& sortedLine : lines)
        outputFile << sortedLine << std::endl;

    return 0;
}