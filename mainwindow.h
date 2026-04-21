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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_cwCalender_selectionChanged();

    void on_btnAdd_clicked();

    void on_lwScheduleList_itemSelectionChanged();

    void on_lwScheduleList_itemDoubleClicked(QListWidgetItem *item);

    void on_Schedule_DeleteRequested(QString id);

private:
    Ui::MainWindow *ui;
    QDate selectedDate;
    QString timeFormat = "yyyy-MM-dd";

    ScheduleManager *scheduleManager;
    QList<Schedule> currentViewList;

    QPushButton *btnAdd;

    void updateList();
};
#endif // MAINWINDOW_H
