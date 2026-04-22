#include "schedulemanager.h"
#include <algorithm>

ScheduleManager::ScheduleManager(QObject *parent) : QObject(parent) {}
void ScheduleManager::addSchedule(const Schedule &schedule) {
    schedules.insert(schedule.getId(), schedule);
    emit schedulesChanged();
}

void ScheduleManager::updateSchedule(QString id, const Schedule &schedule) {
    schedules[schedule.getId()] = schedule;
    emit schedulesChanged();
}

void ScheduleManager::removeSchedule(QString id) {
    schedules.remove(id);
    emit schedulesChanged();
}

QList<Schedule> ScheduleManager::getSchedulesByContainText(
    const QString &text, SearchType type) const {
    QList<Schedule> filtered;

    if (text.isEmpty()) {
        return filtered;
    }

    for (const auto &schedule : schedules) {
        bool match = false;

        switch (type) {
        case SearchType::Title:
            match = schedule.getTitle().contains(text, Qt::CaseInsensitive);
            break;

        case SearchType::Content:
            match = schedule.getDescription().contains(text, Qt::CaseInsensitive);
            break;

        case SearchType::Category:
            match = schedule.getCategory().contains(text, Qt::CaseInsensitive);
            break;

        case SearchType::All:
            match =
                schedule.getTitle().contains(text, Qt::CaseInsensitive) ||
                schedule.getDescription().contains(text, Qt::CaseInsensitive) ||
                schedule.getCategory().contains(text, Qt::CaseInsensitive);
            break;
        }

        if (match) {
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
        Schedule schedule = Schedule::fromJsonObject(value.toObject());
        schedules.insert(schedule.getId(), schedule);
        qDebug() << value;
    }

    return true;
}

QList<Schedule> ScheduleManager::getSortedSchedules() const {
    QList<Schedule> ret = schedules.values();
    std::sort(ret.begin(), ret.end(), [](const Schedule& a, const Schedule& b) {
        if (a.getStartTime() == b.getStartTime()) {
            return a.getEndTime() < b.getEndTime();
        }
        return a.getStartTime() < a.getStartTime();
    });
    return ret;
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