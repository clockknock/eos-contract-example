let ArrayAction = require('../contracts/arrayaction');

let arrayAction = {};
before(() => {
    arrayAction = new ArrayAction("arrayaction", "active");
});

describe('test contract', function () {

    it('test sendarray', async () => {
        let receipt = await arrayAction.sendarray(["alice","bob","click"]);
        console.info("record:", JSON.stringify(receipt, null, 2), "\n ");
    });

});
