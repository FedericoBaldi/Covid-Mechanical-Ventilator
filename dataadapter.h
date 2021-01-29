#ifndef DATAADAPTER_H
#define DATAADAPTER_H

#include <QObject>
#include "datahandler.h"

#define DATANAME_X \
  X(dnPressure             , "pressure",              "PAW",                   "cmH20") \
  X(dnO2                   , "o2",                    "FiO2",                  "%") \
  X(dnFlow                 , "flow",                  "Flow",                  "slpm") \
  X(dnBPM                  , "bpm",                   "Meas. RR",              "bpm") \
  X(dnTidal                , "tidal",                 "VTidal",                "ml") \
  X(dnPeep                 , "peep",                  "PEEP",                  "cmH20") \
  X(dnTemperature          , "temperature",           "Temperature",           "temperature") \
  X(dnBattery_Powered      , "battery_powered",       "Power Source",          "") \
  X(dnBattery_Charge       , "battery_charge",        "Battery",               "%")\
  X(dnPeak                 , "peak",                  "Max Pinsp",             "cmH20") \
  X(dnTotal_Inspired_Volume, "total_inspired_volume", "Vtidal",                "ml") \
  X(dnTotal_Expired_Volume , "total_expired_volume",  "total_expired_volume",  "ml") \
  X(dnVolume_Minute        , "volume_minute",         "Ve",                    "slpm") \

typedef enum
{
  #define X(enumerator, name, showName, measureUnit) enumerator,
    DATANAME_X
  #undef X
  dnMax
}eDataName;

class DataAdapter : public QObject
{
  Q_OBJECT
public:
  explicit DataAdapter(DataHandler *dataHandler, QObject *parent = nullptr);
  float getData(eDataName dataName);
private:
  DataHandler *m_dataHandler;
  static const char * m_dataNameList[];

signals:
  void dataChanged();
};

#endif // DATAADAPTER_H
