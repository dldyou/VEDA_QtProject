#include "schedulemanager.h"

ScheduleManager::ScheduleManager() {}

void ScheduleManager::addSchedule(const Schedule &s) {
    schedules.append(s);
    emit schedulesChanged();
}

void ScheduleManager::updateSchedule(int index, const Schedule &s) {
    if (index >= 0 && index < schedules.size()) {
        schedules[index] = s;
        emit schedulesChanged();
    }
}

void ScheduleManager::removeSchedule(int index) {
    if (index >= 0 && index < schedules.size()) {
        schedules.removeAt(index);
        emit schedulesChanged();
    }
}

bool ScheduleManager::saveSchedules(const QString &fileName) {
    QJsonArray jsonArray;
    for (const auto &schedule : schedules) {
        jsonArray.append(schedule.toJsonObject());
    }

    QJsonDocument doc(jsonArray);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

// JSON 파일에서 리스트 로드
bool ScheduleManager::loadSchedules(const QString &fileName) {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return false;
    }

    QJsonArray jsonArray = doc.array();
    for (const auto &value : jsonArray) {
        schedules.append(Schedule::fromJsonObject(value.toObject()));
        qDebug() << value;
    }

    return true;
}

void ScheduleManager::setStandardSchedules() {
    Schedule schedule1 = Schedule("t1", "d1", QDateTime().currentDateTime().addDays(1), QDateTime().currentDateTime().addDays(1));
    Schedule schedule2 = Schedule("t2", "d2", QDateTime().currentDateTime(), QDateTime().currentDateTime().addDays(2));

    addSchedule(schedule1);
    addSchedule(schedule2);

    if (saveSchedules("schedules.json")) {
        qDebug() << "저장 성공";
    }
    else {
        qDebug() << "저장 실패";
    }
}