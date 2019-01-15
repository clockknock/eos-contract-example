demo of push actions with array string.

from this example you can learn:
1. declare an action with vector params which let you can send array to contract.
2. command line with push array.
3. push action with JavaScript from contract-wrapper.



### unlock wallet

```bash
cleos wallet unlock
PW5KZEh7vs5zvVgyyPQnMhiHh4XXKQ2Xit9ZsLrVgiGx8HhUST84N
```



### create account

```bash
cleos system newaccount --stake-net '0.7000 EOS' --stake-cpu '0.7000 EOS' --buy-ram-kbytes 20480000 eosio arrayaction EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```



### compile and deploy

```bash
## compile
eosio-cpp -I include -o arrayaction.wasm arrayaction.cpp --abigen

##deploy
cleos set contract arrayaction /Users/zhong/coding/CLion/contracts/eos-contract-example/03-array-in-action-params arrayaction.wasm arrayaction.abi
```



### sendarray

```bash
#push action with params name
cleos push action arrayaction sendarray '{"strs":["a","b"]}' -p alice@active

#push action without params name
cleos push action arrayaction sendarray '[["a","b"]]' -p alice@active
```

Result:

```bash
executed transaction: f4b8672ce2ae016803194ce858b864e8583b1c7da73a6db344bce3f36f88357a  104 bytes  1685 us
#   arrayaction <= arrayaction::sendarray       {"strs":["a","b"]}
>> a--b--
```





## push action with contract wrapper

1. enter the contract wrapper's dir:

```bash
cd eos-contract-wrapper-master/
```



2. check network config at `config` directory(**specify your private_key**):

```js
let config = {
    NET_CONFIG: {
        blockchain: 'eos',
        protocol: 'http',
        host: 'localhost',
        port: 80,
        chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f',
        private_key: "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"
    },
    USE_EOSSERVICE:true,
    CONTRACTS: ["arrayaction"]
};


module.exports = config;

```





3. install dependencies:

```bash
npm install
```



4. run:

```bash
npm start
```



5. enter `test` dir run test



