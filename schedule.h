#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include <QMessageBox>
#include <QUuid>

class Schedule {
public:
    Schedule();
    Schedule(QString title, QString description, QDateTime startTime,
             QDateTime endTime, QString category, QString categoryDetail);

    QJsonObject toJsonObject() const;
    static Schedule fromJsonObject(const QJsonObject &obj);

    QString getId() const;
    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    QString getCategory() const;
    QString getCategoryDetail() const;

    void setId(const QString &id);
    void setData(const Schedule &schedule);
private:
    QString id;
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
    // 카테고리 값 추가
    QString category;
    QString categoryDetail;
};

#endif