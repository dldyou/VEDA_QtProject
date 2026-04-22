#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDate>
#include <QList>

#include "schedulemanager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief 메인 윈도우 클래스
 * 
 * - 일정 관리 애플리케이션의 메인 윈도우를 담당하는 클래스입니다. 
 * 
 * - 달력 위젯과 일정 목록을 포함하며, 사용자가 일정을 추가, 수정, 삭제할 수 있는 인터페이스를 제공합니다.
 * 
 * - 달력에서 날짜를 선택하면 해당 날짜에 해당하는 일정 목록이 업데이트되고, 일정 목록에서 일정을 선택하거나 더블 클릭하여 편집할 수 있습니다.
 * 
 * - 일정 삭제는 일정 카드 위젯에서 마우스 오버 시 나타나는 삭제 버튼을 통해 이루어집니다. 삭제 요청이 발생하면 해당 일정 ID를 기반으로 일정을 삭제하고 목록을 업데이트합니다.
 * 
 * - 일정 데이터는 ScheduleManager 클래스를 통해 관리되며, 일정 데이터가 변경될 때마다 UI가 자동으로 업데이트됩니다.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // 윈도우 크기 변경 이벤트 처리 (플로팅 버튼 위치 조정 진행)
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 달력에서 날짜 선택 시 호출되는 슬롯 함수
    void on_cwCalender_selectionChanged();
    // 일정 추가 버튼 클릭 시 호출되는 슬롯 함수
    void on_btnAdd_clicked();
    // 일정 목록에서 일정 선택 시 호출되는 슬롯 함수
    void on_lwScheduleList_itemSelectionChanged();
    // 일정 목록에서 일정 더블 클릭 시 호출되는 슬롯 함수 (일정 편집)
    void on_lwScheduleList_itemDoubleClicked(QListWidgetItem *item);
    // 일정 삭제 요청 시 호출되는 슬롯 함수 (일정 카드 위젯에서 삭제 버튼 클릭 시)
    void on_Schedule_DeleteRequested(QString id);

private:
    Ui::MainWindow *ui;
    // 일정 데이터를 관리하는 ScheduleManager 객체
    ScheduleManager *scheduleManager;
    // 현재 보여줘야 하는 일정 목록 (선택된 날짜 혹은 검색 결과에 따라 정해짐)
    QList<Schedule> currentViewList;
    // 일정 추가 버튼
    QPushButton *btnAdd;

    // 현재 선택된 날짜를 저장하는 멤버 변수
    QDate selectedDate;
    // 일정 시간 표시 형식
    QString timeFormat = "yyyy-MM-dd";

    // 검색 타입을 받기 위한 선언
    SearchType getSearchType() const;

    // 일정 목록을 UI에 업데이트하는 함수
    void updateList();

};
#endif // MAINWINDOW_H
