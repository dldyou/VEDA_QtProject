#include <QDateTime>
#include <QCalendarWidget>
#include <QTextCharFormat>
#include <QMouseEvent>
#include <QAbstractItemView>
#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog) {

    ui->setupUi(this);

    // 캘린더 공통 설정 함수
    auto setupCalendar = [](QDateTimeEdit* dateEdit) {
        QCalendarWidget* cal = dateEdit->calendarWidget();
        if (!cal) return;

        // 캘린더 최소 크기 설정
        cal->setMinimumSize(400, 300);

        // 요일 헤더 색상 및 스타일 (토, 일)
        QTextCharFormat satHeader;
        satHeader.setForeground(QColor("#4078ff"));
        satHeader.setFontWeight(QFont::Bold);

        QTextCharFormat sunHeader;
        sunHeader.setForeground(QColor("#e84118"));
        sunHeader.setFontWeight(QFont::Bold);

        cal->setWeekdayTextFormat(Qt::Saturday, satHeader);
        cal->setWeekdayTextFormat(Qt::Sunday, sunHeader);

        // 월이 바뀔 때마다 날짜 스타일 재적용
        QObject::connect(cal, &QCalendarWidget::currentPageChanged, cal,
                         [cal](int year, int month) {

                             // 기존 스타일 초기화
                             cal->setDateTextFormat(QDate(), QTextCharFormat());

                             // 토요일 스타일
                             QTextCharFormat satFormat;
                             satFormat.setForeground(QColor("#4078ff"));

                             // 일요일 스타일
                             QTextCharFormat sunFormat;
                             sunFormat.setForeground(QColor("#e84118"));

                             QDate firstDay(year, month, 1);
                             int days = firstDay.daysInMonth();

                             // 해당 월의 모든 날짜 순회
                             for (int d = 1; d <= days; ++d) {
                                 QDate date(year, month, d);

                                 QTextCharFormat format;

                                 if (date.dayOfWeek() == Qt::Saturday) {
                                     format = satFormat;
                                 }
                                 else if (date.dayOfWeek() == Qt::Sunday) {
                                     format = sunFormat;
                                 }

                                 // 날짜별 스타일 적용
                                 cal->setDateTextFormat(date, format);
                             }
                         });

        // 현재 날짜 기준으로 캘린더 초기 페이지 설정
        QDate today = QDate::currentDate();
        cal->setCurrentPage(today.year(), today.month());
    };

    // 시작/종료 캘린더 설정
    setupCalendar(ui->deStart);
    setupCalendar(ui->deEnd);

    // 기본 날짜/시간 설정
    QDateTime now = QDateTime::currentDateTime();
    ui->deStart->setDateTime(now);
    ui->deEnd->setDateTime(now.addSecs(3600)); // 1시간 뒤

    // 초기 입력 상태 설정
    ui->cbCategory->setCurrentIndex(-1);
    ui->leTitle->setPlaceholderText("제목을 입력하세요");
    ui->teContent->setPlaceholderText("내용을 입력하세요");
    ui->leCategoryDetail->setPlaceholderText("세부 내용을 입력하세요");

    // 카테고리 선택 전까지 detail 비활성화
    ui->leCategoryDetail->setEnabled(false);

    // 카테고리 선택 시 detail 활성화
    connect(ui->cbCategory, &QComboBox::currentIndexChanged, this,
            [=](int index){
                ui->leCategoryDetail->setEnabled(index >= 0);
            });

    // 전체 스타일시트 적용
    this->setStyleSheet(R"(

/* 다이얼로그 기본 스타일 */
QDialog {
    background-color: #f5f6fa;
}

QLabel {
    font-weight: bold;
    color: #2f3640;
}

/* 입력 위젯 공통 스타일 */
QLineEdit,
QTextEdit,
QComboBox,
QDateTimeEdit {
    border: 1px solid #dcdde1;
    border-radius: 10px;
    padding: 6px 10px;
    background: white;
}

/* 포커스 시 강조 */
QLineEdit:focus,
QTextEdit:focus,
QComboBox:focus,
QDateTimeEdit:focus {
    border: 1px solid #4078ff;
}

/* 드롭다운 영역 (아이콘만 표시) */
QComboBox::drop-down,
QDateTimeEdit::drop-down {
    border: none;
    background: none;
    subcontrol-origin: padding;
    subcontrol-position: top right;
    width: 20px;
}

/* 드롭다운 화살표 아이콘 */
QComboBox::down-arrow,
QDateTimeEdit::down-arrow {
    image: url(:/icons/grayDropDown.svg);
    width: 12px;
    height: 12px;
}

/* 버튼 스타일 */
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

/* 취소 버튼 스타일 */
QPushButton#btnCancel {
    background-color: #dcdde1;
    color: #2f3640;
}

