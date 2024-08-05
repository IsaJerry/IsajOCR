#ifndef OCRSYSTEM_H
#define OCRSYSTEM_H

#include <QDateTime>
#include <Includer.h>
#include <isajdata.h>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <QDebug>

class OCRSystem
{
public:
    OCRSystem();
    QString getAccessToken(QString apiKey, QString secretKey);

    QString HandWriting(QString imageData);

    void SetAccessTokenTime();
    int GetLastTime();
    static size_t SaveAccessToken(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t getHandWrite(void *ptr, size_t size, size_t nmemb, void *stream);

    //static std::string handwriting_result;

    enum OCRModel
    {
        HandWrite = 300
    };

    int InitCount(enum OCRModel model);
    void SetLastCount(enum OCRModel model);

private:
    QString AccessTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";
    QString HandWriteUrl = "https://aip.baidubce.com/rest/2.0/ocr/v1/handwriting";
    QString AccessToken;



};

#endif // OCRSYSTEM_H
