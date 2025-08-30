#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <map>
#include <QFile>
#include <QCoreApplication>


class WeatherTool{
public:
    WeatherTool(){
        QString fileName=QCoreApplication::applicationDirPath();
        fileName+="/citycode-2019-08-23.json";
        QFile file(fileName);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray json=file.readAll();
        file.close();
        QJsonParseError err;
        QJsonDocument jsonDoc=QJsonDocument::fromJson(json,&err);
        QJsonArray citys=jsonDoc.array();
        for(int i=0;i<citys.size();i++)
        {
            QString code=citys.at(i).toObject().value("city_code").toString();
            QString city=citys.at(i).toObject().value("city_name").toString();
            if(code.size()>0)
                 m_mapCity2Code[city] = code;

        }


    }

    QString operator[](const QString &city){
        std::map<QString,QString>::iterator it=m_mapCity2Code.find(city);
        if(it==m_mapCity2Code.end()){
            for(int i=1;i<4;i++){
            if(i==1){
            it=m_mapCity2Code.find(city+u8"市");}
            else if(i==2){
                QString modifiedCity = city;
                 modifiedCity.chop(1);
                 it=m_mapCity2Code.find(modifiedCity);
            }
            else{
                it=m_mapCity2Code.find(city+u8"县");
            }
           }
        }
        if(it!=m_mapCity2Code.end()){
            return it->second;
        }
        return "000000000";
    }

private:
    std::map<QString,QString> m_mapCity2Code;
};

#endif // WEATHERTOOL_H
