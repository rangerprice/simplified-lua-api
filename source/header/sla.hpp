#pragma once
#ifndef SLA_HPP
#define SLA_HPP
#include "slacore.hpp"

class Sla final : public SlaCore
{
	public:
        Sla();
        virtual ~Sla();

        Sla(const std::string&, const bool& = true);
        bool open(const std::string&, const bool& = true) noexcept;
        void exec(const std::string&) const noexcept;
        #include "../template/sla.tpl.cpp"

};

#endif // SLA_HPP
