#include "xmlexpression.h"
#include "xmlparser.h"

#include <iostream>
#include <regex>

XmlExpressionHandler::XmlExpressionHandler()
: pending_obj_state(false)
, pending_chr_to_read('\0')
, pending_str("")
, pending_obj(nullptr)
, m_xml_obj(std::make_shared<MasterObject>()) {
    pending_obj_list.push(m_xml_obj);
}

bool
XmlExpressionHandler::ParseLine(const std::string &input) {

    if(!input.size()) return false; // nothing to parse

    uint32_t read_next_chr_index = 0;

    // check for pennding character left for further processing
    if(pending_chr_to_read == '\0') {
        pending_chr_to_read = input[0];
        read_next_chr_index++;
    }
    
    while(read_next_chr_index < input.size() && pending_chr_to_read == ' ') {
        pending_chr_to_read = input[read_next_chr_index++];
    }

    // based on the current data or the pennding data process further
    switch (pending_chr_to_read) {
        case '<': {
            if(input.size() <= read_next_chr_index) { // not enough data to process futher
                return true;
            }
            else {
                pending_chr_to_read = '\0'; // have enough data to process
            }

            switch (input[read_next_chr_index]) {
                case '?': { // may be a schema obj
                    if(input.size() > read_next_chr_index)
                        return ParseSchemaObj(input.substr(read_next_chr_index+1));
                    break;
                }
                
                case '!':{ // may be a comment obj
                    if(input.size() > read_next_chr_index)
                        return ParseCommentObj(input.substr(read_next_chr_index+1));
                    break;
                }

                case '/':{ // may be a closing an obj
                    if(input.size() > read_next_chr_index)
                        return ParseClosingObj(input.substr(read_next_chr_index+1));
                    break;
                }

                default: { // could be an obj
                    if(input.size() >= read_next_chr_index)
                        return ProcessObj(input.substr(read_next_chr_index));
                    break;
                }
            }

            break;
        }
        default: { // could be anything
            if(input.size() <= read_next_chr_index) { // not enough data to process futher
                return true;
            }
            pending_chr_to_read = '\0';
            if(pending_obj_state) return ProcessAttribute(std::string(1, pending_chr_to_read) + input.substr(read_next_chr_index));
            return ProcessObjValue(std::string(1, pending_chr_to_read) + input.substr(read_next_chr_index));
            break;
        }
    }

    return false;
}

bool
XmlExpressionHandler::ParseSchemaObj(const std::string &str) {

    auto size_str = str.size();
    std::string arg = "";
    std::string value_arg = "";
    bool b_closing = false;
    bool b_value_reading = false;
    uint32_t index_str = 0;
    for (;index_str < size_str; index_str++) {
        auto chr = std::string(1, str[index_str]);
        if(std::regex_match(chr, alpha_num_rex)) {
            arg += str[index_str];
            continue;
        }
        break;
    }

    std::shared_ptr<XmlObjectSpl> obj = nullptr;
    if(arg.size())
    {
        obj = std::make_shared<XmlObjectSpl>(arg);
    }
    else
    {
        return false;
    }

    arg = "";
    Attribute attr;
    for (;index_str<size_str; index_str++) {
        if((!b_value_reading && std::regex_match(std::string(1, str[index_str]), alpha_num_rex))
         || (b_value_reading && std::regex_match(std::string(1, str[index_str]), alpha_val_rex))) {
            if (b_value_reading)
                value_arg += str[index_str];
            else
                arg += str[index_str];
        } else if (str[index_str] == '=') {
            if(!arg.size()) return false;
            attr.tag = arg;
            arg = "";
        } else if (str[index_str] == '"') {
            b_value_reading = !b_value_reading;
            if(!b_value_reading) {
                attr.value = value_arg;
                obj->SetAttribute(attr);
                attr.Reset();
            }
            value_arg = "";
        } else if (str[index_str] == ' ') {
            continue;
        } else if(str[index_str] == '?') {
            b_closing = true;
            continue;
        } else if (str[index_str] == '>' && b_closing == true) {
            break;
        }
        b_closing = false;
    }

    if(b_closing && obj && pending_obj_list.size()) {
        pending_obj_list.top()->SetSubObject(obj);
        return true;
    }

    return false;
}

bool
XmlExpressionHandler::ParseCommentObj(const std::string &str) {
    
    auto str_size = str.size();
    uint32_t index = 0;
    std::string arg = "";
    std::string closing_arg = "";
    const std::string closing_brace = "-->";

    if (index < str_size && str[index] == '-'
    && ++index < str_size && str[index] == '-') {
        for(++index;index<str_size; index++) {
            if (str[index] == '-' || str[index] == '>') {
                closing_arg += str[index];
                if (closing_brace.size() == closing_arg.size()) {
                    if (closing_brace == closing_arg) {
                        std::shared_ptr<XmlObjectSpl> obj = std::make_shared<XmlObjectSpl>();
                        Attribute attr;
                        attr.value = arg;
                        obj->SetAttribute(attr);
                        
                        pending_obj_list.top()->SetSubObject(obj);
                        
                        return true;
                    }
                    arg += closing_arg;
                    closing_arg = "";
                }
                continue;
            }
            arg+=str[index];
        }
    }

    return false;
}

