//  const LfwBoiler = require('./LfwBoiler');

//  let result;

//  result = LfwBoiler.boiler.async(1,21.1,(err,result)=>{
//      console.log(result);
//  });

const boiler_addon = require('./LfwBoiler');

class LfwBoilerInterface{

    //list operations the device can perform
   static listOperation(){
       return [
           'Update Temperature',
           'Check Temperature'
       ];
   }

   static async statusUpdate(){
       //console.log('Calling Interface: Get Temperature');
       //calling the async function ==> async(cmd,temperature) cmd is command. Since less time using the same function for get and set

       boiler_addon.boiler.async(2,23.7,(err,result)=>{
        console.log('Temperature : '+result);
           return result;
       });
       console.log('Waiting For Response');
       
   }

   static async setTemperature(inpTemp){
       
       boiler_addon.boiler.async(1,inpTemp,(err,result)=>{
           console.log('Set Temperature to '+inpTemp+' Celsius');
           return result;
       });
       console.log('Waiting for Response');
   }
}

// LfwBoilerInterface.statusUpdate();
// LfwBoilerInterface.setTemperature(45.0);
// console.log('nadakunnu');

module.exports = {
    LfwBoilerInterface : LfwBoilerInterface
}
