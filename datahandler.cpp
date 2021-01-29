#include "datahandler.h"
#include <QFile>
#include <QTextStream>
#include <QPair>

const int DataHandler::TIMER_TIME = 100;
//MODEL
DataHandler::DataHandler():
  m_dataTimer(nullptr)
{

}

QList<QPair<QString, float> > DataHandler::getCurrentData()
{
  return m_dataList;
}

void DataHandler::setupDataHandler()
{
  if (m_dataTimer == nullptr)
  {
    m_dataTimer = new QTimer(this);
  }
  bool connectionOk = QObject::connect(m_dataTimer, SIGNAL(timeout()),
                                       this, SLOT(refreshData_slot()), Qt::QueuedConnection);
  assert(connectionOk);
  m_dataTimer->start(TIMER_TIME);
}

void DataHandler::refreshData_slot()
{
  QFile file("../gui/gui/DataStream.txt");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QTextStream in(&file);
    m_dataList.clear();
    while (!in.atEnd())
    {
      QString line = in.readLine();
      processLine(line);
    }
    file.close();
    emit dataChanged(); //notify that there are new data availables
  }
}

void DataHandler::processLine(QString line)
{
  QStringList lSplit;
  lSplit = line.split(" ");
  m_dataList.append(qMakePair(lSplit.first(), lSplit.at(1).toFloat()));
}
