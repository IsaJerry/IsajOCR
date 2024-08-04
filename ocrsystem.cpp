#include "ocrsystem.h"

OCRSystem::OCRSystem()
{

}

QString OCRSystem::getAccessToken(QString apiKey, QString secretKey)
{
    CURL *curl;
    curl = curl_easy_init();
    if(curl)
    {
        std::string url = AccessTokenUrl.toStdString() + "&client_id=" + apiKey.toStdString() + "&client_secret=" + secretKey.toStdString();
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        QString reslut;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &reslut);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, SaveAccessToken);
        CURLcode result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK)
        {
            QString a = curl_easy_strerror(result_code);
            QString b = "curl_easy_perform() failed: \n" + a;
            //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result_code));
            curl_easy_cleanup(curl);
            return b;
        }
        curl_easy_cleanup(curl);
        AccessToken = (new ISAJData())->ReadData("Accesstoken");
        if(AccessToken == "")
        {
            return "Get AccessToken ERROR";
        }
        SetAccessTokenTime();
        ISAJData *save = new ISAJData();
        save->SaveData("API Key", apiKey);
        save->SaveData("Secret Key", secretKey);
        return "success";
    }
    else
    {
        return "Get AccessToken ERROR";
    }
}

void OCRSystem::SetAccessTokenTime()
{
    QDateTime time = QDateTime::currentDateTime();
    (new ISAJData())->SaveData("GetTokenTime", time.toString("yyyy-MM-dd hh:mm:ss"));
}

int OCRSystem::GetLastTime()
{
    QString time = (new ISAJData())->ReadData("GetTokenTime");
    if(time == "null")
    {
        return 0;
    }
    QDateTime nowTime = QDateTime::currentDateTime();
    QDateTime setTime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    return 30 - setTime.daysTo(nowTime);
}

size_t OCRSystem::SaveAccessToken(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string s((char *) ptr, size * nmemb);
    Json::Reader reader;
    Json::Value root;
    reader.parse(s,root);
    std::string rest = root["access_token"].asString();
    (new ISAJData())->SaveData("Accesstoken", QString::fromStdString(rest));
    //qDebug() << root["access_token"].asString();
    return nmemb;
}