bool
XmlExpressionHandler::ParseClosingObj(const std::string &str) {

    std::string closing_tag_name = "";
    if(str.size()) {
        for (auto &iter : str) {
            if(iter == '>') break;
            closing_tag_name+= iter;
        }
        if(!pending_obj) {
            pending_obj = pending_obj_list.top();
            pending_obj_list.pop();
        }
        if(pending_obj->GetTagName() == closing_tag_name) {
            pending_obj_list.top()->SetSubObject(pending_obj);
            pending_obj = nullptr;
        }
        return true;
    }
    return false;
}

bool
XmlExpressionHandler::ProcessObj(const std::string &str) {

    auto size_str = str.size();
    uint32_t index_str = 0;
    for (;index_str < size_str; index_str++) {
        if(std::regex_match(std::string(1, str[index_str]), alpha_num_rex)) {
            pending_str += str[index_str];
            continue;
        }
        break;
    }

    if(pending_str.size() && index_str < size_str)// && str[index_str] == '=')
    {
        auto obj = std::make_shared<XmlObject>(pending_str);
        if(pending_obj)
            pending_obj_list.push(pending_obj);
        pending_obj = obj;
        pending_str.clear();

        if(index_str < size_str && str[index_str] == '>') {
            if(index_str+1 < size_str)
                ProcessObjValue(str.substr(index_str+1));
            pending_obj_state = false;
        }
        else if(index_str < size_str && str[index_str] == ' ') {
            if (ProcessAttribute(str.substr(index_str+1)))
                pending_obj_state = false;
            else
                pending_obj_state = false;
        }
        else {
            pending_obj_state = true;
        }
        return true;
    }

    return false;
}

bool
XmlExpressionHandler::ProcessAttribute(const std::string &str) {
    
    bool b_value_reading = false;
    auto size_str = str.size();
    std::string value_arg = "", arg = "";
    
    Attribute attr;
    for (uint32_t index_str=0; index_str<size_str; index_str++) {
        if((!b_value_reading && std::regex_match(std::string(1, str[index_str]), alpha_num_rex))
         || (b_value_reading && std::regex_match(std::string(1, str[index_str]), alpha_val_rex))) {
            if (b_value_reading)
                value_arg += str[index_str];
            else
                arg += str[index_str];
        } else if (str[index_str] == '=') {
            if(!arg.size()) return false;
            attr.tag = arg;
            arg = "";
        } else if (str[index_str] == '"') {
            b_value_reading = !b_value_reading;
            if(!b_value_reading) {
                attr.value = value_arg;
                pending_obj->SetAttribute(attr);
                attr.Reset();
            }
            value_arg = "";
        } else if (str[index_str] == ' ') {
            continue;
        } else if (str[index_str] == '>') {
            if(!attr.tag.size() && !attr.value.size()) return true;
        }
    }
    return false;
}

bool
XmlExpressionHandler::ProcessObjValue(const std::string &str) {

    uint32_t str_size = str.size();
    if (str.size()) {
        for (uint32_t index = 0; index < str_size; index++ )
        {
            if (str[index] == '<') {
                if(++index < str_size && str[index] == '/') {
                    if (pending_obj) pending_obj->SetXmlValue(pending_str);
                    pending_str.clear();
                    return ParseClosingObj(str.substr(index+1));
                }
                return false;
            }
            pending_str += str[index];
        }
        return true;
    }
    return false;
}

void
XmlExpressionHandler::Reset() {
    pending_obj_state = false;
    pending_chr_to_read = '\0';
    pending_str = "";
    pending_obj = m_xml_obj = nullptr;
    pending_obj_list = std::stack<std::shared_ptr<IObject>>();
}

void
XmlExpressionHandler::PrintXml() {
    if(!m_xml_obj) {
        std::cout << "Check Xml file again. Cannot print.\n";
    }
    
    PrintRecursive(m_xml_obj, 0);
}

void
XmlExpressionHandler::PrintRecursive(const std::shared_ptr<IObject> &obj, const int steps) {
    if(!obj) return;
    
    std::cout << "\n";
    
    for (auto i=0; i<steps*space_shift; i++) {
        std::cout << " ";
    }
    
    if(obj->GetTagName().size())
        std::cout << obj->GetTagName() << " ";
    else if(steps) {
        std::cout << "#comment ";
        auto v = obj->GetAttributes();
        for (auto &i : v) {
            std::cout << i.value;
        }
        return;
    }
    
    auto v = obj->GetAttributes();
    if(v.size()) {
        std::cout << "[ ";
        for (auto &i : v) {
            std::cout << i.tag << ": "<< i.value << " ";
        }
        std::cout << "] ";
    }
    
    if(obj->GetTagValue().size())
    {
        std::cout<<": "<<obj->GetTagValue();
    }
    
    auto sobj = obj->GetSubObjects();
    for (auto &i : sobj) {
        PrintRecursive(i, steps+1);
    }
}
