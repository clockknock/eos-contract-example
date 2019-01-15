Let user pay for their ram and the contract owner can modify the value in the table.
from this example you can learn:
1. let multi_index_table can have vector params
2. you can add element to vector in multi_index_table
3. if there have a ram payer, you can modify the value and the system will not let you pay.


### unlock wallet

```bash
cleos wallet unlock
PW5KZEh7vs5zvVgyyPQnMhiHh4XXKQ2Xit9ZsLrVgiGx8HhUST84N
```



### create account

```bash
cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio vectortable EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```



### compile and deploy

```bash
## compile
eosio-cpp -I include -o vectortable.wasm vectortable.cpp --abigen

##deploy
cleos set contract vectortable /Users/zhong/coding/CLion/contracts/eos-contract-example/vector-in-multi-index-table vectortable.wasm vectortable.abi
```



### test bereferer
1.let user push this action, they will create a raw in multi_index_table, and they will be the RAM payer.

```bash
cleos push action vectortable bereferer '["alice"]' -p alice@active
cleos push action vectortable bereferer '["bob"]' -p bob@active

#code scpoe table
cleos get table vectortable vectortable referamount
```



### test addtoken
2.let user init the TOKEN which they want receive.

```bash
cleos push action vectortable addtoken '["bob","1.0000 EOS"]' -p alice@active
cleos push action vectortable addtoken '["bob","0.0000 ETH"]' -p bob@active
cleos push action vectortable addtoken '["bob","0.0000 BTC"]' -p bob@active

#code scpoe table
cleos get table vectortable vectortable referamount
```





### test modifyrefer
3. let contract owner or someone modify their raw to add TOKEN to them.

```bash
cleos push action vectortable modifyrefer '["bob","1.0000 EOS"]' -p vectortable@active
cleos push action vectortable modifyrefer '["bob","1.0000 ETH"]' -p vectortable@active
cleos push action vectortable modifyrefer '["bob","100.0000 BTC"]' -p vectortable@active

#code scpoe table
cleos get table vectortable vectortable referamount
```

