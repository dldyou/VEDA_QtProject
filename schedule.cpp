#include "schedule.h"

Schedule::Schedule()
{

}

Schedule::Schedule(
    QString title,
    QString description,
    QDateTime startTime,
    QDateTime endTime) {
    this->title = title;
    this->description = description;
    this->startTime = startTime;
    this->endTime = endTime;
}

// JSON 객체로 변환
QJsonObject Schedule::toJsonObject() const {
    QJsonObject obj;
    obj["title"] = title;
    obj["description"] = description;
    obj["start_time"] = startTime.toString(Qt::ISODate);
    obj["end_time"] = endTime.toString(Qt::ISODate);
    return obj;
}

// JSON 객체로부터 데이터 로드
Schedule Schedule::fromJsonObject(const QJsonObject &obj) {
    Schedule s;
    s.title = obj["title"].toString();
    s.description = obj["description"].toString();
    s.startTime = QDateTime::fromString(obj["start_time"].toString(), Qt::ISODate);
    s.endTime = QDateTime::fromString(obj["end_time"].toString(), Qt::ISODate);
    return s;
}