#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plotcolors.h"

#include "donstu_funcs/funcline.h"
//#include "donstu_funcs/funcarctan.h"
//#include "donstu_funcs/funcfastosc.h"
//#include "donstu_funcs/funcmodul.h"
//#include "donstu_funcs/funcquartic.h"
//#include "donstu_funcs/funcgauss.h"

#include "donstu_funcs/funcdamped.h"

#include <typeinfo.h>


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
  //this->m_funcs.push_back(new FuncLine({0.75, 10}));
  //this->m_funcs.push_back(new FuncArctan({50, 2}));
  //this->m_funcs.push_back(new FuncFastOsc({50, 10, 1}));
  //this->m_funcs.push_back(new FuncModul({1.25, 15}));
  //this->m_funcs.push_back(new FuncQuartic({0.0005, 0.008, 3}));
  //this->m_funcs.push_back(new FuncGauss({70, -0.005}));
  this->m_funcs.push_back(new FuncDamped({0.01, 500}));

  // create all series
  auto color = chartColors();
  // auto titles = chartTitles();
  for(size_t i = 0; i < this->m_funcs.size(); ++i){

    // create series
    auto ser = this->plot->newSeries();
    ser->setDotColor(color[i]);
    ser->setDotSize(1);
    ser->setLineSize(1);
    // tricks :)
    ser->setTitle(typeid(*(this->m_funcs[i])).name());
    ser->setVisible(false);

    double x = -100;
    double y = 0;
    while(x < 100){
      y = this->m_funcs[i]->calc(x);
      ser->addPoint({static_cast<double>(x), y});
      x += 1;
    }
  }

  // меню с сериями


  // part for genetic

  // create list with funcs for checkboxes list
  this->setupCheckboxList(ui->gbFuncs);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pbGeneticStep_clicked() {
  /*&
    GeneticOptimizer::Config cfg;
    cfg.dim         = 3;
    cfg.popSize     = 80;
    cfg.generations = 150;
    cfg.lowerBound  = {500.0, 5.0, 1.0};   // обороты, зазор, скорость
    cfg.upperBound  = {1200.0, 25.0, 8.0};
    cfg.minimize    = true;                // ищем минимум потерь

    GeneticOptimizer ga(cfg);

    // Пришли экспериментальные данные (X, Y)
    ga.addSample({600, 10, 2}, 3.5);
    ga.addSample({700, 12, 3}, 2.1);
    ga.addSample({800, 15, 4}, 1.4);
    ga.addSample({900, 18, 5}, 0.9);
    ga.addSample({1000, 20, 6}, 1.7);
    ga.addSample({1100, 22, 7}, 3.2);
    // ... сколько угодно точек

    auto result = ga.run();
    if (result.valid) {
      std::cout << "Лучшая точка X = [";
      for (double v : result.bestX) std::cout << v << " ";
      std::cout << "]\n";
      std::cout << "Ожидаемый Y = " << result.bestY << "\n";
    }
    return 0;
  }
  */
}

void MainWindow::setupCheckboxList(QWidget *parentWidget) {
  QVBoxLayout *layout = new QVBoxLayout(parentWidget);
  // create list of functions dynamically
  QListWidget *checkList = new QListWidget(parentWidget);
  layout->addWidget(checkList);

  // 2. Добавляем элементы с чекбоксами
  auto series = this->plot->allSeries();
  for (int i = 0; i < this->plot->allSeries().size(); ++i) {
    QListWidgetItem *item = new QListWidgetItem(QString(series[i]->getTitle()).arg(i), checkList);
    // add checkbox state
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    // without checking state
    item->setCheckState(Qt::Unchecked);
  }

  // change visible
  QObject::connect(checkList, &QListWidget::itemChanged, parentWidget, [this, checkList](QListWidgetItem *item) {
    if (!item) return;
    // index of selected element
    int index = checkList->row(item);
    // get all series
    auto tmp = this->plot->allSeries();
    // current state of checkbox
    if (item->checkState() == Qt::Checked) {
      // to switch off
      tmp[index]->setVisible(false);
    } else {
      // to switch on
      tmp[index]->setVisible(true);
    }
  });
}
