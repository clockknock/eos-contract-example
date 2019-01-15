#include "instcontract.hpp"

namespace eosio {

    void instcontract::instant(name user) {
        eosio::token eos("eosio.token"_n, "eosio.token"_n, get_datastream());
        const auto my_balance = eos.get_balance("eosio.token"_n, user, symbol_code("EOS"));
        print(user.to_string(),"'s balance is ", my_balance);
    }

} /// namespace eosio

EOSIO_DISPATCH(eosio::instcontract, (instant))