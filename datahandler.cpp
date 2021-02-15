#include "datahandler.h"
#include <QFile>
#include <QTextStream>
#include <QPair>

const int DataHandler::TIMER_TIME = 180;
//MODEL it is called "handler" because it handles and manipulate raw data. It acquires them and does a first elaboratio of them.
DataHandler::DataHandler():
  m_dataTimer(nullptr)
{

}

QList<QPair<QString, float>> DataHandler::getCurrentData()
{
  m_dataMutex.lock();
  return m_dataList;
}

void DataHandler::unlockCurrentData()
{
  m_dataMutex.unlock();
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
    QList<QPair<QString, float>> dataList;
    while (!in.atEnd())
    {
      bool isFound = false;
      int index = 0;
      QPair<QString, float> processedLine = processLine(in.readLine());
      while (index < dataList.size() && !isFound)
      {
        if (dataList.at(index).first == processedLine.first)
        {
          dataList.replace(index, processedLine);
          isFound = true;
        }
        index++;
      }
      if (!isFound)
      {
        dataList.append(processedLine);
      }
    }
    file.close();
    m_dataMutex.lock();
    m_dataList = dataList;
    m_dataMutex.unlock();
    emit dataChanged(); //notify that there are new data availables
  }
  m_dataTimer->start(TIMER_TIME);
}

/*!
 * \brief DataHandler::processLine
 * Receive a line and simply split names and values. Does a first float conversion.
 * \param line QString input line
 */
QPair<QString, float> DataHandler::processLine(QString line)
{
  QStringList lSplit;
  lSplit = line.split(" ");
  QPair<QString, float> processedLine;
  if (lSplit.size() == 2) //protection for DataStream file misalignment
  {
    return qMakePair(lSplit.first(), lSplit.at(1).toFloat());
  }
  return processedLine;
}
