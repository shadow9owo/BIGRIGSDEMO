#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <climits>

namespace SmartTDB
{
    extern std::vector<unsigned char> GetRawBytes();
    extern bool SetRawBytes(std::vector<unsigned char>);

    extern int GetIntValue(std::string Name);
    extern unsigned char GetByteValue(std::string Name);
    extern short GetShortValue(std::string Name);
    
    extern void SetIntValue(std::string Name,int value);
    extern void SetByteValue(std::string Name,unsigned char value);
    extern void SetShortValue(std::string Name,short value);

    extern bool Declared;
    extern std::string FILENAME;
    std::string FILENAME = "";
    extern bool DeclareDBname(std::string filename);

    namespace UTILS
    {
        namespace Bytes
        {
            extern std::vector<uint8_t> IntToBytes(uint32_t value);
            extern uint32_t BytesToInt(const std::vector<uint8_t>& bytes);
            std::vector<uint8_t> IntToBytes(uint32_t value)
            {
                std::vector<uint8_t> bytes(4);
                bytes[0] = static_cast<uint8_t>(value & 0xFF);
                bytes[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
                bytes[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
                bytes[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
                return bytes;
            }
            uint32_t BytesToInt(const std::vector<uint8_t>& bytes)
            {
                uint32_t value = 0;
                for (size_t i = 0; i < bytes.size(); ++i) {
                    value |= static_cast<uint32_t>(bytes[i]) << (8 * i);
                }
                return value;
            }
        }
        extern bool DoesNameExist(std::string Name);
        extern void ReplaceValue(std::string Name, int value);
        extern int LoadValue(std::string Name);

        int LoadValue(std::string Name)
        {
            std::ifstream fi(SmartTDB::FILENAME);
            std::string line;
        
            while (std::getline(fi, line))
            {
                if (line.rfind(Name + "||", 0) == 0)
                {
                    std::string byteString = line.substr(Name.length() + 2);
                
                    std::vector<uint8_t> bytes;
                    size_t start = 0;
                    size_t end;
                
                    while ((end = byteString.find(',', start)) != std::string::npos)
                    {
                        bytes.push_back(static_cast<uint8_t>(std::stoi(byteString.substr(start, end - start))));
                        start = end + 1;
                    }

                    if (start < byteString.size())
                        bytes.push_back(static_cast<uint8_t>(std::stoi(byteString.substr(start))));
                
                    return SmartTDB::UTILS::Bytes::BytesToInt(bytes);
                }
            }
        
            return -1;
        }

        void ReplaceValue(std::string Name, int value)
        {
            std::ifstream ifs(FILENAME);
            std::vector<std::string> lines;
            std::string line;

            if (ifs)
            {
                while (std::getline(ifs, line))
                {
                    lines.push_back(line);
                }
                ifs.close();
            }

            std::vector<uint8_t> bytes = Bytes::IntToBytes(value);

            bool replaced = false;
            for (size_t i = 0; i < lines.size(); ++i)
            {
                if (lines[i].rfind(Name + "||", 0) == 0)
                {
                    std::ostringstream oss;
                    oss << Name << "||";
                    for (size_t j = 0; j < bytes.size(); ++j)
                    {
                        oss << static_cast<int>(bytes[j]);
                        if (j < bytes.size() - 1)
                            oss << ",";
                    }
                    lines[i] = oss.str();
                    replaced = true;
                    break;
                }
            }

            if (!replaced)
            {
                std::ostringstream oss;
                oss << Name << "||";
                for (size_t j = 0; j < bytes.size(); ++j)
                {
                    oss << static_cast<int>(bytes[j]);
                    if (j < bytes.size() - 1)
                        oss << ",";
                }
                lines.push_back(oss.str());
            }

            std::ofstream ofs(FILENAME, std::ios::trunc);
            if (!ofs) return;

            for (size_t i = 0; i < lines.size(); ++i)
            {
                ofs << lines[i] << "\n";
            }

            ofs.close();
        }

        bool DoesNameExist(std::string Name)
        {
            std::ifstream ifs(SmartTDB::FILENAME);
            for (std::string line; std::getline(ifs ,line); ) {
                if (line.rfind(Name + "||", 0) == 0)
                {
                    return true;
                }
            }
            return false;
        }
    }

    bool Declared = false;
    
    bool DeclareDBname(std::string filename)
    {
        if (filename.rfind("|", 0) == 0) { return false; }
        if (filename.empty() == true) {return false;}
        FILENAME = filename;
        Declared = true;
        return true;
    }

    int GetIntValue(std::string Name)
    {
        if (!Declared) {return 0;}
        if (!UTILS::DoesNameExist(Name)) return 0;
        try
        {
            int a = UTILS::LoadValue(Name);
            return a;
        }
        catch(const std::exception& e)
        {
            return INT32_MAX;
        }
    }

    unsigned char GetByteValue(std::string Name)
    {
        if (!Declared) {return 0;}
        if (!UTILS::DoesNameExist(Name)) return 0;
        try
        {
            unsigned char a = UTILS::LoadValue(Name);
            return a;
        }
        catch(const std::exception& e)
        {
            return UINT8_MAX;
        }
    }

    short GetShortValue(std::string Name)
    {
        if (!Declared) {return 0;}
        if (!UTILS::DoesNameExist(Name)) return 0;
        try
        {
            short a = UTILS::LoadValue(Name);
            return a;
        }
        catch(const std::exception& e)
        {
            return SHRT_MAX;
        }
    }

    void SetIntValue(std::string Name,int value)
    {
        if (!Declared) {return;}
        UTILS::ReplaceValue(Name,value);
        return;
    }

    void SetByteValue(std::string Name,unsigned char value)
    {
        if (!Declared) {return;}
        UTILS::ReplaceValue(Name,value);
        return;
    }

    void SetShortValue(std::string Name,short value)
    {
        if (!Declared) {return;}
        UTILS::ReplaceValue(Name,value);
        return;
    }

    std::vector<unsigned char> GetRawBytes()
    {
        if (!Declared) {return {};}
        std::ifstream ifs(FILENAME, std::ios::binary | std::ios::ate);
        if (!ifs) {
            return {};
        }

        std::ifstream::pos_type pos = ifs.tellg();
        if (pos <= 0) {
            return {};
        }

        std::vector<unsigned char> result(static_cast<size_t>(pos));

        ifs.seekg(0, std::ios::beg);
        ifs.read(reinterpret_cast<char*>(result.data()), result.size());

        return result;
    }

    bool SetRawBytes(std::vector<unsigned char> input)
    {
        if (!Declared) return false;
        std::vector<unsigned char> a;
        a = GetRawBytes();
        try
        {
            std::remove(FILENAME.c_str());
            std::ofstream db(FILENAME, std::ios::binary);

            db.write(reinterpret_cast<const char*>(input.data()), input.size());

            db.close();
            return true;
        }
        catch(const std::exception& e)
        {
            try
            {
                std::remove(FILENAME.c_str());
                std::ofstream db(FILENAME, std::ios::binary);

                db.write(reinterpret_cast<const char*>(a.data()), a.size());
                db.close();
            }
            catch(const std::exception& e)
            {
                std::cout << "db recovery failed" << std::endl;
                return false;
            }
            
            return false;
        }
    }
}
