#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QPair>
#include <QMessageBox>
#include <QDateTime>
#include <algorithm>
#include <QDir>
#include <QStandardPaths>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/AppIcon.png"));
    initializeUI();
    setupConnections();
    setupTimers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeUI()
{
    ui->dateSelector->setDate(QDate::currentDate());
    ui->dateSelector->setCalendarPopup(true);

    ui->timeEdit->setTime(QTime::currentTime());
    ui->timeEdit->setDisplayFormat("HH:mm");
}

void MainWindow::setupConnections()
{
    connect(ui->ficharButton, &QPushButton::clicked, this, &MainWindow::onFicharClicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportClicked);
}

void MainWindow::setupTimers()
{
    dateTimeUpdateTimer = new QTimer(this);
    connect(dateTimeUpdateTimer, &QTimer::timeout, this, &MainWindow::updateDateTimeDisplay);
    dateTimeUpdateTimer->start(1000);

    dayUpdateTimer = new QTimer(this);
    connect(dayUpdateTimer, &QTimer::timeout, this, &MainWindow::updateDayTime);
    dayUpdateTimer->start(1000);

    weekUpdateTimer = new QTimer(this);
    connect(weekUpdateTimer, &QTimer::timeout, this, &MainWindow::updateWeekTime);
    weekUpdateTimer->start(1000);
}

void MainWindow::updateDateTimeDisplay()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    if (!ui->timeEdit->hasFocus() && !ui->dateSelector->hasFocus()) {
        ui->timeEdit->setTime(currentTime);
        ui->dateSelector->setDate(currentDate);
    }
}

struct FilePath {
    QString dirPath;
    QString filePath;
};

FilePath getDataFilePath(const QDate& date) {
    QString rootPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString yearStr = date.toString("yyyy");
    QString monthStr = date.toString("MM");
    QString dirPath = rootPath + "/data/" + yearStr;
    QString filePath = dirPath + "/" + monthStr + ".csv";

    return {dirPath, filePath};
}

bool ensureDirectoryExists(const QString& dirPath) {
    QDir dir(dirPath);
    if (!dir.exists()) {
        return dir.mkpath(".");
    }
    return true;
}

void MainWindow::onFicharClicked()
{
    QDate selectedDate = ui->dateSelector->date();
    QTime time = ui->timeEdit->time();
    QDateTime entryDateTime(selectedDate, time);

    FilePath paths = getDataFilePath(selectedDate);

    if (!ensureDirectoryExists(paths.dirPath)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el directorio de datos");
        return;
    }

    QFile file(paths.filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream out(&file);
    out << entryDateTime.toString("yyyy-MM-dd HH:mm") << "\n";
    file.close();

    updateDayTime();
    updateWeekTime();
}

qint64 calculateWorkTime(const QList<QDateTime>& entries, bool includeCurrentTime = false) {
    qint64 totalSeconds = 0;

    for (int i = 0; i < entries.size(); i += 2) {
        if (i + 1 >= entries.size()) break;
        totalSeconds += entries[i].secsTo(entries[i + 1]);
    }

    if (includeCurrentTime && entries.size() % 2 == 1) {
        totalSeconds += entries.last().secsTo(QDateTime::currentDateTime());
    }

    return totalSeconds;
}

QString formatTimeHHMM(qint64 seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    return QString("%1:%2")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'));
}

QList<QDateTime> loadEntriesFromFile(const QString& filePath, const QDate& startDate, const QDate& endDate) {
    QList<QDateTime> entries;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return entries;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QDateTime entry = QDateTime::fromString(line, "yyyy-MM-dd HH:mm");
        if (entry.isValid() && entry.date() >= startDate && entry.date() <= endDate) {
            entries.append(entry);
        }
    }
    file.close();

    return entries;
}

void MainWindow::updateDayTime()
{
    QDate today = QDate::currentDate();
    FilePath paths = getDataFilePath(today);

    QList<QDateTime> todayEntries = loadEntriesFromFile(paths.filePath, today, today);

    if (todayEntries.isEmpty()) {
        ui->dayLabel->setText("00:00");
        return;
    }

    std::sort(todayEntries.begin(), todayEntries.end());
    qint64 totalSeconds = calculateWorkTime(todayEntries, true);

    ui->dayLabel->setText(formatTimeHHMM(totalSeconds));
}

