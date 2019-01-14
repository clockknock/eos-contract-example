#include "erasetable.hpp"

namespace eosio {

    void erasetable::insert(name user) {
        record_index records(name(_code), _code.value);
        auto iterator = records.find(user.value);

        if (iterator == records.end()) {
            records.emplace(user, [&]( auto& row ) {
                row.key = user;
            });
        }
    }

    void erasetable::erase() {
        //only contract owner can erase table
        require_auth(get_self());

        record_index records(name(_code), _code.value);
        for (auto _table_itr = records.begin(); _table_itr != records.end();) {
            _table_itr = records.erase(_table_itr);
        }

    }

} /// namespace eosio

EOSIO_DISPATCH(eosio::erasetable, (insert)(erase))