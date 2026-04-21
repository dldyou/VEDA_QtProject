#include <QDateTime>
#include <QCalendarWidget>
#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"
#include <QTextCharFormat>

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog) {
    ui->setupUi(this);

    auto setupCalendar = [](QDateTimeEdit* dateEdit) {
        QCalendarWidget* cal = dateEdit->calendarWidget();
        if (!cal) return;

        cal->setMinimumSize(400, 300);

        // 요일 헤더 (일, 토) 스타일
        QTextCharFormat satHeader;
        satHeader.setForeground(QColor("#4078ff"));
        satHeader.setFontWeight(QFont::Bold);

        QTextCharFormat sunHeader;
        sunHeader.setForeground(QColor("#e84118"));
        sunHeader.setFontWeight(QFont::Bold);

        cal->setWeekdayTextFormat(Qt::Saturday, satHeader);
        cal->setWeekdayTextFormat(Qt::Sunday, sunHeader);

        QObject::connect(cal, &QCalendarWidget::currentPageChanged, cal, [cal](int year, int month) {
        cal->setDateTextFormat(QDate(), QTextCharFormat()); // 초기화

        QTextCharFormat satFormat;
        satFormat.setForeground(QColor("#4078ff"));


        QTextCharFormat sunFormat;
         sunFormat.setForeground(QColor("#e84118"));


        QDate firstDay(year, month, 1);
        int days = firstDay.daysInMonth();

        for (int d = 1; d <= days; ++d) {
            QDate date(year, month, d);

            QTextCharFormat format;

            if (date.dayOfWeek() == Qt::Saturday) {
                format = satFormat;
            }
            else if (date.dayOfWeek() == Qt::Sunday) {
                format = sunFormat;
            }

            cal->setDateTextFormat(date, format);
            }
        });

        QDate today = QDate::currentDate();
        cal->setCurrentPage(today.year(), today.month());
    };

    setupCalendar(ui->deStart);
    setupCalendar(ui->deEnd);

    // 2. 초기값 및 Placeholder 설정
    QDateTime now = QDateTime::currentDateTime();
    ui->deStart->setDateTime(now);
    ui->deEnd->setDateTime(now.addSecs(3600));

    ui->cbCategory->setCurrentIndex(-1);
    ui->leTitle->setPlaceholderText("제목을 입력하세요");
    ui->teContent->setPlaceholderText("내용을 입력하세요");
    ui->leCategoryDetail->setPlaceholderText("세부 내용을 입력하세요");
    ui->leCategoryDetail->setEnabled(false);

    connect(ui->cbCategory, &QComboBox::currentIndexChanged, this, [=](int index){
        ui->leCategoryDetail->setEnabled(index >= 0);
    });

    // 전체 스타일시트 적용
    this->setStyleSheet(R"(
/* 기본 다이얼로그 */
QDialog {
    background-color: #f5f6fa;
}

QLabel {
    font-weight: bold;
    color: #2f3640;
}

/* 입력 위젯 */
QLineEdit,
QTextEdit,
QComboBox,
QDateTimeEdit {
    border: 1px solid #dcdde1;
    border-radius: 10px;
    padding: 6px 10px;
    background: white;
}

QLineEdit:focus,
QTextEdit:focus,
QComboBox:focus,
QDateTimeEdit:focus {
    border: 1px solid #4078ff;
}


/* 드롭다운 (아이콘만) */
QComboBox::drop-down,
QDateTimeEdit::drop-down {
    border: none;
    background: none;
    subcontrol-origin: padding;
    subcontrol-position: top right;
    width: 20px;
}

QComboBox::down-arrow,
QDateTimeEdit::down-arrow {
    image: url(:/icons/grayDropDown.svg);
    width: 12px;
    height: 12px;
}

QPushButton {
    background-color: #4078ff;
    color: white;
    border-radius: 8px;
    padding: 8px 16px;
    font-weight: bold;
}

QPushButton:hover {
    background-color: #3065d1;
}

QPushButton#btnCancel {
    background-color: #dcdde1;
    color: #2f3640;
}

QPushButton#btnCancel:hover {
    background-color: #c8c9cc;
}

QCalendarWidget QWidget#qt_calendar_navigationbar {
    background-color: #dbeafe;
}


QCalendarWidget QToolButton#qt_calendar_prevmonth,
QCalendarWidget QToolButton#qt_calendar_nextmonth {
    qproperty-iconSize: 12px;
    width: 22px;
    height: 22px;
}

QCalendarWidget QToolButton {
    color: #2f3640;
    background: transparent;
    font-weight: 600;
    font-size: 13px;
    border: none;
    padding: 4px 8px;
    border-radius: 6px;
}

QCalendarWidget QToolButton:hover {
    background-color: #e7f0ff;
}

QCalendarWidget QToolButton:pressed {
    background-color: #dbeafe;
    color: white;
}

QCalendarWidget QHeaderView::section {
    color: #718093;
    background-color: white;
    padding: 4px;
    border: none;
}

QCalendarWidget QAbstractItemView {
    border: none;
    outline: none;
    selection-background-color: transparent;
}

QCalendarWidget QAbstractItemView::item {
    border-radius: 6px;
}

QCalendarWidget QAbstractItemView::item:selected {
    background: transparent;
    color: #000000;
    font: bold;
}

QCalendarWidget QAbstractItemView::item:hover {
    background-color: #dfe6ff;
}
)");
}

ScheduleEditorDialog::~ScheduleEditorDialog() {
    delete ui;
}

void ScheduleEditorDialog::on_btnSave_clicked() {
    QString title = ui->leTitle->text();
    QString content = ui->teContent->toPlainText();

    QString category = ui->cbCategory->currentText();
    QString categoryDetail = ui->leCategoryDetail->text();

    QDateTime startDateTime = ui->deStart->dateTime();
    QDateTime endDateTime = ui->deEnd->dateTime();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "경고", "제목을 입력하세요.");
        return;
    }

    // 👉 카테고리 선택 안 했을 때
    if (ui->cbCategory->currentIndex() < 0) {
        QMessageBox::warning(this, "경고", "카테고리를 선택해주세요.");
        return;
    }

    if (startDateTime > endDateTime) {
        QMessageBox::warning(this, "경고", "종료 시간이 시작 시간보다 빠릅니다.");
        return;
    }

    Schedule scheduleData(
        title, 
        content, 
        startDateTime, 
        endDateTime,  
        category, 
        categoryDetail
    );

    schedule.setData(scheduleData);
    emit scheduleSaved(schedule);
    accept();
}

void ScheduleEditorDialog::setDate(const QDate &date) {
    ui->deStart->setDate(date);
    ui->deEnd->setDate(date);
}

void ScheduleEditorDialog::setSchedule(const Schedule &schedule) {
    this->schedule = schedule;
    ui->leTitle->setText(schedule.getTitle());
    ui->teContent->setText(schedule.getDescription());

    ui->deStart->setDateTime(schedule.getStartTime());
    ui->deEnd->setDateTime(schedule.getEndTime());

    ui->cbCategory->setCurrentText(schedule.getCategory());
    ui->leCategoryDetail->setText(schedule.getCategoryDetail());

    // 👉 수정 모드에서는 detail 활성화
    ui->leCategoryDetail->setEnabled(true);
}

void ScheduleEditorDialog::on_btnCancel_clicked() {
    reject();
}

