#include "datahandler.h"
#include <QFile>
#include <QTextStream>
#include <QPair>

const int DataHandler::TIMER_TIME = 200;
//MODEL it is called "handler" because it handles and manipulate raw data. It acquires them and does a first elaboratio of them.
DataHandler::DataHandler():
  m_dataTimer(nullptr)
{

}

QList<QPair<QString, float> > DataHandler::getCurrentData()
{
  return m_dataList;
}

/*!
 * \brief DataHandler::setupDataHandler
 * Creates a timer and setup signal-slot connection to refresh data everytime the timer ends.
 */
void DataHandler::setupDataHandler()
{
  if (m_dataTimer == nullptr)
  {
    m_dataTimer = new QTimer(this);
  }
  m_dataTimer->setSingleShot(true);
  bool connectionOk = QObject::connect(m_dataTimer, SIGNAL(timeout()),
                                       this, SLOT(refreshData_slot()), Qt::QueuedConnection);
  assert(connectionOk);
  m_dataTimer->start(TIMER_TIME);
}

/*!
 * \brief DataHandler::refreshData_slot
 * Reads the data stream file and process it, line by line. At the end notify higher levels that the data have changed.
 */
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
  m_dataTimer->start(TIMER_TIME);
}

/*!
 * \brief DataHandler::processLine
 * Receive a line and simply split names and values. Does a first float conversion.
 * \param line QString input line
 */
void DataHandler::processLine(QString line)
{
  QStringList lSplit;
  lSplit = line.split(" ");
  m_dataList.append(qMakePair(lSplit.first(), lSplit.at(1).toFloat()));
}
