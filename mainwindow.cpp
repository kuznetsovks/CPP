#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "godunov.h"

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

double t=0.;
double tm=0;
bool pla=false;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Riemann R;
    double eps=0.01;
    R.Gamma=ui->gammabox->value();
    double TO=ui->tobox->value();
    double TIN=ui->tinbox->value();
    double DIAPH=ui->diaphbox->value();
    int CELLS=ui->nxbox->value();
    double minL=0;
    double maxL=ui->lmaxbox->value();
    double UL=ui->ulbox->value();
    double PL=ui->plbox->value();
    double DL=ui->rolbox->value();
    double UR=ui->urbox->value();
    double PR=ui->prbox->value();
    double DR=ui->rorbox->value();
    double DX = (maxL-minL)/CELLS;
    int N=CELLS+1;


       R.State(UL,PL,DL,UR,PR,DR);
       if (pla==false)
       {
           tm=TO;
       }

       QVector<double> X(N),S(N),DS(N),US(N),PS(N),U(N);
       for(int i=1;i<N;i++)
       {
           X[i] = (i - DIAPH)*DX;
           S[i]    = (X[i] - DIAPH)/tm;
           R.Sample(R.PM,R.UM,S[i],DS[i],US[i],PS[i]);
           U[i]=PS[i]/DS[i]/R.G8;

       }
           ui->widget->clearGraphs();
           ui->widget_2->clearGraphs();
           ui->widget_3->clearGraphs();
           ui->widget_4->clearGraphs();

           ui->widget->addGraph();
           ui->widget_2->addGraph();
           ui->widget_3->addGraph();
           ui->widget_4->addGraph();

           ui->widget->graph(0)->setData(X, DS);
           ui->widget_2->graph(0)->setData(X, PS);
           ui->widget_3->graph(0)->setData(X, US);
           ui->widget_4->graph(0)->setData(X, U);

           ui->widget->xAxis->setLabel("x");
           ui->widget->yAxis->setLabel("RO");
           ui->widget_2->xAxis->setLabel("x");
           ui->widget_2->yAxis->setLabel("P");
           ui->widget_3->xAxis->setLabel("x");
           ui->widget_3->yAxis->setLabel("V");
           ui->widget_4->xAxis->setLabel("x");
           ui->widget_4->yAxis->setLabel("U");

           ui->widget->xAxis->setRange(minL,maxL);
           ui->widget_2->xAxis->setRange(minL,maxL);
           ui->widget_3->xAxis->setRange(minL,maxL);
           ui->widget_4->xAxis->setRange(minL,maxL);



            double minD = DS[0]-eps, maxD = DS[0];
            for (int i=1; i<N; i++)
              {
                  if (DS[i]<minD) minD = DS[i];
                  if (DS[i]>maxD) maxD = DS[i];
              }
              ui->widget->yAxis->setRange(minD,maxD);

            double minP = PS[0]-eps, maxP = PS[0];
            for (int i=1; i<N; i++)
               {
                   if (PS[i]<minP) minP = PS[i];
                   if (PS[i]>maxP) maxP = PS[i];
               }
              ui->widget_2->yAxis->setRange(minP,maxP);

             double minV = US[0]-eps, maxV = US[0];
             for (int i=1; i<N; i++)
                {
                    if (US[i]<minV) minV = US[i];
                    if (US[i]>maxV) maxV = US[i];
                }
               ui->widget_3->yAxis->setRange(minV,maxV);

              double minU = U[0]-eps, maxU = U[0];
              for (int i=1; i<N; i++)
                {
                    if (U[i]<minU) minU = U[i];
                    if (U[i]>maxU) maxU = U[i];
                }
               ui->widget_4->yAxis->setRange(minU,maxU);


              ui->widget->replot();
              ui->widget_2->replot();
              ui->widget_3->replot();
              ui->widget_4->replot();

}






void MainWindow::on_playbutton_toggled(bool checked)
{
    double TO=ui->tobox->value();
    double TIN=ui->tinbox->value();
    double j=TIN;
    double ch=0;

    if (checked==true)
    {
        t = 0.05;
        pla=true;     


            j=TIN;
            tm=j;
        while ((j<=TO) and (j!=-1)){
            if(t<0){
                if (j<=0.05){
                    j=0;t=0;tm=0;
                  //MainWindow::on_pushButton_clicked();
                }
            }
            ch=j;
        MainWindow::on_pushButton_clicked();
        delay();

        std::cout<<"j="<<j<<std::endl;

        tm=j;

        j=j+t;

        if ((j<0.)or (ch==j))
        {
           j=-1;
        }
        }

        if (j==-1) {
            j=0.;
        }
    }
    if (checked==false)
    {
        pla=false;
        t = 0.;

    }

}

void MainWindow::on_speedbutton_toggled(bool checked)
{

    if (pla==true){
    if (checked==true)
    {
        t = 0.1;
        std::cout<<"t"<<std::endl;
    }
    if (checked==false)
    {
        t = 0.05;
    }
    }
    if (pla==false){
        if (checked==true)
        {
            t = 0.1;
        }
        if (checked==false)
        {
            t = 0.05;
        }
    }
}

void MainWindow::on_reversespeed_toggled(bool checked)
{

    if (pla==true){
    if (checked==true)
    {
        t = -0.05;
        std::cout<<"t"<<std::endl;
    }
    if (checked==false)
    {
        t = 0.05;
    }
    }
    if (pla==false){
        if (checked==true)
        {
            t = -0.05;
        }
        if (checked==false)
        {
            t = 0.05;
        }
    }
}

void MainWindow::on_playbutton_2_clicked()
{
    t=0;
}
