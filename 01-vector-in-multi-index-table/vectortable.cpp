/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "vectortable.hpp"

namespace eosio {

    void vectortable::bereferer(name user) {
        auto refer_amount_itr = _refer_amount.find(user.value);
        if (refer_amount_itr == _refer_amount.end()) {
            //emplace new user
            _refer_amount.emplace(user, [&](auto &ra) {
                ra.referer = user;
            });
        }
    }

    void vectortable::addtoken(name user, asset quantity) {
        auto refer_amount_itr = _refer_amount.find(user.value);

        if (refer_amount_itr != _refer_amount.end()) {
            _refer_amount.modify(refer_amount_itr, same_payer, [&](auto &ra) {
                vector<asset> &assets = ra.assets;
                bool should_add_new_token = true;
                for (int i = 0; i < assets.size(); i++) {
                    if (assets[i].symbol == quantity.symbol) {
                        should_add_new_token = false;
                        break;
                    }
                }

                eosio_assert(should_add_new_token,"you already support this token");
                quantity=asset(0,quantity.symbol);
                ra.assets.push_back(quantity);

            });
        }
    }

    void vectortable::modifyrefer(name user, asset quantity) {
        require_auth(get_self());
        auto refer_amount_itr = _refer_amount.find(user.value);

        if (refer_amount_itr != _refer_amount.end()) {
            _refer_amount.modify(refer_amount_itr, same_payer, [&](auto &ra) {
                vector<asset> &assets = ra.assets;
                for (int i = 0; i < assets.size(); i++) {
                    if (assets[i].symbol == quantity.symbol) {
                        assets[i] += quantity;
                        break;
                    }
                }
            });
        }
    }

} /// namespace eosio

EOSIO_DISPATCH(eosio::vectortable, (bereferer)(addtoken)(modifyrefer))