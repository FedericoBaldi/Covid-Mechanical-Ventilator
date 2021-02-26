#include "monitor.h"
#include "ui_monitor.h"
#include "QDebug"

const char * Monitor::m_titleNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) showName,
  DATANAME_X
  #undef X
};

const char * Monitor::m_measureUnitNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) measureUnit,
  DATANAME_X
  #undef X
};

Monitor::Monitor(DataAdapter *dataAdapter, eDataName dataName, QWidget *parent) :
  ViewIf(parent),
  ui(new Ui::Monitor),
  m_dataAdapter(dataAdapter),
  m_dataName(dataName)
{
  ui->setupUi(this);
  QString title(m_titleNameList[dataName]);
  if (m_measureUnitNameList[dataName] != "")
  {
    title.append(" [");
    title.append(m_measureUnitNameList[dataName]);
    title.append("]");
  }
  ui->label_name->setText(title);
  ui->display_opts->setCurrentWidget(ui->default_text);
  ui->label_value->setText(QString::number(qRound(m_dataAdapter->getData(m_dataName))));
}

Monitor::~Monitor()
{
  delete ui;
}

void Monitor::refresh()
{
  ui->label_value->setText(QString::number(qRound(m_dataAdapter->getData(m_dataName))));
}
