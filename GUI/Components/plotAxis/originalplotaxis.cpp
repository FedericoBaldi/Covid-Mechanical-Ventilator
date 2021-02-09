/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2018 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 25.06.18                                             **
**          Version: 2.0.1                                                **
****************************************************************************/

#include "originalplotaxis.h"

const char * OriginalPlotAxis::m_titleNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) showName,
  DATANAME_X
  #undef X
};

OriginalPlotAxis::OriginalPlotAxis(DataAdapter *dataAdapter, eDataName dataName, QColor graphColor, QWidget *parent) :
  QCustomPlot(parent),
  m_dataAdapter(dataAdapter),
  m_dataName(dataName)
{
  axisRect()->axis(QCPAxis::atLeft, 0)->setLabelPadding(5);
  m_Graph = addGraph(xAxis, axisRect()->axis(QCPAxis::atLeft, 0)); // create graph
  m_Graph->setPen(QPen(graphColor));
  QBrush graphBrush;
  graphBrush.setColor(QColor("black"));
  graphBrush.setStyle(Qt::SolidPattern);
  setBackground(graphBrush);

  yAxis->grid()->setVisible(false);
  yAxis->setLabel(m_titleNameList[dataName]);
  yAxis->setLabelColor(QColor(255,228,181));
  yAxis->setSubTicks(true);
  yAxis->setSubTickPen(QPen(QColor(127,114,90)));
  QPen yAxPen(QColor(255,228,181));
  yAxPen.setStyle(Qt::SolidLine);
  yAxis->setBasePen(QPen(QColor(255,228,181)));
  yAxis->setTickPen(QPen(QColor(255,228,181)));
  yAxis->setTickLabelColor(QColor(146,146,146));
  xAxis->setBasePen(QPen(QColor(255,228,181)));
  xAxis->setTicks(false);
  xAxis->setTickLabels(false);
  xAxis->grid()->setVisible(false);

  connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
  mDataTimer.start(200);
}

OriginalPlotAxis::~OriginalPlotAxis()
{
  delete this;
}

void OriginalPlotAxis::timerSlot()
{
  m_Graph->addData(m_Graph->dataCount(), m_dataAdapter->getData(m_dataName)); //add a new data point to the graph and

  xAxis->rescale();
  m_Graph->rescaleValueAxis(false, true); // make key axis range scroll with the data

  xAxis->setRange(xAxis->range().upper, 100, Qt::AlignRight);
  replot();
}