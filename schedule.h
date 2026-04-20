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
private:
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
};

#endif // SCHEDULE_H
