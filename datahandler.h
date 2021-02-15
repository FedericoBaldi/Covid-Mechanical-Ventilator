#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <QObject>
#include <QTimer>
#include <QMutex>

class DataHandler : public QObject
{
  Q_OBJECT
public:
  DataHandler();
  QList<QPair<QString, float>> getCurrentData();
  void unlockCurrentData();

private:
  QTimer *m_dataTimer;
  QList<QPair<QString, float>> m_dataList;
  QPair<QString, float> processLine(QString line);
  QMutex m_dataMutex;
  static const int TIMER_TIME;

signals:
  void dataChanged();
  void newData(QList<QPair<QString, float>> dataList);

public slots:
  void setupDataHandler();
  void refreshData_slot();
};

#endif // DATAHANDLER_H
