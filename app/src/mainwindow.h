#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QMap>
#include <QPair>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateDateTimeDisplay();
    void updateDayTime();
    void updateWeekTime();
    void onFicharClicked();
    void onExportClicked();

private:
    Ui::MainWindow *ui;
    QTimer *dateTimeUpdateTimer;
    QTimer *dayUpdateTimer;
    QTimer *weekUpdateTimer;

    // Métodos de inicialización
    void initializeUI();
    void setupConnections();
    void setupTimers();

    // Método para exportar entradas de tiempo
    void exportTimeEntries(QFile& exportFile, const QMap<QDate, QList<QTime>>& entriesByDate);
};
#endif // MAINWINDOW_H
