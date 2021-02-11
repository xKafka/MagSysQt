#ifndef STLOBJECTMEASUREMENT_H
#define STLOBJECTMEASUREMENT_H

#include <QWidget>
#include <QThread>

#include <Utils/include/command.h>

#include "stlobjectmeasurementworker.h"

class STLObjectMeasurement : public QWidget
{
    Q_OBJECT

    QThread m_thread{};
    STLObjectMeasurementWorker *m_worker{};

    std::string m_name{ "magsys" };

public:
    STLObjectMeasurement();
    ~STLObjectMeasurement() noexcept override;

    [[nodiscard]] inline auto name() const { return m_name; }

    [[nodiscard]] inline auto *worker() const { return m_worker; }

    bool do_magic(const Command &cmd);

    void run_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void load_cmd(const std::vector<std::string> &args);

    void stop_cmd(const std::vector<std::string> &args);

};

#endif // STLOBJECTMEASUREMENT_H
