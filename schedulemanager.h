#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include "schedule.h"
#include <QJsonArray>
#include <QFile>
#include <QList>

/**
 * @class ScheduleManager
 * @brief 일정 관리 클래스
 * 
 * - 일정 객체를 관리하는 클래스입니다. 일정의 추가, 수정, 삭제, 검색 기능과 함께, 일정 데이터를 JSON 파일로 저장하고 불러오는 기능을 제공합니다.
 * 
 * - 일정 데이터가 변경될 때마다 `schedulesChanged()` 신호를 발생시켜 UI에 변경 사항을 알립니다.
 * 
 * - 일정은 고유 ID를 기반으로 관리되며, 일정 목록은 날짜별로 정렬되어 반환됩니다.
 */
class ScheduleManager : public QObject {
    Q_OBJECT
public:
    explicit ScheduleManager(QObject *parent = nullptr);
    // CRUD
    // 일정 추가
    void addSchedule(const Schedule &schedule);
    // 일정 수정
    void updateSchedule(QString id, const Schedule &schedule);
    // 일정 삭제
    void removeSchedule(QString id);
    // 일정 검색
    QList<Schedule> getSchedulesByContainText(const QString &text) const;

    // 일정 목록 반환 (시작 시간, 종료 시간 기준으로 정렬)
    QList<Schedule> getSortedSchedules() const;
    // 특정 날짜에 해당하는 일정 목록 반환
    QList<Schedule> getSchedulesForDate(const QDate &date) const;
    // 파일 입출력
    bool saveSchedules(const QString &fileName = "schedules.json");
    bool loadSchedules(const QString &fileName = "schedules.json");
signals:
    // 데이터가 변할 때마다 이 신호를 발생시켜 UI에 알림
    void schedulesChanged();
private:
    // 일정 데이터를 저장하는 해시맵 (ID -> Schedule)
    QHash<QString, Schedule> schedules;
};

#endif // SCHEDULEMANAGER_H
