#ifndef SCHEDULEEDITORDIALOG_H
#define SCHEDULEEDITORDIALOG_H
#include "schedule.h"
#include <QDialog>

namespace Ui {
class ScheduleEditorDialog;
}

/**
 * @class ScheduleEditorDialog
 * @brief 일정 편집 대화상자 클래스
 * 
 * - 일정의 제목, 설명, 시작 시간, 종료 시간, 카테고리 정보를 입력받아 새로운 일정을 생성하거나 기존 일정을 수정할 수 있는 대화상자입니다.
 * 
 * - 사용자가 일정을 저장하면 `scheduleSaved(const Schedule &schedule)` 신호를 발생시켜 MainWindow에 변경된 일정을 전달합니다.
 */
class ScheduleEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleEditorDialog(QWidget *parent = nullptr);
    
    // ui 요소에 일정 정보를 대입
    void setDate(const QDate &date);
    // 편집할 일정 정보를 설정
    void setSchedule(const Schedule &schedule);

    ~ScheduleEditorDialog();

private slots:
    // 저장 버튼 클릭 시 호출되는 슬롯 함수
    void on_btnSave_clicked();
    // 취소 버튼 클릭 시 호출되는 슬롯 함수
    void on_btnCancel_clicked();

signals:
    // 일정이 저장되었을 때 MainWindow에 변경된 일정을 전달하는 signal
    void scheduleSaved(const Schedule &schedule);

private:
    Ui::ScheduleEditorDialog *ui;
    // 편집 중인 일정 정보를 저장하는 멤버 변수
    Schedule schedule;
};

#endif // SCHEDULEEDITORDIALOG_H
