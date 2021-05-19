#include <iostream>
#include <random>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <nan.h>
#include <v8.h>
#include <time.h>
#include <thread>
#include <chrono>

using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;
using std::cout;
using std::endl;
using std::pow;
using std::setprecision;
using std::sqrt;
using v8::Function;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

using namespace std::chrono_literals;

class lab_boiler : public AsyncWorker
{

    //boiler temperature
    float boiler_temp{5.0f};
    int command;
    bool ack;
  

    //function to set the device temperature to desired value 
    bool setDeviceTemp(float tempValue)
    {
        //Exchange information with the device
        std::this_thread::sleep_for(1s);
        return true;
    }
    //function to get boiler temperature
    float getDeviceTemp()
    {
        //generating random temperature value in the range of 20->400
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<> distr(20, 400);
        boiler_temp = distr(eng);
        std::this_thread::sleep_for(2s);
        return boiler_temp;
    }

public:
    lab_boiler(Callback *callback, int cmd, float btmp) : AsyncWorker(callback){
        command=cmd;
        boiler_temp=btmp;
    }

    ~lab_boiler() {}

    void Execute()
    {
        //used command as an integer for ease of implementation
        // command 1-> trigers setDeviceTemp function. 2-> gets the current temperature
        
        if (command == 1)
        {
            ack = setDeviceTemp(boiler_temp);
            //boiler_temp = boiler_temp
        }
        else if (command == 2)
        {
            boiler_temp = getDeviceTemp();
            ack = true;
        }
    }
    void HandleOKCallback(){

        Local<Value> argv[]={
            Null(),
            New<Number>(boiler_temp),
            New<v8::Boolean>(ack)
        };
        callback->Call(3,argv);
    }
};

NAN_METHOD(performAsync){
    int jsCmd = To<int>(info[0]).FromJust();
    double jsTemp = To<double>(info[1]).FromJust();
    Callback* callback = new Callback(info[2].As<Function>());
    AsyncQueueWorker(new lab_boiler(callback,jsCmd,jsTemp));
}
NAN_MODULE_INIT(Init){
    NAN_EXPORT(target,performAsync);
}
NODE_MODULE(boiler, Init)
