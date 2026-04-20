#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include <QMessageBox>

class Schedule {
public:
    Schedule();
    Schedule(QString title, QString description, QDateTime startTime, QDateTime endTime);

    QJsonObject toJsonObject() const;
    static Schedule fromJsonObject(const QJsonObject &obj);

    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
private:
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
};

#endif