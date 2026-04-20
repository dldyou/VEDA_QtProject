#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
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

private slots:
    void on_cwCalender_selectionChanged();

    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnRemove_clicked();

private:
    Ui::MainWindow *ui;
    QDate selectedDate;
    ScheduleManager *scheduleManager;

    void updateTable();
};
#endif // MAINWINDOW_H
