#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "donstu_funcs/funcfastosc.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // create plot
  this->plot = new DotPlotWidget(ui->wPlots);

  // update and setup main plot
  this->plot->setPlotBgcolor(Qt::white);
  this->plot->setPlotRange({-100, -100}, {100, 100});
  this->plot->showPlot(true);
  this->plot->showAxis(true);
  this->plot->setAxisColor(Qt::black);
  this->plot->setAxisSize(2);
  this->plot->setAxisXTitle("x-axis");
  this->plot->setAxisYTitle("y-axis");
  this->plot->setGridColor(Qt::gray);
  this->plot->setGridMode(GridMode::gmStep);
  this->plot->setGridOXStep(5);
  this->plot->setGridOYStep(5);
  this->plot->showGrid(true);



  // series for hyperbola
  this->sFastOsc = new DotPlotSeries<double>("FastOsc", Qt::blue, 1, true);
  FuncFastOsc f1({60, 2});
  double x = -100;
  while(x < 100){
    double y = f1.calc(x);
    this->sFastOsc->addPoint({x, y});
    x += 1;
  }

  this->plot->newSeries(*(this->sFastOsc));

}

MainWindow::~MainWindow() {
  delete ui;
}
