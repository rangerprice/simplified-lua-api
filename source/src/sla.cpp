#include "../header/sla.hpp"

using namespace std;

Sla::Sla() : SlaCore() {}

Sla::Sla(const std::string& file_path, const bool& default_lib) : SlaCore() 
{
	open(file_path, default_lib);
}

bool Sla::open(const std::string& file_path, const bool& default_lib) noexcept
{
	context = luaL_newstate();
	assert(context);

	if (default_lib) {
    	luaL_openlibs(context);
    }

	bool err = luaL_dofile(context, file_path.c_str());

	if (!err) {
		perror("Error: cannot open or execute " + *file_path.c_str());
		return false;
	}
	else {
		return true;
	}
}

void Sla::exec(const string & line) const noexcept
{
    luaL_dostring(context, line.c_str());
}

Sla::~Sla()
{
    lua_close(context);
}
