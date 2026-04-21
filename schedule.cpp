#include "schedule.h"

Schedule::Schedule()
{
    this->id = QUuid::createUuid().toString();
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
    this->id = QUuid::createUuid().toString();
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
    Schedule schedule;
    schedule.title = obj["title"].toString();
    schedule.description = obj["description"].toString();
    schedule.startTime = QDateTime::fromString(obj["start_time"].toString(), Qt::ISODate);
    schedule.endTime = QDateTime::fromString(obj["end_time"].toString(), Qt::ISODate);
    return schedule;
}

QString Schedule::getId() const {
    return this->id;
}

QString Schedule::getTitle() const {
    return this->title;
}

QString Schedule::getDescription() const {
    return this->description;
}

QDateTime Schedule::getStartTime() const {
    return this->startTime;
}

QDateTime Schedule::getEndTime() const {
    return this->endTime;
}