#include <Moduls/MainWindow/Include/mainwindow.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(std::make_unique<Ui::MainWindow>())
{
    m_ui->setupUi(this);

    connect(m_ui->lineEdit_cmd_line, &QLineEdit::returnPressed, this, [&]()
    {
        auto &cmd_line = *m_ui->lineEdit_cmd_line;

        emit command_signal(cmd_line.text().toStdString());

        cmd_line.clear();
    });

}

void MainWindow::to_echo_write(const std::string &what)
{
    m_ui->plainTextEdit_echo->appendPlainText(what.data());
}

void MainWindow::visualize(const Position &what)
{
    m_ui->widget->visualize(what);
}

MainWindow::~MainWindow()
{
}