QPushButton#btnCancel:hover {
    background-color: #c8c9cc;
}

/* 캘린더 상단 네비게이션 */
QCalendarWidget QWidget#qt_calendar_navigationbar {
    background-color: #dbeafe;
}

/* 이전/다음 버튼 크기 */
QCalendarWidget QToolButton#qt_calendar_prevmonth,
QCalendarWidget QToolButton#qt_calendar_nextmonth {
    qproperty-iconSize: 12px;
    width: 22px;
    height: 22px;
}

/* 캘린더 버튼 스타일 */
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
}

/* 요일 헤더 */
QCalendarWidget QHeaderView::section {
    color: #718093;
    background-color: white;
    padding: 4px;
    border: none;
}

/* 날짜 영역 */
QCalendarWidget QAbstractItemView {
    border: none;
    outline: none;
    selection-background-color: transparent;
}

/* 날짜 셀 */
QCalendarWidget QAbstractItemView::item {
    border-radius: 6px;
}

/* 선택된 날짜 */
QCalendarWidget QAbstractItemView::item:selected {
    background: transparent;
    color: #000000;
    font: bold;
}

/* 호버 효과 */
QCalendarWidget QAbstractItemView::item:hover {
    background-color: #bcd2ff;
}
)");
}

// 소멸자
ScheduleEditorDialog::~ScheduleEditorDialog() {
    delete ui;
}

// 저장 버튼 클릭 시
void ScheduleEditorDialog::on_btnSave_clicked() {

    // 입력값 가져오기
    QString title = ui->leTitle->text();
    QString content = ui->teContent->toPlainText();
    QString category = ui->cbCategory->currentText();
    QString categoryDetail = ui->leCategoryDetail->text();

    QDateTime startDateTime = ui->deStart->dateTime();
    QDateTime endDateTime = ui->deEnd->dateTime();

    // 제목 필수 체크
    if (title.isEmpty()) {
        QMessageBox::warning(this, "경고", "제목을 입력하세요.");
        return;
    }

    // 카테고리 선택 여부 체크
    if (ui->cbCategory->currentIndex() < 0) {
        QMessageBox::warning(this, "경고", "카테고리를 선택해주세요.");
        return;
    }

    // 시간 유효성 검사
    if (startDateTime > endDateTime) {
        QMessageBox::warning(this, "경고", "종료 시간이 시작 시간보다 빠릅니다.");
        return;
    }

    // Schedule 객체 생성
    Schedule scheduleData(
        title,
        content,
        startDateTime,
        endDateTime,
        category,
        categoryDetail
        );

    // 데이터 저장 및 시그널 발생
    schedule.setData(scheduleData);
    emit scheduleSaved(schedule);

    // 다이얼로그 종료
    accept();
}

// 특정 날짜 설정
void ScheduleEditorDialog::setDate(const QDate &date) {
    ui->deStart->setDate(date);
    ui->deEnd->setDate(date);
}

// 기존 일정 데이터 로드 (수정 모드)
void ScheduleEditorDialog::setSchedule(const Schedule &schedule) {
    this->schedule = schedule;

    ui->leTitle->setText(schedule.getTitle());
    ui->teContent->setText(schedule.getDescription());

    ui->deStart->setDateTime(schedule.getStartTime());
    ui->deEnd->setDateTime(schedule.getEndTime());

    ui->cbCategory->setCurrentText(schedule.getCategory());
    ui->leCategoryDetail->setText(schedule.getCategoryDetail());

    // 수정 시 detail 활성화
    ui->leCategoryDetail->setEnabled(true);
}

// 취소 버튼 클릭 시
void ScheduleEditorDialog::on_btnCancel_clicked() {
    reject();
}
