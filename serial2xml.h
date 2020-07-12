/*
 * tinyxml2 usage:
 * -- CREATE -- 
 * tinyxml2::XMLDocument: xml file object,
 * tinyxml2::XMLError: xml error object,
 * tinyxml2::XMLComment* comment = doc.NewComment(string); 
 * tinyxml2::XMLElement* elem = doc.NewElement(string);
 * tinyxml2::XMLText* text = doc.NewText(string);
 * elem->SetAttribute(string1, string2), elem->SetText(string);
 * elem->InsertFirstChild(elem)
 * elem->InsertEndChild(elem), elem->InsertEndChild(text), doc.InsertEndChild(elem), 
 * doc.SaveFile(file_name): save a xml file, using XMLError object to judge the mistake.
 * 
 * -- PARSE --
 * tinyxml2::XMLError ret = doc.LoadFile(file_name);
 * tinyxml2::XMLElement* root = doc.RootElement();
 * tinyxml2::XMLElement* elem = elem->FirstChildElement(string); # Must have attribute
 * elem->Name(), elem->Attribute(string), elem->GetText()
 * 
 * -- VISIT --
 * elem->FirstChild()
 * elem->FirstChildElement(char*)
 * elem->Last**  
 * elem->NextSibling()
 * elem->NextSiblingElement(char*)
 * elem->Previous**
 * elem->Parent()
 * elem->FirstChild()->ToElement()
**/

#ifndef _SERIALIZE_XML_H_
#define _SERIALIZE_XML_H_
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

namespace serial2xml {
    template <typename T>
    class XMLSerializerBase {
    private:
        std::vector<T> regMembers;
        std::vector<T> loadMembers;
        std::string file_name = "test.xml"; 
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* root;

        inline void reset() {
            doc.Clear();
            tinyxml2::XMLDeclaration* dec = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
            doc.InsertFirstChild(dec);
            root = doc.NewElement("Serialization");
            doc.InsertEndChild(root);
        }

        inline void xml_save(string name) {
            doc.SaveFile(name.c_str());
            xml2Base64(name);
        }

        inline void xml_save() {
            doc.SaveFile(file_name.c_str());
        }

        void xml2Base64(string name);

        template <class H, class ...Args>
        void userDefinedType2XML (string file, H head, Args... rest) {
            serialize(head, root);
            userDefinedType2XML(file, rest...);
        }

        void userDefinedType2XML (string file)
        {
            xml_save(file);
        }

    public:
        /*
            serialize_xml(pair0, "std_pair", "pair.xml");
            deserialize_xml(pair1, "std_pair", "pair.xml");
        */
        XMLSerializerBase(void) {
            regMembers.clear();
            loadMembers.clear();
            reset();
            /*
                <?xml version="1.0" encoding="UTF-8"?>
                <Serialization>
                    ......
                </Serialization>
            */
        };

