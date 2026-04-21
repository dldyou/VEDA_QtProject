#ifndef SCHEDULECARDWIDGET_H
#define SCHEDULECARDWIDGET_H

#include <QWidget>
#include <QStyle>
#include <QEnterEvent>
#include "schedule.h"

namespace Ui {
class ScheduleCardWidget;
}

/**
 * @class ScheduleCardWidget
 * @brief 일정 카드 위젯 클래스
 * 
 * - 일정 정보를 시각적으로 표현하는 카드 형태의 위젯입니다. 
 * 
 * - 일정의 제목, 시간, 카테고리 등을 표시하며, 마우스 오버 시 삭제 버튼이 나타납니다.
 */
class ScheduleCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleCardWidget(const Schedule &schedule, QWidget *parent = nullptr);
    ~ScheduleCardWidget();

    // 카드 선택 상태 설정
    void setCardSelected(bool isSelected);

signals:
    // 삭제 요청 시 MainWindow에 일정 ID를 전달하는 signal
    void deleteRequested(QString id);

protected:
    // 마우스 오버 이벤트 처리
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::ScheduleCardWidget *ui;
    // 일정 ID를 저장하는 멤버 변수
    QString id;
};

#endif // SCHEDULECARDWIDGET_H
