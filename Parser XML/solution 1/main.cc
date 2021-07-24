#include "xmlexpression.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {

    // take input here
    if(argc <= 1) {
        // return file not mentioned
        std::cout << "Error: Wrong usage of command! \nCorrect usage: xmlparser file_name\n";
        return 0;
    }

    // check file is valid or not
    std::string file_path = std::string(argv[1]);

    // verify file is XML file
    auto str_path_len = file_path.size();
    if(str_path_len < 4 || file_path.substr(str_path_len - 4).compare(".xml") != 0) {
        std::cout << "Error: Entered file is not a XML file.\n";
    }

    std::ifstream xml_file_obj(file_path);

    // read file and get line by line data
    std::string per_line;
    XmlExpressionHandler xml_exp_obj;
    while(std::getline(xml_file_obj, per_line)) {
        // read file in the per_line
        // and also checks XML is a valid XML file
        if(xml_exp_obj.ParseLine(per_line))
            per_line.clear(); // clear buffer after reading
        else {
            xml_exp_obj.Reset();
            std::cout << "Error: XML file is not in correct format";
        }
    }
    xml_file_obj.close();

    xml_exp_obj.PrintXml();
    // get started with objectifying the XML tags

    return 0;
}
