#pragma once
#include <QMainWindow>
#include "acana_dotplot/dotplotwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  DotPlotWidget *plot;

  DotPlotSeries<double> *sHyperbola;
  DotPlotSeries<double> *sFastOsc;
};
