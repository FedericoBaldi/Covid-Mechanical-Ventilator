#include "initializer.h"
#include "GUI/Components/originalview.h"
#include "GUI/Components/alternativeview.h"
#include "GUI/Components/alternativeview2.h"
#include "mainwindow.h"
#include "GUI/Components/monitor.h"

Initializer::Initializer(QObject *parent) : QObject(parent)
{
  m_viewList.clear();
}

Initializer::~Initializer()
{
  m_handlerThread.quit();
}

/*!
 * \brief Initializer::start
 * Create a thread in a safe mode (signal-slot start) where DataHandler is running.
 * Populate a QList of VierewIf objectes input to the MainWindow.
 */
void Initializer::start()
{
  m_dataHandler = new DataHandler();
  m_dataHandler->moveToThread(&m_handlerThread);
  m_handlerThread.start();
  bool connectionOK = QObject::connect(this, SIGNAL(dataHandlerSetUp_signal()),
                                       m_dataHandler, SLOT(setupDataHandler()), Qt::AutoConnection);
  assert(connectionOK);

  m_dataAdapater = new DataAdapter(m_dataHandler);
  emit dataHandlerSetUp_signal();

  m_viewList.append(new OriginalView(m_dataAdapater));
  m_viewList.append(new AlternativeView(m_dataAdapater));
  m_viewList.append(new AlternativeView2(m_dataAdapater));
  m_mainWindow = new MainWindow(m_dataAdapater, m_viewList);
  m_mainWindow->show();
}
