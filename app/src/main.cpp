#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QTimeEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QDir>

static QString dataDirectory()
{
    // 1) Si defines FICHAJE_DATA_DIR en el entorno, lo usamos:
    if (const char* env = std::getenv("FICHAJE_DATA_DIR")) {
        return QString::fromLocal8Bit(env);
    }
    // 2) En macOS o Windows, la ruta local de Google Drive
#ifdef Q_OS_MACOS
    return QDir::homePath() + "/Google Drive/Fichaje";
#elif defined(Q_OS_WIN)
    return QDir::homePath() + "/Google Drive/Fichaje";
#else
    // Fallback: mismo AppData
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
