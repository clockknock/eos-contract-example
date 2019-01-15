#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

#include "eosio.token.hpp"

namespace eosio {

    using std::string;
    using std::vector;

    class [[eosio::contract("instcontract")]] instcontract : public contract {
    public:
        using contract::contract;

        instcontract(name receiver, name code, datastream<const char *> ds)
                : contract(receiver, code, ds) {}

        [[eosio::action]]
        void instant(name user);

    };

} /// namespace eosio