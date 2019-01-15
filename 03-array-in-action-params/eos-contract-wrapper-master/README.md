## Eos Contract Wrapper

Create eos contract js wrapper, make it OOP to calling contract.



### Usage

#### 1.clone

clone this project and run `npm install`  at project dir.



#### 2.change config

Check the `config`  dir you can see some config like:

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
    CONTRACTS: ["eosio.token"]
};

module.exports = config;
```

this project can create contract wrapper  using `eosjs`'s transact or my other project[ eos.service](https://github.com/clockknock/eos.service)'s transact. If you are using `eosjs`, change `USE_EOSSERVICE:true` to `USE_EOSSERVICE:false`, and add the contract name into `CONTRACTS` after you set code and set abi to your eos chain.



#### 3. run 

Back to `src`  and then **run** `index.js`, your contracts will show in `contracts`, after create wrapper, use example at [here](https://github.com/clockknock/eos-contract-wrapper/blob/master/test/test_wrapped_contract.js), just pass your parameter and you can get the transaction receipt.

```js

let EosToken = require('../contracts/eosio.token');

describe('test contract', function () {
    it('test eosio.token transfer', async () => {
        let receipt = await eosToken.transfer("alice", "bob", "1.0000 EOS", "test contract wrapper");
        console.info(JSON.stringify(receipt, null, 2), "\n ");
    });

});
```



> If you are just using these project to create contract class and copy them, please make sure  your config can be found by these files.

### What have I done

I'm using `fs` to write `CONTRACT_NAME.js` to `contracts` dir like the following code,  if you have using `eosjs` before, you will feel familiar with it. I have done most `require` template code that we will not want do that once again and once again. And if you using these class, you can get code from some IDE, make calling contract OOP. To Instantiation the contract object, pass the `actorName` and `permission` level to it, and enjoy.

```js

require("eosjs");
let Config = require("../config");
let net_config = Config.NET_CONFIG;

let {Api, JsonRpc} = require("eosjs");
let JsSignatureProvider = require('eosjs/dist/eosjs-jssig');
const fetch = require('node-fetch');
const {TextDecoder, TextEncoder} = require('text-encoding');

let rpc = new JsonRpc(`${net_config.protocol}://${net_config.host}:${net_config.port}`, {fetch});

const signatureProvider = new JsSignatureProvider.default([net_config.private_key]);
let api = new Api({
    rpc: rpc,
    signatureProvider,
    textDecoder: new TextDecoder,
    textEncoder: new TextEncoder
});

class Eosiotoken {
    
    constructor(actor, permission) {
        this.name = "eosio.token";
        this.actor = actor;
        this.permission = permission;
    }
    
    async transfer(from, to, quantity, memo) {
        return await api.transact({
            actions: [{
                account: this.name,
                name: "transfer",
                authorization: [{
                    actor: this.actor,
                    permission: this.permission
                }],
                data: {from, to, quantity, memo}
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });        
    }

    async issue(to, quantity, memo) {
        return await api.transact({
            actions: [{
                account: this.name,
                name: "issue",
                authorization: [{
                    actor: this.actor,
                    permission: this.permission
                }],
                data: {to, quantity, memo}
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });        
    }

    async create(issuer, maximum_supply) {
        return await api.transact({
            actions: [{
                account: this.name,
                name: "create",
                authorization: [{
                    actor: this.actor,
                    permission: this.permission
                }],
                data: {issuer, maximum_supply}
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });        
    }
    
}
module.exports = Eosiotoken;
```



and if you are using my  [eos.service](https://github.com/clockknock/eos.service), your will find the code is more concise, just like these:

```js
let EosService = require("eos-service");
let Config = require("../config");
let eosService = new EosService(Config.NET_CONFIG);

class Eosiotoken {
    
    constructor(actor, permission) {
        this.name = "eosio.token";
        this.actor = actor;
        this.permission = permission;
    }
    
    async transfer(from, to, quantity, memo) {
        let data = {from, to, quantity, memo};
        return await eosService.pushAction(this.name, "transfer", this.actor, data,this.permission);        
    }

    async issue(to, quantity, memo) {
        let data = {to, quantity, memo};
        return await eosService.pushAction(this.name, "issue", this.actor, data,this.permission);        
    }

    async create(issuer, maximum_supply) {
        let data = {issuer, maximum_supply};
        return await eosService.pushAction(this.name, "create", this.actor, data,this.permission);        
    }

    
}
module.exports = Eosiotoken;
```

