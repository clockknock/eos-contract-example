#include "arrayaction.hpp"

namespace eosio {

    void arrayaction::sendarray(vector<string>& strs) {
        for( const auto& value : strs ) {
            print(value+"--");
        }
    }

} /// namespace eosio

EOSIO_DISPATCH(eosio::arrayaction, (sendarray))