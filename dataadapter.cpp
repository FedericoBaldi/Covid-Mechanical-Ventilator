#include "dataadapter.h"

const char * DataAdapter::m_dataNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) name,
  DATANAME_X
  #undef X
};
//PRESENTER
DataAdapter::DataAdapter(DataHandler *dataHandler, QObject *parent) :
  QObject(parent),
  m_dataHandler(dataHandler)
{
  bool connectionOk = QObject::connect(m_dataHandler, SIGNAL(dataChanged()),
                                       this, SIGNAL(dataChanged()), Qt::QueuedConnection);
  assert(connectionOk);
}

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