        // public API for serialization.
        // one way: push element 1 by 1 into the container, and save at once.
        inline void push_back (T const& elem) {
            regMembers.push_back(elem);
        }
        inline void save () {
            file_name = "test.xml";
            for( auto item : regMembers ) {
                serialize(item, root);
            }
            xml_save();
        }
        inline void save (string file) {
            reset();
            for( auto item : regMembers ) {
                serialize(item, root);
            }
            xml_save(file);
        }
        // the other: use the API to serialize one by one.
        inline void serialize_xml(int& obj, string type, string file_name) {
            reset();
            if(type != "std_int") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(short& obj, string type, string file_name) {
            reset();
            if(type != "std_short") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(double& obj, string type, string file_name) {
            reset();
            if(type != "std_double") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(float& obj, string type, string file_name) {
            reset();
            if(type != "std_float") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(long& obj, string type, string file_name) {
            reset();
            if(type != "std_long") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(bool& obj, string type, string file_name) {
            reset();
            if(type != "std_bool") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(long long& obj, string type, string file_name) {
            reset();
            if(type != "std_long_long") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(long double& obj, string type, string file_name) {
            reset();
            if(type != "std_long_double") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }           
        inline void serialize_xml(char& obj, string type, string file_name) {
            reset();
            if(type != "std_char") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }
        inline void serialize_xml(string& obj, string type, string file_name) {
            reset();
            if(type != "std_string") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        } 
        inline void serialize_xml(wchar_t& obj, string type, string file_name) {
            reset();
            if(type != "std_wchar_t") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);
        }               
        template <class Vec> inline void serialize_xml(const std::vector<Vec>& obj, string type, string file_name) {
            reset();
            if(type != "std_vector") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);        
        }
        template <class First, class Second> inline void serialize_xml(const std::pair<First, Second>& obj, string type, string file_name) {
            reset();
            if(type != "std_pair") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);        
        }
        template <class List> inline void serialize_xml(const std::list<List>& obj, string type, string file_name) {
            reset();
            if(type != "std_list") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);        
        }    
        template <class Set> inline void serialize_xml(const std::set<Set>& obj, string type, string file_name) {
            reset();
            if(type != "std_set") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);        
        }
        template <class First, class Second> inline void serialize_xml(const std::map<First, Second>& obj, string type, string file_name) {
            reset();
            if(type != "std_map") 
                cout << "Warning: requested type is not matched with object type!" << endl;
            serialize(obj, root);
            xml_save(file_name);        
        }        

        // public API for deserialization.
        inline void deserialize_xml(int& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_int"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_int"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(short& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_short"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_short"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(float& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_float"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_float"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }        
        inline void deserialize_xml(double& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_double"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_double"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(bool& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_bool"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_bool"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(long double& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_long_double"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_long_double"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(long long& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_long_long"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_long_long"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(long& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_long"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_long"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(char& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_char"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_char"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(wchar_t& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_wchar_t"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_wchar_t"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }
        inline void deserialize_xml(string& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_string"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_string"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }
        }

        template <class Vec> inline void deserialize_xml(std::vector<Vec>& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_vector"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_vector"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }        
        }
        template <class First, class Second> inline void deserialize_xml(std::pair<First, Second>& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_pair"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_pair"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }        
        }
        template <class List> inline void deserialize_xml(std::list<List>& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_list"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_list"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }        
        }
        template <class Set> inline void deserialize_xml(std::set<Set>& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_set"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_set"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }        
        }    
        template <class First, class Second> inline void deserialize_xml(std::map<First, Second>& obj, string type, string file_name) {
            reset();
            tinyxml2::XMLError ret = doc.LoadFile(file_name.c_str());        
            if(ret != 0) { cout << "Fail to open the xml file" << endl; return; }
            root = doc.FirstChildElement("Serialization");
            if(type != ("std_map"))
                cout << "Warning: requested type is not totally matched with object type!" << endl;
            bool _ret = deserialize(obj, type, root->FirstChildElement("std_map"));
            if(!_ret) { cout << "Cannot find data with requested type in the xml file!" << endl; return; }        
        }    
        
        // other operations.
        inline int size () {
            return regMembers.size();
        }
        inline void printAll () {
            for ( auto elem : regMembers ) cout << elem;
            cout << endl;
        }

        // user-defined type
        template <class ...Args>
        void userDefinedTypeToXML (string file, Args... args) {
            reset();
            userDefinedType2XML(file, args...);
        }

    private:
        // inline serialize for arithmetic object.
        // In C++98:
        inline void serialize(const bool& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_bool");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        };
        inline void serialize(const char& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_char");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        };
        inline void serialize(const wchar_t& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_wchar_t");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        // inline void serialize(char16_t object, std::string file_name);
        // inline void serialize(char32_t object, std::string file_name);
        inline void serialize(const short& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_short");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const int& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_int");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const long& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_long");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const long long& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_long_long");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const float& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_float");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const double& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_double");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }
        inline void serialize(const long double& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_long_double");
            elem->SetAttribute("val", std::to_string(object).c_str());
            node->InsertEndChild(elem);
        }    
        inline void serialize(const string& object, tinyxml2::XMLElement* node) {
            tinyxml2::XMLElement* elem = doc.NewElement("std_string");
            elem->SetAttribute("val", object.c_str());
            node->InsertEndChild(elem);
        }    
        // serialize for stl.
        template <class Vec>
        void serialize(const std::vector<Vec>& object, tinyxml2::XMLElement* node);
        template <class First, class Second>
        void serialize(const std::pair<First, Second>& object, tinyxml2::XMLElement* node);
        template <class List>
        void serialize(const std::list<List>& object, tinyxml2::XMLElement* node);
        template <class Set>
        void serialize(const std::set<Set>& object, tinyxml2::XMLElement* node);
        template <class First, class Second>
        void serialize(const std::map<First, Second>& object, tinyxml2::XMLElement* node);    

        // inline deserialize for arithmetic object.
        // In C++98:
        // find value in current node.
        inline bool deserialize(bool& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoi(value_str, 0, 10);
            return true;
        };
        inline bool deserialize(char& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoi(value_str, 0, 10);
            return true;
        };
        inline bool deserialize(wchar_t& object, string type, tinyxml2::XMLElement* node) {   
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoi(value_str, 0, 10);
            return true;
        }
        // inline void deserialize(char16_t object);
        // inline void deserialize(char32_t object);
        inline bool deserialize(short& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoi(value_str, 0, 10);
            return true;
        }
        inline bool deserialize(int& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoi(value_str, 0, 10);
            return true;
        }
        inline bool deserialize(long& object, string type, tinyxml2::XMLElement* node) {       
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stol(value_str, 0, 10);
            return true;
        }
        inline bool deserialize(long long& object, string type, tinyxml2::XMLElement* node) {     
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stoll(value_str, 0, 10);
            return true;
        }
        inline bool deserialize(float& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stof(value_str, 0);
            return true;
        }
        inline bool deserialize(double& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stod(value_str, 0);
            return true;
        }
        inline bool deserialize(long double& object, string type, tinyxml2::XMLElement* node) {
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = stold(value_str, 0);
            return true;
        }
        inline bool deserialize(string& object, string type, tinyxml2::XMLElement* node) {      
            if(!node) return false;
            string value_str = node->Attribute("val");
            object = value_str;
            return true;
        }

        // deserialize for stl.
        template <class Vec>
        bool deserialize(std::vector<Vec>& object, string type, tinyxml2::XMLElement* node);
        template <class First, class Second>
        bool deserialize(std::pair<First, Second>& object, string type, tinyxml2::XMLElement* node);
        template <class List>
        bool deserialize(std::list<List>& object, string type, tinyxml2::XMLElement* node);
        template <class Set>
        bool deserialize(std::set<Set>& object, string type, tinyxml2::XMLElement* node);
        template <class First, class Second>
        bool deserialize(std::map<First, Second>& object, string type, tinyxml2::XMLElement* node);  
   
    };

    // s
    template<typename T> template<class Vec>
    void XMLSerializerBase<T>::serialize(const std::vector<Vec>& object, tinyxml2::XMLElement* node)
    {
        tinyxml2::XMLElement* elem = doc.NewElement("std_vector");
        elem->SetAttribute("size", object.size());
        node->InsertEndChild(elem);
        for( auto item : object)
            serialize(item, elem);
    }

    template<typename T> template<class First, class Second>
    void XMLSerializerBase<T>::serialize(const std::pair<First, Second>& object, tinyxml2::XMLElement* node)
    {
        tinyxml2::XMLElement* elem = doc.NewElement("std_pair");
        node->InsertEndChild(elem);
        tinyxml2::XMLElement* first = doc.NewElement("first");
        elem->InsertEndChild(first);
        serialize(object.first, first);
        tinyxml2::XMLElement* second = doc.NewElement("second");
        elem->InsertEndChild(second);
        serialize(object.second, second);    
    }

    template<typename T> template<class List>
    void XMLSerializerBase<T>::serialize(const std::list<List>& object, tinyxml2::XMLElement* node)
    {
        tinyxml2::XMLElement* elem = doc.NewElement("std_list");
        elem->SetAttribute("size", object.size());
        node->InsertEndChild(elem);
        for( auto item : object )
            serialize(item, elem);
    }

    template<typename T> template<class Set>
    void XMLSerializerBase<T>::serialize(const std::set<Set>& object, tinyxml2::XMLElement* node)
    {
        tinyxml2::XMLElement* elem = doc.NewElement("std_set");
        elem->SetAttribute("size", object.size());
        node->InsertEndChild(elem);
        for( auto item : object )
            serialize(item, elem);
    }

    template<typename T> template<class First, class Second>
    void XMLSerializerBase<T>::serialize(const std::map<First, Second>& object, tinyxml2::XMLElement* node)
    {
        tinyxml2::XMLElement* elem = doc.NewElement("std_map");
        elem->SetAttribute("size", object.size());
        node->InsertEndChild(elem);
        for( auto item : object ) {
            First f = item.first;
            Second s = item.second;
            tinyxml2::XMLElement* child = doc.NewElement("std_pair");
            elem->InsertEndChild(child);
            tinyxml2::XMLElement* first = doc.NewElement("first");
            child->InsertEndChild(first);
            serialize(f, first);
            tinyxml2::XMLElement* second = doc.NewElement("second");
            child->InsertEndChild(second);
            serialize(s, second);
        }
    }   

    // de
    template<typename T> template<class Vec>
    bool XMLSerializerBase<T>::deserialize(std::vector<Vec>& object, string type, tinyxml2::XMLElement* node)
    {
        if(!node) return false;
        tinyxml2::XMLElement* child = node->FirstChild()->ToElement();
        for(size_t i = 0; i < atoi(node->Attribute("size")); i++) {
            Vec new_element;
            deserialize(new_element, string(child->Name()), child);
            object.push_back(new_element);
            if(child->NextSibling())
                child = child->NextSibling()->ToElement();
        }
        return true;    
    }

    template<typename T> template<class First, class Second>
    bool XMLSerializerBase<T>::deserialize(std::pair<First, Second>& object, string type, tinyxml2::XMLElement* node)
    {
        if(!node) return false;
        tinyxml2::XMLElement* first = node->FirstChildElement("first");
        tinyxml2::XMLElement* second = node->FirstChildElement("second");
        First f;
        Second s;
        deserialize(f, string(first->FirstChild()->ToElement()->Name()), first->FirstChild()->ToElement());
        deserialize(s, string(second->FirstChild()->ToElement()->Name()), second->FirstChild()->ToElement());
        object.first = f;
        object.second = s;
        return true;       
    }

    template<typename T> template<class List>
    bool XMLSerializerBase<T>::deserialize(std::list<List>& object, string type, tinyxml2::XMLElement* node)
    {
        if(!node) return false;
        tinyxml2::XMLElement* child = node->FirstChild()->ToElement();
        for(size_t i = 0; i < atoi(node->Attribute("size")); i++) {
            List new_element;
            deserialize(new_element, string(child->Name()), child);
            object.push_back(new_element);
            if(child->NextSibling())
                child = child->NextSibling()->ToElement();
        }
        return true;    
    }

    template<typename T> template<class Set>
    bool XMLSerializerBase<T>::deserialize(std::set<Set>& object, string type, tinyxml2::XMLElement* node)
    {
        if(!node) return false;
        tinyxml2::XMLElement* child = node->FirstChild()->ToElement();
        for(size_t i = 0; i < atoi(node->Attribute("size")); i++) {
            Set new_element;
            deserialize(new_element, string(child->Name()), child);
            object.insert(new_element);
            if(child->NextSibling())
                child = child->NextSibling()->ToElement();
        }
        return true;
    }

    template<typename T> template<class First, class Second>
    bool XMLSerializerBase<T>::deserialize(std::map<First, Second>& object, string type, tinyxml2::XMLElement* node)
    {
        if(!node) return false;
        tinyxml2::XMLElement* child = node->FirstChild()->ToElement();
        for(size_t i = 0; i < atoi(node->Attribute("size")); i++) {
            std::pair<First, Second> new_element;
            tinyxml2::XMLElement* first = child->FirstChildElement("first");
            tinyxml2::XMLElement* second = child->FirstChildElement("second");
            First f;
            Second s;
            deserialize(f, string(first->FirstChild()->ToElement()->Name()), first->FirstChild()->ToElement());
            deserialize(s, string(second->FirstChild()->ToElement()->Name()), second->FirstChild()->ToElement());
            new_element.first = f;
            new_element.second = s;        
            object.insert(new_element);
            if(child->NextSibling())
                child = child->NextSibling()->ToElement();
        }
        return true;    
    }                                                                                                                                                                                                                           

    template<typename T>
    void XMLSerializerBase<T>::xml2Base64(string name)
    {
        FILE* fp_xml = fopen(name.c_str(), "r");
        FILE* fp_base64 = fopen((name.substr(0, name.find('.')) + "_base64.bin").c_str(), "w+");
        if((!fp_xml) || (!fp_base64)) return;
        char tmp[3], base64tmp[4], base64[4];
        int cnt = 0, numRead;
        for( numRead = fread(tmp, 1, 3, fp_xml); numRead != 0 && (!feof(fp_xml)) ; fread(tmp, 1, 3, fp_xml)) {
            if(numRead == 2)
                tmp[2] = 0;
            else if(numRead == 1)
                tmp[2] = tmp[1] = 0;
            base64tmp[0] = (tmp[0] >> 2) & 0x3f;
            base64tmp[1] = (((tmp[0] & 0x03) << 4) | (tmp[1] >> 4)) & 0x3f;
            base64tmp[2] = (((tmp[1] & 0x0f) << 2) | (tmp[2] >> 6)) & 0x3f;
			base64tmp[3] = (tmp[2] & 0x3f) & 0x3f;
			for (int i = 0; i < 4; i++) {
				if (base64tmp[i] >= 0 && base64tmp[i] < 26)
					base64[i] = base64tmp[i] + 65;
				else if (26 <= base64tmp[i] && base64tmp[i] < 52)
					base64[i] = base64tmp[i] + 71;
				else if (52 <= base64tmp[i] && base64tmp[i] < 62)
					base64[i] = base64tmp[i] - 4;
				else if (base64tmp[i] == 62)
					base64[i] = 43;
				else base64[i] = 47;
			}
            fwrite(base64, 1, 4, fp_base64);
        }
        fclose(fp_base64);
        fclose(fp_xml);
    }
}
#endif