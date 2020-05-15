#pragma once
#include <fstream>
#include <cmath>
#include <iostream>
#include <exception>
class Riemann{
public:
    double Gamma,G1,G2,G3,G4,G5,G6,G7,G8;
    double DL,UL,PL,CL,DR,UR,PR,CR;
    double PM,PStart,POld,UStart,MPA,UM;
    double X,T;
    double FL,FR,FLD,FRD;
   // double PS,DS,US;

    Riemann();
    ~Riemann();
    void State(double& Ul,double& Pl,double& Dl,double& Ur,double& Pr,double& Dr);
    void Start(double& US,double& PS,double& DS);
    void StartPU(double& P,double& U,double& MPA);
    void PreFun(double& F,double& FD,double& P,double& DK,double& PK,double& CK);
    void FP(double& PSTART);
    void Sample(double& PM,double& UM,double& S,double& D,double& U,double& P);
};



