#include "originalview.h"
#include "ui_originalview.h"

OriginalView::OriginalView(DataAdapter *dataAdapater, QWidget *parent) :
  ViewIf(parent),
  ui(new Ui::OriginalView),
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
}

OriginalView::~OriginalView()
{
  delete ui;
}

void OriginalView::refresh()
{
  for (int index = 0; index < m_monitorsList.size(); index++)
  {
    m_monitorsList.at(index)->refresh();
  }
}
