#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include "schedule.h"
#include <QJsonArray>
#include <QFile>
#include <QList>

class ScheduleManager
{
public:
    ScheduleManager();
    // CRUD
    void addSchedule(const Schedule &schedule);
    void updateSchedule(int index, const Schedule &schedule);
    void removeSchedule(int index);
    // getter
    const QList<Schedule>& getSchedules() const { return schedules; }
    // 파일 입출력
    bool saveSchedules(const QString &fileName);
    bool loadSchedules(const QString &fileName);
signals:
    // 데이터가 변할 때마다 이 신호를 발생시켜 UI에 알림
    void schedulesChanged();
private:
    QList<Schedule> schedules;
};

#endif // SCHEDULEMANAGER_H
