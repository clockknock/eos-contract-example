make user pay for their ram and the contract owner can modify the value in the table.



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

```bash
cleos push action vectortable bereferer '["bob"]' -p bob@active

#code scpoe table
cleos get table vectortable vectortable referamount
```



### test addtoken

```bash
cleos push action vectortable addtoken '["bob","1.0000 EOS"]' -p bob@active
cleos push action vectortable addtoken '["bob","0.0000 ETH"]' -p bob@active
cleos push action vectortable addtoken '["bob","0.0000 BTC"]' -p bob@active

#code scpoe table
cleos get table vectortable vectortable referamount
```





### test modifyrefer

```bash
cleos push action vectortable modifyrefer '["bob","1.0000 EOS"]' -p vectortable@active
cleos push action vectortable modifyrefer '["bob","1.0000 ETH"]' -p vectortable@active
cleos push action vectortable modifyrefer '["bob","100.0000 BTC"]' -p vectortable@active

#code scpoe table
cleos get table vectortable vectortable referamount
```

