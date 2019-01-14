example of erase table from one action



### unlock wallet

```bash
cleos wallet unlock
PW5KZEh7vs5zvVgyyPQnMhiHh4XXKQ2Xit9ZsLrVgiGx8HhUST84N
```



### create account

```bash
cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio erasetable EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio bob EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```



### compile and deploy

```bash
## compile
eosio-cpp -I include -o erasetable.wasm erasetable.cpp --abigen

##deploy
cleos set contract erasetable /Users/zhong/coding/CLion/contracts/eos-contract-example/02-erase-table erasetable.wasm erasetable.abi
```



### add records

```bash
cleos push action erasetable insert '["bob"]' -p bob@active
cleos push action erasetable insert '["alice"]' -p alice@active
```



### query table

```bash
cleos get table erasetable erasetable records
```

Result:

```bash
{
  "rows": [{
      "key": "alice"
    },{
      "key": "bob"
    }
  ],
  "more": false
}
```



### erase table

```bash
cleos push action erasetable erase '[]' -p erasetable@active
```



query again:

```bash
cleos get table erasetable erasetable records
```



Result:

```bash
{
  "rows": [],
  "more": false
}
```









