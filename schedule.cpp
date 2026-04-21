#include "schedule.h"

Schedule::Schedule()
{

}

Schedule::Schedule(QString title, QString description,
    QDateTime startTime, QDateTime endTime,
    QString category, QString categoryDetail) {
    this->title = title;
    this->description = description;
    this->startTime = startTime;
    this->endTime = endTime;
    this->category = category;
    this->categoryDetail = categoryDetail;
}

// JSON 객체로 변환
QJsonObject Schedule::toJsonObject() const {
    QJsonObject obj;
    obj["title"] = title;
    obj["description"] = description;
    obj["start_time"] = startTime.toString(Qt::ISODate);
    obj["end_time"] = endTime.toString(Qt::ISODate);
    obj["category"] = category;
    obj["category_detail"] = categoryDetail;
    return obj;
}

// JSON 객체로부터 데이터 로드
Schedule Schedule::fromJsonObject(const QJsonObject &obj) {
    Schedule schedule;
    schedule.title = obj["title"].toString();
    schedule.description = obj["description"].toString();
    schedule.startTime = QDateTime::fromString(obj["start_time"].toString(), Qt::ISODate);
    schedule.endTime = QDateTime::fromString(obj["end_time"].toString(), Qt::ISODate);
    schedule.category = obj["category"].toString();
    schedule.categoryDetail = obj["category_detail"].toString();
    return schedule;
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

QString Schedule::getCategory() const {
    return category;
}

QString Schedule::getCategoryDetail() const {
    return categoryDetail;
}