example of erase table from one action
from this example you can learn:
1.iterator the multi_index_table and erase them all.



### unlock wallet

```bash
cleos wallet unlock
PW5KZEh7vs5zvVgyyPQnMhiHh4XXKQ2Xit9ZsLrVgiGx8HhUST84N
```



### create account

```bash
cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio erasetable EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```



### compile and deploy

```bash
## compile
eosio-cpp -I include -o erasetable.wasm erasetable.cpp --abigen

##deploy
cleos set contract erasetable /Users/zhong/coding/CLion/contracts/eos-contract-example/02-erase-table erasetable.wasm erasetable.abi
```



### add records
1. add records to multi_index_table
```bash
cleos push action erasetable insert '["bob"]' -p bob@active
cleos push action erasetable insert '["alice"]' -p alice@active
```



### query table
2. check table's records

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
3. push action to erase table

```bash
cleos push action erasetable erase '[]' -p erasetable@active
```



query again:

```bash
cleos get table erasetable erasetable records
```



Result:
you can see the table is empty now.

```bash
{
  "rows": [],
  "more": false
}
```









