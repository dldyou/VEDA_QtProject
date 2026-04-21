#include "schedulemanager.h"
ScheduleManager::ScheduleManager(QObject *parent) : QObject(parent) {}
void ScheduleManager::addSchedule(const Schedule &s) {
    schedules.append(s);
    emit schedulesChanged();
}

void ScheduleManager::updateSchedule(QString id, const Schedule &schedule) {
    for (int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getId() == id) {
            schedules[i] = schedule;
            break;
        }
    }
    emit schedulesChanged();
}

void ScheduleManager::removeSchedule(QString id) {
    for (int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getId() == id) {
            schedules.removeAt(i);
            break;
        }
    }
    emit schedulesChanged();
}

QList<Schedule> ScheduleManager::getSchedulesByContainText(const QString &text) const {
    QList<Schedule> filtered;

    // 검색어가 비어있으면 빈 리스트 반환
    if (text.isEmpty()) {
        return filtered;
    }

    for (const auto &schedule : schedules) {
        if (schedule.getTitle().contains(text, Qt::CaseInsensitive) ||
            schedule.getDescription().contains(text, Qt::CaseInsensitive)) {
            filtered.append(schedule);
        }
    }
    return filtered;
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

    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
        }
        else {
            return false;
        }
    }

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return false;
    }

    schedules.clear();

    QJsonArray jsonArray = doc.array();
    for (const auto &value : jsonArray) {
        schedules.append(Schedule::fromJsonObject(value.toObject()));
        qDebug() << value;
    }

    return true;
}

QList<Schedule> ScheduleManager::getSchedulesForDate(const QDate &date) const {
    QList<Schedule> filtered;
    for (const auto &schedule : schedules) {
        if (schedule.getStartTime().date() <= date && date <= schedule.getEndTime().date()) {
            filtered.append(schedule);
        }
    }
    return filtered;
}