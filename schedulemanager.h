#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include "schedule.h"
#include <QJsonArray>
#include <QFile>
#include <QList>

class ScheduleManager : public QObject {
    Q_OBJECT
public:
    explicit ScheduleManager(QObject *parent = nullptr);
    // CRUD
    void addSchedule(const Schedule &schedule);
    void updateSchedule(QString id, const Schedule &schedule);
    void removeSchedule(QString id);
    QList<Schedule> getSchedulesByContainText(const QString &text) const;

    QList<Schedule> getSortedSchedules() const;
    QList<Schedule> getSchedulesForDate(const QDate &date) const;
    // 파일 입출력
    bool saveSchedules(const QString &fileName = "schedules.json");
    bool loadSchedules(const QString &fileName = "schedules.json");
signals:
    // 데이터가 변할 때마다 이 신호를 발생시켜 UI에 알림
    void schedulesChanged();
private:
    QHash<QString, Schedule> schedules;
};

#endif // SCHEDULEMANAGER_H
