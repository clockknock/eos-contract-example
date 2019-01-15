from this demo you can learn:

1. instantiation a contract from another contract

2. invoke it's static action(such as eosio.token's get_balance )



### unlock wallet

```bash
cleos wallet unlock
PW5KZEh7vs5zvVgyyPQnMhiHh4XXKQ2Xit9ZsLrVgiGx8HhUST84N
```



### create account

```bash
cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio instcontract EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```



### compile and deploy

```bash
## compile
eosio-cpp -I include -o instcontract.wasm instcontract.cpp --abigen

##deploy
cleos set contract instcontract /Users/zhong/coding/CLion/contracts/eos-contract-example/04-instantiation-contract-in-another-contract instcontract.wasm instcontract.abi
```



### instant

pass a account name and get it's balance of `EOS`

```bash
cleos push action instcontract instant '["alice"]' -p alice@active
```

Result:

```bash
executed transaction: 80ef5dda1afe44e15b9f2502947b624d7cf91d13253988c4ab3463d7182b0836  104 bytes  365 us
#  instcontract <= instcontract::instant        {"user":"alice"}
>> alice's balance is 907.6304 EOS
```









