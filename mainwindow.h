#pragma once
#include <QMainWindow>
#include <QListWidgetItem>

#include <vector>


#include "acana_dotplot/dotplotwidget.h"
#include "donstu_funcs/functemplate.h"

#include "simple_genetic/simplegenetic.h"

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

  void setupCheckboxList(QWidget *parentWidget);

private slots:
  void on_pbGeneticStep_clicked();

private:
  Ui::MainWindow *ui;
  DotPlotWidget *plot;

  // collect of funcs
  std::vector<FuncTemplate<double>*> m_funcs;
  // collect of koefs of funcs
  std::vector<std::vector<double>> m_koefs;

  // count of series
  static size_t const kSeriesCount = 30;
};
