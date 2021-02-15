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

#include "plotaxis.h"

const char * PlotAxis::m_titleNameList[] =
{
  #define X(enumerator, name, showName, measureUnit) showName,
  DATANAME_X
  #undef X
};

PlotAxis::PlotAxis(DataAdapter *dataAdapter, QList<eDataName> dataNameList, QWidget *parent) :
  QCustomPlot(parent),
  m_dataAdapter(dataAdapter),
  m_dataNameList(dataNameList)
{
  // configure plot to have two right axes:
  yAxis->setTickLabels(false);
  xAxis->setTickLabels(false);
  connect(yAxis2, SIGNAL(rangeChanged(QCPRange)), yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis

  yAxis2->setVisible(true);

  for (int index = 0; index < m_dataNameList.size(); index++)
  {
    axisRect()->addAxis(QCPAxis::atRight);
    axisRect()->axis(QCPAxis::atRight, index)->setLabelPadding(5);
    m_GraphList.append(addGraph(xAxis, axisRect()->axis(QCPAxis::atRight, index))); // create graph
    m_GraphList.at(index)->setPen(QPen(QColor((qrand()%255), (qrand()%255), (qrand()%255))));
    m_TagList.append(new AxisTag(m_GraphList.at(index)->valueAxis())); //create tag with AxisTag class (see axistag.h/.cpp)
    m_TagList.at(index)->setPen(m_GraphList.at(index)->pen());
    axisRect()->axis(QCPAxis::atRight, index)->setLabel(m_titleNameList[dataNameList.at(index)]);
  }
  axisRect()->removeAxis(axisRect()->axis(QCPAxis::atRight, m_dataNameList.size()));
}

PlotAxis::~PlotAxis()
{
  delete this;
}

void PlotAxis::refresh()
{
  for (int index = 0; index < m_dataNameList.size(); index++)
  {
    m_GraphList.at(index)->addData(m_GraphList.at(index)->dataCount(), m_dataAdapter->getData(m_dataNameList.at(index))); //add a new data point to the graph and

    xAxis->rescale();
    m_GraphList.at(index)->rescaleValueAxis(false, true); // make key axis range scroll with the data

    double graphValue = m_GraphList.at(index)->dataMainValue(m_GraphList.at(index)->dataCount()-1); // update the vertical axis tag positions and texts to match the rightmost data point of the graph
    m_TagList.at(index)->updatePosition(graphValue);
    m_TagList.at(index)->setText(QString::number(graphValue, 'f', 1));
  }

  xAxis->setRange(xAxis->range().upper, 100, Qt::AlignRight);
  replot();
}
