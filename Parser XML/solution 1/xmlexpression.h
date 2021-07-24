#pragma once

#include "xmlparser.h"

#include <string>
#include <stack>
#include <memory>
#include <regex>

class XmlExpressionHandler {
private:
    const std::regex alpha_num_rex = std::regex("[a-zA-Z0-9_-]");
    const std::regex alpha_val_rex = std::regex("[a-zA-Z0-9_.:-]");
    const std::regex alpha_ext_rex = std::regex("[a-zA-Z0-9_.?!@#$%^&*()+;\"\\/,':-]");
    
    const int space_shift = 2;
    
    bool pending_obj_state;
    char pending_chr_to_read;
    std::string pending_str;
    std::shared_ptr<IObject> pending_obj;
    std::shared_ptr<MasterObject> m_xml_obj;
    std::stack<std::shared_ptr<IObject>> pending_obj_list;

    bool ParseSchemaObj(const std::string &str);
    bool ParseCommentObj(const std::string &str);
    bool ParseClosingObj(const std::string &str);
    bool ProcessObj(const std::string &str);
    bool ProcessAttribute(const std::string &str);
    bool ProcessObjValue(const std::string &str);
    void PrintRecursive(const std::shared_ptr<IObject> &obj, const int steps);
public:
    XmlExpressionHandler();
    bool ParseLine(const std::string &input);
    void Reset();
    void PrintXml();
};
