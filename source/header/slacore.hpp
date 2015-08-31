#pragma once
#ifndef SLACORE_HPP
#define SLACORE_HPP

#include <string>
#include <functional>
#include <map>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
}
#include <iostream>

class SlaCore
{
	public: 
		SlaCore();

		#include "../template/slacore.tpl.cpp"

		~SlaCore();

		enum class DataType {
			INT, 
			NUM, 
			STR, 
			BOOL, 
			NIL, 
			FUNC 
		};

		lua_State* context; 
	private:
		std::function<void(const void* const)> addInt = [this](const void* const p = nullptr) -> void { const int* const val = (int*)p; lua_pushinteger(context, *val); };
		std::function<void(const void* const)> addNum = [this](const void* const p = nullptr) -> void { const int* const val = (int*)p; lua_pushnumber(context, *val); };
		std::function<void(const void* const)> addStr = [this](const void* const p = nullptr) -> void { const std::string* const val = (std::string*)p; lua_pushstring(context, (*val).c_str()); };
		std::function<void(const void* const)> addBool = [this](const void* const p = nullptr) -> void { const bool* const val = (bool*)p; lua_pushboolean(context, *val); };
		std::function<void(const void* const)> addNil = [this](const void* const p = nullptr) -> void { lua_pushnil(context); };

		std::map<DataType, const std::function<void(const void* const)>> operations {
			{DataType::INT, addInt} ,
			{DataType::NUM, addNum} ,
			{DataType::STR, addStr} ,
			{DataType::BOOL, addBool} ,
			{DataType::NIL, addNil } ,
		};

		int nb_param = 0;
};

#endif // SLACORE_HPP
