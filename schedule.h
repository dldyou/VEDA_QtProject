#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include <QMessageBox>
#include <QUuid>

/**
 * @class Schedule
 * @brief 일정 정보를 담는 클래스
 *
 * - 일정의 제목, 설명, 시작 시간, 종료 시간, 카테고리 정보를 포함하며, JSON 객체로 변환 및 생성 기능을 제공합니다.
 * 
 * - 일정의 고유 ID를 UUID를 통해 자동으로 생성하여 관리합니다.
 */
class Schedule {
public:
    Schedule();
    Schedule(
        QString title, 
        QString description, 
        QDateTime startTime, 
        QDateTime endTime, 
        QString category, 
        QString categoryDetail
    );

    // Schedule 객체를 JSON 객체로 변환합니다.
    QJsonObject toJsonObject() const;
    // JSON 객체에서 Schedule 객체를 생성합니다.
    static Schedule fromJsonObject(const QJsonObject &obj);
    
    // Getter 및 Setter 메서드
    QString getId() const;
    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    QString getCategory() const;
    QString getCategoryDetail() const;

    void setId(const QString &id);
    void setData(const Schedule &schedule);
private:
    // 고유 ID
    QString id;
    // 일정 제목
    QString title;
    // 일정 설명
    QString description;
    // 일정 시작 시간
    QDateTime startTime;
    // 일정 종료 시간
    QDateTime endTime;
    // 일정 카테고리
    QString category;
    // 카테고리 상세 정보
    QString categoryDetail;
};

#endif