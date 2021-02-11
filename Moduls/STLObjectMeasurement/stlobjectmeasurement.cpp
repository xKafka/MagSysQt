#include "stlobjectmeasurement.h"

STLObjectMeasurement::STLObjectMeasurement()
  :   m_thread(this),
      m_worker(new STLObjectMeasurementWorker)
{
     worker()->moveToThread(&m_thread);

     connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

     m_thread.start();
}

STLObjectMeasurement::~STLObjectMeasurement()
{
  m_thread.wait();
  m_thread.quit();
}

bool STLObjectMeasurement::do_magic(const Command &cmd)
{
  for(const auto &key : cmd.keys)
  {
      if(key == "--load")
      {
          load_cmd(cmd.args);

          return true;
      }

      if(key == "--run")
      {
          run_cmd(cmd.args);

          return true;
      }

      if(key == "--show")
      {
          show_cmd(cmd.args);

          return true;
      }

      if(key == "--stop")
      {
          show_cmd(cmd.args);

          return true;
      }

      return false;
  }

  return false;
}

void STLObjectMeasurement::show_cmd(const std::vector<std::string> &args)
{
  QMetaObject::invokeMethod(m_worker, "show_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void STLObjectMeasurement::run_cmd(const std::vector<std::string> &args)
{
  QMetaObject::invokeMethod(m_worker, "run_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void STLObjectMeasurement::load_cmd(const std::vector<std::string> &args)
{
  QMetaObject::invokeMethod(m_worker, "load_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void STLObjectMeasurement::stop_cmd(const std::vector<std::string> &args)
{
  QMetaObject::invokeMethod(m_worker, "stop_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}


