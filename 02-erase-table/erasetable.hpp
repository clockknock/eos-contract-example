#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

namespace eosio {

    using std::string;
    using std::vector;

    class [[eosio::contract("erasetable")]] erasetable : public contract {
    public:
        using contract::contract;

        erasetable(name receiver, name code, datastream<const char *> ds)
                : contract(receiver, code, ds) {}

        [[eosio::action]]
        void insert(name user);

        [[eosio::action]]
        void erase();


    private:
        struct [[eosio::table]] recorder {
            name key;
            uint64_t primary_key() const { return key.value; }
        };

        using record_index = eosio::multi_index<"records"_n, recorder>;

    };

} /// namespace eosio