#include <Arduino.h>

#define BLINKER_MIOT_LIGHT
#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "e03de825f051";   //换成APP获取到的密匙
char ssid[] = "UROBEI";          //WiFi账号
char pswd[] = "UROBEI123";   //WIFI密码

int GPIOpin=2;//定义GPIO口用于控制继电器
int GPIOFENGS=23;//风扇连接端口

#define BUTTON_1 "ButtonKey"


BlinkerButton Button1("12");     //这里需要根据自己在BLINKER里面设置的名字进行更改
BlinkerButton Button2("34");     //这里需要根据自己在BLINKER里面设置的名字进行更改

void button1_callback(const String & state)
{
    //BLINKER_LOG("get button state: ", state);
    Serial.println("in button1\n");
    Blinker.vibrate(); 
    if ((state=="123")||(state=="on")) {
        //digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(GPIOpin, HIGH);
        // 反馈开关状态
        Button1.print("on");
    } else if((state=="456")||(state=="off")){
        //digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(GPIOpin, LOW);
        // 反馈开关状态
        Button1.print("off");
    }
}



void miotPowerState(const String & state)
{
    Serial.println("in miotpowerState\n");
    BLINKER_LOG("need set power state: ",state);

    if (state == BLINKER_CMD_OFF) 
    {//如果语音接收到是关闭灯就设置GPIO口为高电平
        digitalWrite(GPIOpin, LOW);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_ON) 
    {
        digitalWrite(GPIOpin, HIGH);
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
}


void setup() {
    Serial.begin(115200);
    //pinMode(LED_BUILTIN, OUTPUT);
    pinMode(GPIOpin,OUTPUT);
    pinMode(GPIOFENGS,OUTPUT);
    digitalWrite(GPIOFENGS,LOW);
    digitalWrite(GPIOpin,LOW);//初始化，由于继电器是低电平触发。所以刚开始设为高电平
    //digitalWrite(LED_BUILTIN, HIGH);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button1_callback);
    BlinkerMIOT.attachPowerState(miotPowerState);//这段代码一定要加，不加小爱同学控制不了,务必在回调函数中反馈该控制状态


}

void loop()
{
    Blinker.run();
}