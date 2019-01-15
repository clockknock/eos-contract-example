#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

namespace eosio {

    using std::string;
    using std::vector;

    class [[eosio::contract("arrayaction")]] arrayaction : public contract {
    public:
        using contract::contract;

        arrayaction(name receiver, name code, datastream<const char *> ds)
                : contract(receiver, code, ds) {}

        [[eosio::action]]
        void sendarray(vector<string>& strs);

    };

} /// namespace eosio