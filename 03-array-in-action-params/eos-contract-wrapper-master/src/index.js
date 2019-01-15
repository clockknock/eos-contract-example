let fs = require("fs");
let path = require("path");
let Config = require("../config");
let EosService = require("eos-service");

let eosService = new EosService(Config.NET_CONFIG);

async function getActions(contractName) {
    let api = await eosService.rpc.get_abi(contractName);
    let actions = api.abi.actions;
    let structs = api.abi.structs;

    actions.forEach((action) => {
        structs.forEach((struct) => {
            if (action.name === struct.name) {
                action.fields = struct.fields;
            }
        })
    });

    return actions;
}

async function makeContractWithEosjs(contractName) {
    //get api and get actions
    let actions = await getActions(contractName);

    let contractClassName = contractName.replace(contractName.charAt(0), contractName.charAt(0).toUpperCase());
    contractClassName = contractClassName.replace(".", "");

    let actionsBuffer = "";
    actions.forEach((action) => {

        //concat params string
        let params = "";
        if(action.fields===undefined){
            return;
        }
        for (let i = 0; i < action.fields.length; i++) {
            let field = action.fields[i];
            params += `${field.name}, `;

        }
        params = params.substr(0, params.length - 2);

        //concat methods
        actionsBuffer += `
    async ${action.name}(${params}) {
        return await api.transact({
            actions: [{
                account: this.name,
                name: "${action.name}",
                authorization: [{
                    actor: this.actor,
                    permission: this.permission
                }],
                data: {${params}}
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });        
    }
`;
    });

    return `require("eosjs");
let Config = require("../config");
let net_config = Config.NET_CONFIG;

let {Api, JsonRpc} = require("eosjs");
let JsSignatureProvider = require('eosjs/dist/eosjs-jssig');
const fetch = require('node-fetch');
const {TextDecoder, TextEncoder} = require('text-encoding');

let rpc = new JsonRpc(\`\${net_config.protocol}://\${net_config.host}:\${net_config.port}\`, {fetch});

const signatureProvider = new JsSignatureProvider.default([net_config.private_key]);
let api = new Api({
    rpc: rpc,
    signatureProvider,
    textDecoder: new TextDecoder,
    textEncoder: new TextEncoder
});

class ${contractClassName} {
    
    constructor(actor, permission) {
        this.name = "${contractName}";
        this.actor = actor;
        this.permission = permission;
    }
    ${actionsBuffer}
}
module.exports = ${contractClassName};`;
}

async function makeContractWithEosService(contractName) {
    //get api and get actions
    let actions = await getActions(contractName);

    let contractClassName = contractName.replace(contractName.charAt(0), contractName.charAt(0).toUpperCase());
    contractClassName = contractClassName.replace(".", "");

    let actionsBuffer = "";
    actions.forEach((action) => {
        //concat params string
        let params = "";
        if(action.fields===undefined){
            return;
        }
        for (let i = 0; i < action.fields.length; i++) {
            let field = action.fields[i];
            params += `${field.name}, `;

        }
        params = params.substr(0, params.length - 2);

        //concat methods
        actionsBuffer += `
    async ${action.name}(${params}) {
        let data = {${params}};
        return await eosService.pushAction(this.name, "${action.name}", this.actor, data,this.permission);        
    }
`;
    });

    return `let EosService = require("eos-service");
let Config = require("../config");
let eosService = new EosService(Config.NET_CONFIG);

class ${contractClassName} {
    
    constructor(actor, permission) {
        this.name = "${contractName}";
        this.actor = actor;
        this.permission = permission;
    }
    ${actionsBuffer}
}
module.exports = ${contractClassName};`;
}

function contractMaker() {
    Config.CONTRACTS.forEach(async (contractName) => {
        let contractsDir = path.join(__dirname, "../", `contracts`);

        //create contract folder
        let isDirExists = fs.existsSync(contractsDir);
        if (!isDirExists) {
            fs.mkdir(contractsDir);
        }
        let context;
        if(Config.USE_EOSSERVICE){
            context = await makeContractWithEosService(contractName);
        }else{
            context = await makeContractWithEosjs(contractName);
        }

        fs.writeFile(`${contractsDir}/${contractName}.js`, context, (err) => {
            if (err) {
                console.error(JSON.stringify("write error", null, 2), "\n ");
                console.error(JSON.stringify(err, null, 2), "\n ");
                return;
            }
            console.info(JSON.stringify("write success", null, 2), "\n ");
        });
    })

}

contractMaker();
