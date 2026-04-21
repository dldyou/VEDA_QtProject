#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include <QMessageBox>
#include <QUuid>

class Schedule {
public:
    Schedule();
    Schedule(QString title, QString description, QDateTime startTime, QDateTime endTime);

    QJsonObject toJsonObject() const;
    static Schedule fromJsonObject(const QJsonObject &obj);

    QString getId() const;
    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    void setId(const QString& id);
private:
    QString id;
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
};

#endif