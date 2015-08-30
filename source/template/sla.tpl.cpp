const auto get(const std::string &var) const noexcept
{
	lua_settop(context, 0);
	lua_getglobal(context, var.c_str());

	return lua_tostring(context, 1);
}

auto get(const std::string &table, const int &indice) noexcept
{
    lua_settop(context, 0);
    lua_getglobal(context, table.c_str());
    lua_pushnumber(context, indice);
    lua_gettable(context, -2);

    return lua_tostring(context, 1);
}

