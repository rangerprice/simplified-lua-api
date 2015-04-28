#ifndef SLA_H
#define SLA_H
#include <string>
#include <vector>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
}

using namespace std;

class Sla
{
    private:
        vector<void*> pams;
        vector<int> pamsType; // 1 FOR INT, 2 FOR STRING
        string file_path; // contient le répertoire du fichier lua
        lua_State* stat; // contient le ptr vers le contexte d'éxécution
        int int_val;
        string string_val;

        // ____________________ BACKEND METHOD
        // DON'T CALL THIS METHOD ! ITS PRIVATE !!

        // set the type of the param in pamsType.
        // If is string, set 2 in pamsType, if is int, set 1 in pamsType

        void setParamType(int *nb);
        void setParamType(string *str);

        // Return the value of pams[row]
        // the param type is useless. It just allow the member function overloading

        int getIntParam(int row);
        string getStrParam(int row, int type);

        // push the params val into the stack of lua

        void pushParam(int val);
        void pushParam(string val);


    public:
        Sla();

        // ____________________ FRONTEND METHOD
        // The list of method below can be call by the user of the class Sla

        Sla(string file_path); // create the execution context

        /* return the string value of the global variable
        varname in the lua context execution.
        For overload version of getStr(), return the string
        value of the element in table table where indice = indice

        do the same for getInt() but for int value
        */

        string getStr(string varname);
        string getStr(string table, int indice);

        int getInt(string varname);
        int getInt(string table, int indice);

        // Execute line in the context execution of lua
        void exec(string line);

        // call a function
        void call(string fname);


        /*
        Add a parameters for the function that will be called by call()
        */
        template<typename T>
        void setParam(T *p1)
        {
            void* ptr(0);
            ptr = p1;

            pams.push_back(ptr);
            setParamType(p1);
        }

        ~Sla();
};

#endif // SLA_H

