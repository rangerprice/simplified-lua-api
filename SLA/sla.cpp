#include "sla.h"
using namespace std;

Sla::Sla() {}

Sla::Sla(string file_path)
{
    this->stat = luaL_newstate();

    if (!stat) exit(0);

    luaL_openlibs(stat);

    if (luaL_dofile(stat, file_path.c_str())) exit(0);
}

string Sla::getStr(string varname)
{
    lua_settop(stat, 0);
    lua_getglobal(stat, varname.c_str());
    if (lua_isstring(stat, 1) == 1)
    {
        return lua_tostring(stat, 1);
        lua_pop(stat, 1);
        exit(0);
    }
    else {
        return NULL;
        exit(0);
    }
}

string Sla::getStr(string table, int indice)
{
    lua_settop(stat, 0);
    lua_getglobal(stat, table.c_str());
    lua_pushnumber(stat, indice);
    lua_gettable(stat, -2);

    return lua_tostring(stat, -1);
}

int Sla::getInt(string varname)
{
    lua_settop(stat, 0);
    lua_getglobal(stat, varname.c_str());

    if (lua_isnumber(stat, 1) == 1)
    {
        return lua_tonumber(stat, 1);
        lua_pop(stat, 1);
        exit(0);
    }
    else {
        return 0;
        exit(0);
    }
}

int Sla::getInt(string table, int indice)
{
    lua_settop(stat, 0);
    lua_getglobal(stat, table.c_str());
    lua_pushnumber(stat, indice);
    lua_gettable(stat, -2);

    return lua_tonumber(stat, -1);
}

void Sla::call(string fname)
{
    lua_settop(stat, 0);
    lua_getglobal(stat, fname.c_str());

    for (int i=0; i < (int)pams.size(); i++)
    {
        if (pamsType[i] == 1) pushParam(getIntParam(i));
        else pushParam(getStrParam(i, 2));
    }

    lua_call(stat, pams.size(), LUA_MULTRET);

    pams.erase(pams.begin(), pams.end());
}

void Sla::setParamType(int *nb)
{
    pamsType.push_back(1);
}

void Sla::setParamType(string *str)
{
    pamsType.push_back(2);
}

int Sla::getIntParam(int row)
{
    return *(int*)pams[row];
}

string Sla::getStrParam(int row, int type)
{
    return *(string*)pams[row];
}

void Sla::pushParam(int val)
{
    lua_pushnumber(stat, val);
}

void Sla::pushParam(string val)
{
    lua_pushstring(stat, val.c_str());
}

void Sla::exec(string line)
{
    luaL_dostring(stat, line.c_str());
}

Sla::~Sla()
{
    lua_close(stat);
}

