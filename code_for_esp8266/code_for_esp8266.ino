#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define DEBUG 1
const char ssid[]     = "i";         // wifi 名称
const char password[] = "asdf1234";     //wifi 密码
const char OneNetServer[] = "api.heclouds.com";
const char APIKEY[] = "TuqsxXg9j6ZxPUzg4kBiuD67cgI=";    // API KEY
int32_t DeviceId = 642850877;                             //设备ID
char DataStreams1[] = "qqqqq";
const size_t MAX_CONTENT_SIZE = 1024;                  // 最大内容长度
const unsigned long HTTP_TIMEOUT = 2100;                // 超时时间
int stream1;                         //用于存放返回的数值
WiFiClient client;
const int tcpPort = 80;
struct UserData 
{
    int errno_val;                // 错误返回值
    char error[32];               // 错误返回信息
    int recived_val;             // 接收数据值
    char udate_at[32];            // 最后更新时间及日期
};

//
//跳过 HTTP 头，使我们在响应正文的开头
//
bool skipResponseHeaders() 
{
    char endOfHeaders[] = "\r\n\r\n";
    client.setTimeout(HTTP_TIMEOUT);
    bool ok = client.find(endOfHeaders);
    if (!ok) 
    {
      Serial.println("No response or invalid response!"); //未响应
    }
    return ok;
}
//
//从HTTP服务器响应中读取正文 
//
void readReponseContent(char* content, size_t maxSize) 
{
    //  size_t length = client.peekBytes(content, maxSize);
    size_t length = client.readBytes(content, maxSize);
    delay(20);
    //Serial.println(length);
    //Serial.println("Get the data from Internet!"); //获取到数据
    content[length] = 0;
    //Serial.println(content);
    //Serial.println("Read Over!");
}
//
// 解析数据存储到传入的结构体中
//
bool parseUserData_test(char* content, struct UserData* userData) 
{
    const size_t BUFFER_SIZE = 1024;
    // 在堆栈上分配一个临时内存池 -- Allocate a temporary memory pool on the stack
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    // 如果堆栈的内存池太大，使用 DynamicJsonBuffer jsonBuffer 代替
    // --If the memory pool is too big for the stack, use this instead:
    //  --DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(content);
    if (!root.success()) 
    {
      Serial.println("JSON parsing failed!");
      return false;
    }
    // 复制需要的信息到userData结构体中
    userData->errno_val = root["errno"];
    strcpy(userData->error, root["error"]);
    // 成功返回0 -- Number 0 represents successful 
    if ( userData->errno_val == 0 ) 
    {
      userData->recived_val = root["data"]["datastreams"][0]["datapoints"][0]["value"];
      strcpy(userData->udate_at, root["data"]["datastreams"][0]["datapoints"][0]["at"]);
      //Serial.print("Recived Value : ");
      //Serial.print(userData->recived_val);
      //Serial.print("\t The last update time : ");
      //Serial.println(userData->udate_at);
    }
   // Serial.print("errno : ");
   // Serial.print(userData->errno_val);
    //Serial.print("\t error : ");
    //Serial.println(userData->error);
  
    return true;
}

// 读取数据
int readData(int dId, char dataStream[])
{
    // 创建发送请求的URL 
    String url = "/devices/";
    url += String(dId);
    url += "/datapoints?datastream_id=";
    url += dataStream;

    // 创建发送指令 
    String send_data = String("GET ") + url + " HTTP/1.1\r\n" +
                     "api-key:" + APIKEY + "\r\n" +
                     "Host:" + OneNetServer + "\r\n" +
                     "Connection: close\r\n\r\n";
    // 发送指令 
    client.print(send_data);
    // 调试模式串口打印发送的指令
    if (DEBUG)
    {
      //Serial.println(send_data);
    }
    unsigned long timeout = millis();
    while (client.available() == 0) 
    {
      if (millis() - timeout > 2000) 
      {
        //Serial.println(">>> Client Timeout !");
        client.stop();
        break;
      }      
    }

    if (skipResponseHeaders())  
    { 
      char response[MAX_CONTENT_SIZE];
      // 从服务器读取信息后解析
      readReponseContent(response, sizeof(response));
      UserData data1;
      if (parseUserData_test(response, &data1)) 
      {
       // Serial.println("Data parse OK!");
        return data1.recived_val;
      }
     }
}

void setup() 
{
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    Serial.begin(115200);
    WiFi.mode(WIFI_AP_STA);        //设置工作模式 
    delay(10);

//    Serial.println("");
//    Serial.print("Trying to connect to ");
//    Serial.println(ssid);
                                     // 连接到wifi  
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      //Serial.print(".");
    }
  
//    Serial.println("");
//    Serial.println("WiFi connected");
//    Serial.print("IP address: ");
//    Serial.println(WiFi.localIP());
    
}

void loop() 
{
    delay(100);
    //建立连接并判断 
    if (!client.connect(OneNetServer, tcpPort)) 
    {
      //Serial.println("connection failed");
      return;
    }
    //从云端获取值并存于 stream1
    stream1=readData(DeviceId, DataStreams1);
    //stream2=readData(DeviceId, DataStreams2);
    Serial.print(stream1);
    //if(stream1 == 2) GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 1);
    //else GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 0);
   //Serial.println("closing connection");
}
