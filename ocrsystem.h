#ifndef OCRSYSTEM_H
#define OCRSYSTEM_H

#include <QDateTime>
#include <Includer.h>
#include <isajdata.h>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
//#include <aip-cpp-sdk-4.16.7/ocr.h>

class OCRSystem
{
public:
    OCRSystem();
    QString getAccessToken(QString apiKey, QString secretKey);

    void SetAccessTokenTime();
    int GetLastTime();
    static size_t SaveAccessToken(void *ptr, size_t size, size_t nmemb, void *stream);

private:
    QString AccessTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";
    QString AccessToken;

};

#endif // OCRSYSTEM_H
