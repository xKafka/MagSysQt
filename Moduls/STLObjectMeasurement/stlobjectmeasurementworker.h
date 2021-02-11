#ifndef STLOBJECTMEASUREMENTWORKER_H
#define STLOBJECTMEASUREMENTWORKER_H

#include <QObject>

#include "positionfilereader.h"


class STLObjectMeasurementWorker : public QObject
{
    Q_OBJECT

    struct RunConfig
    {
        std::string samples_per_step{};
        std::string on_position_delay{};
    };

    RunConfig m_config{};

    PositionFileReader m_position_reader{};

    bool m_is_running{ false };

    int m_steps{};

    Position m_printer_position{};

    void load_file(const std::string &args);

    void run(const std::vector<std::string> &args);

    template<typename CmdRecognizer>
    void parse_cmd(const std::vector<std::string> &args, CmdRecognizer recognizer)
    {
        if(args.empty())
            emit dump("{magsys} no such commands allowed");
        else
        {
            recognizer();
        }
    }

public:
    explicit STLObjectMeasurementWorker(QObject *parent = nullptr);

public slots:
    void run_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void load_cmd(const std::vector<std::string> &args);

    void stop_cmd(const std::vector<std::string> &args);

    void printer_on_position(const Position &);

    void new_data_available(const std::vector<std::string> &);

signals:
    void dump(const std::string &);

    void command(const std::string &);
};

#endif // STLOBJECTMEASUREMENTWORKER_H
