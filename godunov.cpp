#include "godunov.h"
Riemann::Riemann()
{
    Gamma=1.4;
    G1=(Gamma-1)/(2.0*Gamma);
    G2=(Gamma+1)/(2.0*Gamma);
    G3=2.0*Gamma/(Gamma-1);
    G4=2.0/(Gamma-1);
    G5=2.0/(Gamma+1);
    G6=(Gamma-1)/(Gamma+1);
    G7=(Gamma-1)/2.0;
    G8=(Gamma-1);
    CL=sqrt(Gamma*PL/DL);
    CL=sqrt(Gamma*PR/DR);
    PM=0;
    PStart=0;
    MPA=1;
    UStart=0;
    POld=0;
    FL=0;
    FR=0;
    FLD=0;
    FRD=0;
    UM=0;
}
Riemann::~Riemann(){};

void Riemann::State(double& Ul,double& Pl,double& Dl,double& Ur,double& Pr,double& Dr)
{
    DL=Dl;
    UL=Ul;
    PL=Pl;
    DR=Dr;
    UR=Ur;
    PR=Pr;
    CL=sqrt(Gamma*PL/DL);
    CR=sqrt(Gamma*PR/DR);
    if (G4*(CL+CR)<(UR-UL))
    {
        //throw
        //cout<<G4*(CL+CR)<<endl;
        //cout<<(UR-UL)<<endl;
        //cout<<"Vacuum generated"<<endl;
    }
    StartPU(PM,UM,MPA);//Start(US,PS,DS);
}
  /* void Riemann::Start(double& US,double& PS,double& DS)
    {

        double XPOS;
        double S;
        double DX = LEN/CELLS;
        std::ofstream ofs ("black.csv", std::ofstream::out);
        std::ofstream ofs1 ("white.csv", std::ofstream::out);
        for(int i=1;i<CELLS+1;i++)
        {
            XPOS = (i - DIAPH)*DX;
            S    = (XPOS - DIAPH)/TO;

            Sample(PM,UM,S,DS,US,PS);
            //ofs <<XPOS<<endl;
            //ofs1 <<PS/DS/G8<<endl;


            //" ; "<<PS<<" ; "<<DS<<" ; "<<US<<endl;
            //Sample() SAMPLE(PM, UM, S, DS, US, PS)
            //S = (XPOS - DIAPH)/TIMEOUT;
        }
        //ofs <<1<<endl;
       // ofs1 <<0.125<<endl;
       // ofs.close();
       // ofs1.close();
    }*/

   void Riemann::StartPU(double& P,double& U,double& MPA)
    {
        double Change=1;
        //int i=0;
        double TOLPRE = 1e-6;
        FP(PStart);
        POld=PStart;
        double UDiff = UR - UL;
       while (Change>=TOLPRE)
        {
           // i=i++;
            PreFun(FL, FLD, POld, DL, PL, CL);
            PreFun(FR, FRD, POld, DR, PR, CR);
            P = POld - (FL + FR + UDiff)/(FLD + FRD);
            Change = 2.0*std::abs((P - POld)/(P + POld));
            if (P<0)
            {
                P=0.0;
            }
            POld = P;
            U=0.5*(UL+UR+FR-FL);

        }

    }
    void Riemann::PreFun(double& F,double& FD,double& P,double& DK,double& PK,double& CK)
    {
        double PRAT;
        if (P<=PK)
        {//rarefraction wave
            PRAT=P/PK;
            F =  G4*CK*(pow(PRAT,G1) - 1.0);
            FD = (1.0/(DK*CK))*pow(PRAT,(-G2));
        }
        else
        {//shockwave
            double AK = G5/DK;
            double BK = G6*PK;
            double QRT = sqrt(AK/(BK + P));
            F = (P - PK)*QRT;
            FD = (1.0 - 0.5*(P - PK)/(BK + P))*QRT;
        }
    }

    void Riemann::FP(double& PSTART)
    {
        double QUSER = 2.0;
        double CUP = 0.25*(DL + DR)*(CL + CR);
        double PPV = 0.5*(PL + PR) + 0.5*(UL - UR)*CUP;
        PPV = std::max(0.0, PPV);
        double PMIN = std::min(PL, PR);
        double PMAX = std::max(PL, PR);
        double QMAX = PMAX/PMIN;
        double PN=0;

        if((QMAX<=QUSER) and (PMIN<=PPV) and (PPV<=PMAX))
           {
               PN=PPV;

           }
           else
            {
                if (PPV<PMIN)
                {
                    double PQ = pow((PL/PR),G1);
                    double UM = (PQ*UL/CL + UR/CR +G4*(PQ - 1.0))/(PQ/CL + 1.0/CR);
                    double PTL = 1.0 + G7*(UL - UM)/CL;
                    double PTR = 1.0 + G7*(UM - UR)/CR;
                    PN = 0.5*(pow(PL*PTL,G3) + pow(PR*PTR,G3));
                }
                else
                {
                    double GEL=sqrt((G5/DL)/(G6*PL+PPV));
                    double GER=sqrt((G5/DR)/(G6*PR+PPV));
                     PN=(GEL*PL+GER*PR-(UR-UL))/(GER+GEL);
                }
            }
        PSTART=PN;
    }

    void Riemann::Sample(double& PM,double& UM,double& S,double& D,double& U,double& P)
    {
        double SHL,STL,CML,PML,PMR,CMR;
        double SL,SR,SHR,STR;
        double C;
        if (S<=UM)
        {
            if(PM<=PL)
            {//left rarefraction wave
                SHL = UL - CL;
                if (S<=SHL)
                {
                    D = DL;
                    U = UL;
                    P = PL;
                }
                else
                {
                    CML = CL*pow((PM/PL),G1);//
                    STL = UM - CML;

                    if (S>STL)
                    {
                        D = pow(DL*(PM/PL),(1.0/Gamma));
                        U = UM;
                        P = PM;

                    }
                    else
                    {

                        U = G5*(CL + G7*UL + S);
                        C = G5*(CL + G7*(UL - S));
                        D = pow(DL*(C/CL),G4);
                        P = pow(PL*(C/CL),G3);
                    }
                }
            }
            else
            {//left shock wave
                PML = PM/PL;
                SL = UL - CL*sqrt(G2*PML + G1);
                if (S<=SL)
                {
                    D = DL;
                    U = UL;
                    P = PL;
                }
                else
                {
                    D = DL*(PML + G6)/(PML*G6 + 1.0);
                    U = UM;
                    P = PM;
                }
            }
        }
        else
        {
            if (PM>PR)
            {// right shock
                PMR = PM/PR;
                SR = UR + CR*sqrt(G2*PMR + G1);
                if (S>=SR)
                {
                    D = DR;
                    U = UR;
                    P = PR;
                }
                else
                {
                    D = DR*(PMR + G6)/(PMR*G6 + 1.0);
                    U = UM;
                    P = PM;
                }
            }
            else
            {//right rarefractio
                SHR = UR + CR;
                if (S>=SHR)
                {
                    D = DR;
                    U = UR;
                    P = PR;
                }
                else
                {
                    CMR = pow(CR*(PM/PR),G1);
                    STR = UM + CMR;
                    if (S<=STR)
                    {
                        D = pow(DR*(PM/PR),(1.0/Gamma));
                        U = UM;
                        P = PM;
                    }
                    else
                    {
                        U = G5*(-CR + G7*UR + S);
                        C = G5*(CR - G7*(UR - S));
                        D = pow(DR*(C/CR),G4);
                        P = pow(PR*(C/CR),G3);
                    }
                }
            }
        }
    }
