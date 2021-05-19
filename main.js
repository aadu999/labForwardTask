const {LfwBoilerInterface} = require('./boilerInterfaceTest')

function getTemp(){
return new Promise(resolve =>{
    console.log('Calling Interface : Get Temperature');
    let result = LfwBoilerInterface.statusUpdate();
    setTimeout(() => resolve("done!"), 4000)
}).then((s)=>{
    console.log('Calling Interface : Set Temp to 27.8')
    LfwBoilerInterface.setTemperature(27.8);
});
}


async function asyncCall() {
    const result = await getTemp();
  }

  asyncCall();