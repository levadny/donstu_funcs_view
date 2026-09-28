#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plotcolors.h"

#include "donstu_funcs/funcline.h"
//#include "donstu_funcs/funcarctan.h"
//#include "donstu_funcs/funcfastosc.h"
//#include "donstu_funcs/funcmodul.h"
//#include "donstu_funcs/funcquartic.h"
#include "donstu_funcs/funcgauss.h"
//#include "donstu_funcs/


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

  // add funcs
  this->m_funcs.push_back(new FuncLine({0.75, 10}));
  //this->m_funcs.push_back(new FuncArctan({50, 2}));
  //this->m_funcs.push_back(new FuncFastOsc({50, 10, 1}));
  //this->m_funcs.push_back(new FuncModul({1.25, 15}));
  //this->m_funcs.push_back(new FuncQuartic({0.0005, 0.008, 3}));
  this->m_funcs.push_back(new FuncGauss({70, -0.005}));

  // create all series
  auto color = chartColors();
  // auto titles = chartTitles();
  for(size_t i = 0; i < this->m_funcs.size(); ++i){

    // create series
    auto ser = this->plot->newSeries();
    ser->setDotColor(color[i]);
    ser->setDotSize(1);
    ser->setLineSize(1);
    //ser->setTitle(titles[i]);
    ser->setVisible(true);

    double x = -100;
    double y = 0;
    while(x < 100){
      y = this->m_funcs[i]->calc(x);
      ser->addPoint({x, y});
      x += 1;
    }
  }

  // меню с сериями


  // part for genetic


}

MainWindow::~MainWindow() {
  delete ui;
}
