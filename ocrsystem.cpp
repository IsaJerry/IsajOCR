#include "ocrsystem.h"

OCRSystem::OCRSystem()
{
    AccessToken = (new ISAJData())->ReadData("Accesstoken");
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

QString OCRSystem::HandWriting(QString imageData)
{
    std::string url = HandWriteUrl.toStdString() + "?access_token=" + AccessToken.toStdString();
    CURL *curl = NULL;
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_httppost *post = NULL;
        curl_httppost *last = NULL;
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "image", CURLFORM_COPYCONTENTS, imageData.toStdString().data(), CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getHandWrite);
        CURLcode result_code = curl_easy_perform(curl);
        if(result_code != CURLE_OK)
        {
            QString a = curl_easy_strerror(result_code);
            QString b = "curl_easy_perform() failed: \n" + a;
            curl_easy_cleanup(curl);
            return b;
        }
        curl_easy_cleanup(curl);
        //qDebug()<<(new ISAJData())->ReadData("TempData");
        GetResult();
        return "success";
    }
    else
    {
        return "curl_easy_init() failed.";
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

void OCRSystem::GetResult()
{
    QString res = (new ISAJData())->ReadData("TempData");
    Json::Reader reader;
    Json::Value root;
    reader.parse(res.toStdString(),root);
    int num = root["words_result_num"].asInt();
    Json::Value words = root["words_result"];
    for(int i=0; i<num; i++)
    {
        result << QString::fromStdString(words[i]["words"].asString());
    }
}

QStringList OCRSystem::GetWordsList()
{
    return result;
}

void OCRSystem::SetLastCount(enum OCRModel model)
{
    ISAJData *last = new ISAJData();
    QString count = last->ReadData("LastCount");
    if(count == "null")
    {
        last->SaveData("LastCount", QString::number(model - 1));
    }
    last->SaveData("LastCount", QString::number(count.toInt() - 1));
}

size_t OCRSystem::SaveAccessToken(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string s((char *) ptr, size * nmemb);
    Json::Reader reader;
    Json::Value root;
    reader.parse(s,root);
    std::string rest = root["access_token"].asString();
    (new ISAJData())->SaveData("Accesstoken", QString::fromStdString(rest));
    return nmemb;
}

size_t OCRSystem::getHandWrite(void *ptr, size_t size, size_t nmemb, void *stream)
{
    (new ISAJData())->SaveData("TempData", QString::fromStdString(std::string((char *) ptr, size * nmemb)));
    return size * nmemb;
}

