#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>

class Schedule {
public:
    Schedule();
    Schedule(QString, QString, QDateTime, QDateTime);

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

#endif // SCHEDULE_H
