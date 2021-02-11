#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string_view>
#include <memory>
#include <Utils/include/command.h>
#include <Utils/include/position.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::string_view m_name{ "window" };

    std::unique_ptr<Ui::MainWindow> m_ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    [[nodiscard]] inline auto &object() const { return *m_ui; }
    [[nodiscard]] inline auto name() const { return m_name; }

    std::string_view do_magic(const Command &cmd) { }

public slots:
    void to_echo_write(const std::string &what);
    void visualize(const Position &what);

signals:
    void command_signal(const std::string);
    void dump(std::string_view);
};

#endif // MAINWINDOW_H
