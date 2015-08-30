/*
	A useful and efficient way to use compile-time recursion, partial template specialization and variadic template parameter pack
	by rangerprice, alias absorbement.
*/
template <typename Val, typename Type, typename...Args>
inline void push(const std::pair<const Val, Type> var, const Args&...args) noexcept {
	const void* const valueptr = &var.first;
	operations[var.second](valueptr);

	nb_param++;
	push(args...);
}; 

void push() const noexcept {
	
};

template <typename...Args>
void call(const std::string & fname, const Args&...args) noexcept {
	lua_settop(context, 0);
    lua_getglobal(context, fname.c_str());

    push(args...);
    lua_call(context, nb_param, LUA_MULTRET);
};



