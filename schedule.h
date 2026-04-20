#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include <QMessageBox>

class Schedule {
public:
    Schedule();
    Schedule(QString title, QString description,
             QDateTime startTime, QDateTime endTime);

    // getter/setter
    void setTitle(const QString &t);
    void setDescription(const QString &d);
    void setStartTime(const QDateTime &s);
    void setEndTime(const QDateTime &e);

    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;

    QJsonObject toJsonObject() const;
    static Schedule fromJsonObject(const QJsonObject &obj);

private:
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
};

#endif