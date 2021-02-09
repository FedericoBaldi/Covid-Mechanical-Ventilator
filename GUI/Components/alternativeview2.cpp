#include "alternativeview2.h"
#include "ui_alternativeview2.h"

AlternativeView2::AlternativeView2(DataAdapter *dataAdapater, QWidget *parent) :
  ViewIf(parent),
  ui(new Ui::AlternativeView2),
  m_dataAdapter(dataAdapater)
{
  ui->setupUi(this);

  m_monitorsList.append(new Monitor(m_dataAdapter, dnBattery_Charge));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnBattery_Powered));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnBPM));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnPeak));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnPeep));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnTotal_Inspired_Volume));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnVolume_Minute));
  ui->monitors_slots->addWidget(m_monitorsList.last());
  m_monitorsList.append(new Monitor(m_dataAdapter, dnO2));
  ui->monitors_slots->addWidget(m_monitorsList.last());

  QList<eDataName> dataNameList;
  dataNameList.append(dnPressure);
  ui->graphLayout->addWidget(new PlotAxis(m_dataAdapter, dataNameList));

  dataNameList.clear();
  dataNameList.append(dnTidal);
  ui->graphLayout->addWidget(new PlotAxis(m_dataAdapter, dataNameList));

  dataNameList.clear();
  dataNameList.append(dnFlow);
  ui->graphLayout->addWidget(new PlotAxis(m_dataAdapter, dataNameList));
}

AlternativeView2::~AlternativeView2()
{
  delete ui;
}

void AlternativeView2::refresh()
{
  for (int index = 0; index < m_monitorsList.size(); index++)
  {
    m_monitorsList.at(index)->refresh();
  }
}
