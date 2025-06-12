#include "STD.hpp"
#include "Save.hpp"
#include "Data.hpp"

namespace Save
{
    void Save()
    {
        SmartTDB::SetIntValue("score",Data::pbscore);
        return;
    }
    void Load()
    {
        if (SmartTDB::GetIntValue("score") != 0)
        {
            Data::pbscore = SmartTDB::GetIntValue("score");
        }
        return;
    }
    void init()
    {
        SmartTDB::DeclareDBname("sav");
        return;
    }
}