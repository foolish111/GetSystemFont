#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QDebug>
#include <QStringList>
#include <QCompleter>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCompleter *completer;
    QStringList dataFileList;
    QString getfileContent();

private slots:
    void setFamily(QString);
    void setFontSize(QString);
    void openFile();
};

#endif // MAINWINDOW_H
