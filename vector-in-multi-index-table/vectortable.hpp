/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

namespace eosio {

    using std::string;
    using std::vector;

    class [[eosio::contract("vectortable")]] vectortable : public contract {
    public:
        using contract::contract;

        vectortable(name receiver, name code, datastream<const char *> ds)
        : contract(receiver, code, ds),_refer_amount(get_self(), get_self().value){}

        [[eosio::action]]
        void bereferer(name user);

        [[eosio::action]]
        void addtoken(name user,asset quantity);

        [[eosio::action]]
        void modifyrefer(name user,asset quantity);

    private:

        TABLE refer_amounts {
            name referer;
            vector<asset> assets = {};

            uint64_t primary_key() const { return referer.value; }
        };

        typedef eosio::multi_index<"referamount"_n, refer_amounts> refer_amount;

        refer_amount _refer_amount;
    };

} /// namespace eosio