#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Font->setFixedWidth(200);
    ui->FontSize->setFixedWidth(200);
    QStringList fontsize;
    fontsize<<"5"<<"5.5"<<"6.5"<<"7.5"<<"8"<<"9"<<"10"<<"10.5"<<"11"<<"12"<<"14"<<"16"<<"18"<<"20"<<"26"<<"28"<<"56"<<"72";
    ui->FontSize->addItems(fontsize);

    QStringList strings;
    QFontDatabase database;
    foreach (QString family, database.families(QFontDatabase::SimplifiedChinese)) {
        strings.append(family);
    }
    completer = new QCompleter(strings, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    //设置下拉提示popup的样式
    completer->popup()->setStyleSheet("    background-color: #294662;\
                                   color: #ffffff;\
                                   border: 1px solid #375C80;\
                                   border-radius: 5px;\
                                   padding: 0px 0px 0px 0px;\
                                   min-width: 17px;\
                                   font: 14px \"Arial\";");
    ui->Font->addItems(strings);
    ui->Font->setCompleter(completer);
    ui->textEdit->setEnabled(false);
    connect(ui->fontComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setFamily(QString)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openFile()));
    ui->fontComboBox->setWritingSystem(QFontDatabase::SimplifiedChinese);
    connect(ui->FontSize, SIGNAL(currentIndexChanged(QString)), this, SLOT(setFontSize(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFamily(QString family)
{
    QFont font;
    font.setPointSize(ui->FontSize->currentText().toFloat());
    font.setFamily(family);
    ui->textEdit->setFont(font);
}

void MainWindow::setFontSize(QString fontSize)
{
    QFont font;
    font.setFamily(ui->Font->currentText());
    font.setPointSize(fontSize.toFloat());
    ui->textEdit->setFont(font);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName (this,
                       tr("打开文件"), "", tr("文件 (*.txt *.rtf *.doc *.docx *.pdf)"));

    if (!fileName.isNull())
    {
        qDebug()<<fileName;
        dataFileList.append(fileName);
        ui->textEdit->setPlainText(getfileContent());
    }
}

QString MainWindow::getfileContent()
{
    QString string;
    string.clear();
    foreach (QString fileName, dataFileList) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Can't open the file!";
        }
        if (fileName.contains(".txt"))
        {
            qDebug()<<"txt文件";
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString str(line);
                string.append(str);
            }
        }
        else if (fileName.endsWith(".docx"))
            qDebug()<<"docx文件";
        else if (fileName.endsWith(".doc"))
            qDebug()<<"doc文件";
        else if (fileName.endsWith(".pdf"))
            qDebug()<<"pdf文件";
        else
            qDebug()<<"rtf文件";
    }
    return string;
}
