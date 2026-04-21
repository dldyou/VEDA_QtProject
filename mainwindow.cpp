#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "schedulemanager.h"
#include "scheduleeditordialog.h"
#include "schedulecardwidget.h"

void applyStyleSheet(QWidget* widget, const QString& path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        widget->setStyleSheet(styleSheet);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    applyStyleSheet(this, ":/style/style/style.qss");

    btnAdd = new QPushButton("+", this);
    btnAdd->setObjectName("btnAdd");
    btnAdd->setCursor(Qt::PointingHandCursor);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::on_btnAdd_clicked);

    ui->cwCalender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    QTextCharFormat saturdayFormat;
    saturdayFormat.setForeground(QColor("#007bff"));
    saturdayFormat.setFontWeight(QFont::Bold);
    ui->cwCalender->setWeekdayTextFormat(Qt::Saturday, saturdayFormat);

    QTextCharFormat sundayFormat;
    sundayFormat.setForeground(QColor("#dc3545"));
    sundayFormat.setFontWeight(QFont::Bold);
    ui->cwCalender->setWeekdayTextFormat(Qt::Sunday, sundayFormat);

    scheduleManager = new ScheduleManager(this);
    connect(scheduleManager, &ScheduleManager::schedulesChanged, this, &MainWindow::updateList);
    connect(ui->leSearch, &QLineEdit::textChanged, this, &MainWindow::updateList);
    connect(ui->lwScheduleList, &QListWidget::itemSelectionChanged, this, &MainWindow::on_lwScheduleList_itemSelectionChanged);

    scheduleManager->loadSchedules();

    ui->lwScheduleList->setSpacing(4);
    ui->lwScheduleList->setFocusPolicy(Qt::NoFocus);

    selectedDate = QDate::currentDate();
    ui->lblSelectedDate->setText(selectedDate.toString(timeFormat));
    updateList();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cwCalender_selectionChanged() {
    selectedDate = ui->cwCalender->selectedDate();
    ui->lblSelectedDate->setText(selectedDate.toString(timeFormat));
    ui->leSearch->clear();
    updateList();
}

void MainWindow::updateList()
{
    QString searchText = ui->leSearch->text();

    ui->lwScheduleList->clear();

    // 화면 데이터 결정
    if (searchText.isEmpty()) {
        currentViewList = scheduleManager->getSchedulesForDate(selectedDate);
    }
    else {
        currentViewList = scheduleManager->getSchedulesByContainText(searchText);
    }

    // 테이블 출력
    for (int i = 0; i < currentViewList.size(); i++) {
        const Schedule &schedule = currentViewList[i];

        QListWidgetItem *item = new QListWidgetItem(ui->lwScheduleList);
        ScheduleCardWidget *card = new ScheduleCardWidget(schedule);

        item->setSizeHint(card->sizeHint());

        connect(card, &ScheduleCardWidget::deleteRequested, this, &MainWindow::on_Schedule_DeleteRequested);

        ui->lwScheduleList->addItem(item);
        ui->lwScheduleList->setItemWidget(item, card);
    }
}

void MainWindow::on_btnAdd_clicked() {
    ScheduleEditorDialog dlg(this);
    // 날짜 전달
    dlg.setDate(selectedDate);

    connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
            this, [this](const Schedule &s){
                scheduleManager->addSchedule(s);
                scheduleManager->saveSchedules();

                qDebug() << "시작 날짜:" << s.getStartTime().toString(Qt::ISODate);
                qDebug() << "끝 날짜:" << s.getEndTime().toString(Qt::ISODate);
                qDebug() << "저장 완료";
            });

    dlg.exec();
}

void MainWindow::on_Schedule_DeleteRequested(QString id) {
    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "삭제 확인", "정말 삭제하시겠습니까?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        scheduleManager->removeSchedule(id);
        scheduleManager->saveSchedules();
    }
}

void MainWindow::on_lwScheduleList_itemSelectionChanged() {
    for (int i = 0; i < ui->lwScheduleList->count(); ++i) {
        QListWidgetItem *item = ui->lwScheduleList->item(i);
        ScheduleCardWidget *card = qobject_cast<ScheduleCardWidget*>(ui->lwScheduleList->itemWidget(item));

        if (card) {
            card->setCardSelected(item->isSelected());
        }
    }
}


void MainWindow::on_lwScheduleList_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui->lwScheduleList->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "오류", "수정할 항목을 선택해주세요.");
        return;
    }

    Schedule selected = currentViewList[row];

    ScheduleEditorDialog dlg(this);
    dlg.setSchedule(selected);

    connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
            this, [this, selected](const Schedule &s) {
                scheduleManager->updateSchedule(selected.getId(), s);
                scheduleManager->saveSchedules();
            });

    dlg.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    if (btnAdd) {
        int paddingRight = 30;
        int paddingBottom = 30;
        int btnWidth = 60;
        int btnHeight = 60;

        btnAdd->setGeometry(this->width() - btnWidth - paddingRight,
                            this->height() - btnHeight - paddingBottom,
                            btnWidth, btnHeight);

        btnAdd->raise();
    }
}