void MainWindow::updateWeekTime()
{
    QDate currentDate = QDate::currentDate();
    QDate startOfWeek = currentDate.addDays(-(currentDate.dayOfWeek() - 1)); // Moonday as first day
    QDate endOfWeek = startOfWeek.addDays(6); // Sunday as last day

    QList<QDateTime> weekEntries;

    QSet<QPair<int, int>> monthsNeeded;
    QDate checkDate = startOfWeek;
    while (checkDate <= endOfWeek) {
        monthsNeeded.insert({checkDate.year(), checkDate.month()});
        checkDate = checkDate.addDays(1);
    }

    for (const auto& yearMonth : monthsNeeded) {
        QDate tempDate(yearMonth.first, yearMonth.second, 1);
        FilePath paths = getDataFilePath(tempDate);

        QList<QDateTime> entries = loadEntriesFromFile(paths.filePath, startOfWeek, endOfWeek);
        weekEntries.append(entries);
    }

    if (weekEntries.isEmpty()) {
        ui->weekLabel->setText("00:00");
        return;
    }

    std::sort(weekEntries.begin(), weekEntries.end());

    QMap<QDate, QList<QDateTime>> entriesByDay;
    for (const QDateTime &entry : weekEntries) {
        entriesByDay[entry.date()].append(entry);
    }

    qint64 totalSeconds = 0;
    for (auto it = entriesByDay.begin(); it != entriesByDay.end(); ++it) {
        QList<QDateTime> dayEntries = it.value();
        qint64 daySeconds = calculateWorkTime(dayEntries, it.key() == QDate::currentDate());
        totalSeconds += daySeconds;
    }

    ui->weekLabel->setText(formatTimeHHMM(totalSeconds));
}

void MainWindow::onExportClicked()
{
    QDate selectedDate = ui->dateSelector->date();
    QString rootPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString yearStr = selectedDate.toString("yyyy");
    QString monthStr = selectedDate.toString("MM");
    QString exportDirPath = rootPath + "/export/" + yearStr;
    QString exportFileName = exportDirPath + "/" + monthStr + ".txt";

    FilePath dataPath = getDataFilePath(selectedDate);

    if (!ensureDirectoryExists(exportDirPath)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el directorio de exportación");
        return;
    }

    QFile inputFile(dataPath.filePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No hay datos para exportar en el mes seleccionado");
        return;
    }

    QMap<QDate, QList<QTime>> entriesByDate;
    QTextStream in(&inputFile);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QDateTime dt = QDateTime::fromString(line, "yyyy-MM-dd HH:mm");
        if (dt.isValid()) {
            entriesByDate[dt.date()].append(dt.time());
        }
    }
    inputFile.close();

    QFile exportFile(exportFileName);
    if (!exportFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el archivo de exportación");
        return;
    }

    exportTimeEntries(exportFile, entriesByDate);
    exportFile.close();

    // QMessageBox::information(this, "Exportación",
    //                          "Datos exportados correctamente a:\n" + exportFileName);
}

void MainWindow::exportTimeEntries(QFile& exportFile, const QMap<QDate, QList<QTime>>& entriesByDate)
{
    QTextStream out(&exportFile);

    int maxPairs = 0;
    for (auto it = entriesByDate.begin(); it != entriesByDate.end(); ++it) {
        int pairs = (it.value().size() + 1) / 2;  // Rounding up
        maxPairs = qMax(maxPairs, pairs);
    }

    out << "Día\tTotal";
    for (int i = 1; i <= maxPairs; i++) {
        out << "\tEntrada " << i << "\tSalida " << i;
    }
    out << "\n";

    for (auto it = entriesByDate.begin(); it != entriesByDate.end(); ++it) {
        QDate date = it.key();
        QList<QTime> times = it.value();
        std::sort(times.begin(), times.end());

        qint64 totalSeconds = 0;
        QList<QPair<QTime, QTime>> pairs;

        for (int i = 0; i < times.size(); i += 2) {
            if (i + 1 >= times.size()) break;
            QTime start = times[i];
            QTime end = times[i + 1];
            totalSeconds += start.secsTo(end);
            pairs.append(qMakePair(start, end));
        }

        QTime lastEntryTime;
        bool hasUnpairedEntry = false;
        if (times.size() % 2 != 0) {
            lastEntryTime = times.last();
            QTime currentTime = QTime::currentTime();
            totalSeconds += lastEntryTime.secsTo(currentTime);
            hasUnpairedEntry = true;
        }

        QStringList lineParts;
        lineParts << date.toString("dd") << formatTimeHHMM(totalSeconds);

        for (const auto &pair : pairs) {
            lineParts << pair.first.toString("HH:mm") << pair.second.toString("HH:mm");
        }

        if (hasUnpairedEntry) {
            lineParts << lastEntryTime.toString("HH:mm") << "-";
        }

        while (lineParts.size() < 2 + maxPairs * 2) {
            lineParts << "";
        }

        out << lineParts.join('\t') << "\n";
    }
}
