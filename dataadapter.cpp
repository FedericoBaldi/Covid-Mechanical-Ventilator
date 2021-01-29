#include "dataadapter.h"

const char * DataAdapter::m_dataNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) name,
  DATANAME_X
  #undef X
};
//PRESENTER it is called "Adapter" because work as a collector of data and provides function to access them.
DataAdapter::DataAdapter(DataHandler *dataHandler, QObject *parent) :
  QObject(parent),
  m_dataHandler(dataHandler)
{
  bool connectionOk = QObject::connect(m_dataHandler, SIGNAL(dataChanged()),
                                       this, SIGNAL(dataChanged()), Qt::QueuedConnection);
  assert(connectionOk);
}

/*!
 * \brief DataAdapter::getData
 * Ask for current data and parse them to return the asked one.
 * \param dataName X_Macro enum that binds data to it.
 * \return description name data.
 */
float DataAdapter::getData(eDataName dataName)
{
  float result = 0;
  bool isFound = false;
  int index = 0;
  QList<QPair<QString, float>> dataList = m_dataHandler->getCurrentData();
  while (index < dataList.size() && !isFound)
  {
    if (dataList.at(index).first == m_dataNameList[dataName])
    {
      result = dataList.at(index).second;
    }
    index++;
  }
  return result;
}


