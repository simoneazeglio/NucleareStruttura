//
//  Diffrazione.cpp , Con alimentazione a 30kV
//  
//
//  Created by Simone Azeglio
//  Valori picchi teorici
//  Theta non thetax2
//  Kalfa 1 = 15.84° ; Kalfa 2 = 33.10°  ; Kalfa 3 = 55.00°
//  Kbeta 1 = 14.16° ; Kbeta 2 = 29.30° ;Kbeta 3 = 47.23°;




#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>



// Multi Gaussian function
Double_t MultiGaussianPeaks(Double_t *x, Double_t *par) {
    return (par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0]+
            par[4]*TMath::Exp(-0.5*((x[0]-par[5])*(x[0]-par[5]))/(2*par[6]*par[6]))+
            par[7]*TMath::Exp(-0.5*((x[0]-par[8])*(x[0]-par[8]))/(2*par[9]*par[9]))+
            par[10]*TMath::Exp(-0.5*((x[0]-par[11])*(x[0]-par[11]))/(2*par[12]*par[12]))+
            par[13]*TMath::Exp(-0.5*((x[0]-par[14])*(x[0]-par[14]))/(2*par[15]*par[15]))+
            par[16]*TMath::Exp(-0.5*((x[0]-par[17])*(x[0]-par[17]))/(2*par[18]*par[18])));
}



void Diffrazione(){


    //numero misure
    const int nmisure =   290;
    
    
    // numero misure senza doppi
    const int nmisure2= 145;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[]  = {138, 139, 136, 118, 120, 100, 122, 104, 107, 115,
                         121, 117, 116, 117, 106, 89, 115, 131, 109, 134,
                         116, 136, 124, 117, 139, 131, 137, 133, 136, 134,
        
                         123, 123, 330, 349, 482, 422 , 467, 490, 431, 432,
                         405, 360 , 268, 253, 218, 217, 171, 166, 139, 158,
                         190, 167,  189, 204, 175, 199, 272, 273, 873, 847,
        
                         1511, 1548, 2000, 2090 , 2218, 2053, 2070, 2138, 1737, 1801,
                         1160, 1200, 750, 754, 426, 416, 254, 279, 184, 210,
                         178, 172, 168, 177, 158, 145, 176, 162, 183, 200,
        
                         188, 193, 193,  205, 225, 198, 217, 195, 223, 208,
                         249, 189, 231, 207, 205, 211, 199, 210, 185, 210,
                         226, 231, 256, 292, 279, 290, 310, 326, 285, 284,
        
                         299, 304, 276, 269, 223, 240, 243, 234, 218, 258,
                         216, 228, 187, 212, 229, 217, 219, 204, 200, 230,
                         215, 226, 227, 230, 203, 223, 227, 200, 274, 285,
        
                         375, 345, 526, 463, 645, 622, 674, 694 , 624, 682,
                         640, 614, 626, 604, 555, 517 , 422, 419, 349, 369,
                         292, 280, 253, 229, 237, 254, 236, 245, 234, 252,
        
                         232, 243, 259, 238, 252, 257, 283, 285, 331, 299,
                         347, 349, 394, 375, 365, 391, 406, 392, 394 , 404,
                         403 , 427, 376, 396, 374, 385, 404, 416, 421, 408,
        
                         384, 392, 411,   380, 439, 364, 403, 390, 423, 394,
                         422, 386, 473, 421, 423, 429, 419, 426, 440, 447,
                         395, 449 , 430, 453, 450, 451, 426, 410, 475, 428,
        
                         505, 493, 534, 499, 504, 521, 506, 500, 520, 500,
                         491, 514, 488, 540, 546, 502, 528, 573, 598,  542,
                         568, 556, 588, 568, 598, 609, 585, 566, 597, 586,
        
                         603, 601, 548, 551, 575, 555, 535, 553, 510, 533,
                         500, 532, 494, 506, 548, 570, 543, 577, 619, 613 };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float ThetaX2[]  = {12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
                        17, 17, 18, 18, 19, 19, 20, 20, 21, 21,
                        22, 22, 23, 23, 24, 24, 25, 25, 26, 26,
        
                        27, 27, 28, 28, 28.167, 28.167, 28.33, 28.33, 28.5, 28.5,
                        28.66, 28.66, 28.83, 28.83, 29, 29 , 30 , 30, 30.167, 30.167,
                        30.33, 30.33, 30.5 , 30.5, 30.66, 30.66 ,30.83, 30.83, 31, 31,
        
                        31.167, 31.167, 31.33, 31.33, 31.5, 31.5 , 31.66, 31.66, 31.83, 31.83,
                        32, 32, 32.167, 32.167, 32.33, 32.33, 32.5, 32.5, 32.67, 32.67,
                        32.83, 32.83, 33, 33, 38, 38, 43, 43, 48, 48,
        
                        53, 53, 54, 54, 55, 55, 56, 56, 57, 57,
                        57.5, 57.5, 57.67, 57.67, 57.83, 57.83, 58, 58, 58.167, 58.167,
                        58.33, 58.33, 58.5, 58.5, 58.67, 58.67, 58.83, 58.83, 59, 59,
        
                        59.167, 59.167, 59.33, 59.33, 59.5, 59.5, 59.67, 59.67, 59.83, 59.83,
                        60, 60, 60.167, 60.167, 60.33, 60.33, 60.5, 60.5, 61, 61,
                        63, 63, 65, 65, 65.167, 65.167, 65.33, 65.33, 65.5, 65.5,
        
                        65.67, 65.67, 65.83, 65.83, 66, 66, 66.167, 66.167, 66.33, 66.33,
                        66.5, 66.5, 66.67, 66.67, 66.83, 66.83, 67, 67, 67.167, 67.167,
                        67.33, 67.33, 67.5, 67.5, 67.67, 67.67, 67.83, 67.83, 68, 68,
        
                        68.167, 68.167, 68.33, 68.33, 73, 73, 78, 78,
                        83, 83, 88, 88 , 92, 92, 92.33, 92.33, 92.67, 92.67,
                        92.83, 92.83, 93, 93, 93.167, 93.167, 93.33, 93.33, 93.5, 93.5,
        
                        93.67, 93.67, 93.83, 93.83, 94, 94, 94.167, 94.167, 94.33, 94.33,
                        94.5, 94.5 , 94.67, 94.67, 94.83, 94.83, 95, 95, 95.167, 95.167,
                        95.33, 95.33, 95.5, 95.5, 95.67, 95.67, 95.83, 95.83, 96, 96,
        
                        101, 101, 106, 106, 108, 108, 108.33, 108.33, 108.5, 108.5, 108.67, 108.67,
                        108.83, 108.83, 109, 109, 109.167, 109.167, 109.33, 109.33, 109.5, 109.5,
                        109.67, 109.67, 109.83, 109.83, 110, 110, 110.167, 110.167, 110.33, 110.33,
        
                        110.5, 110.5, 110.67, 110.67, 110.83, 110.83, 111, 111, 111.167, 111.167,
                        111.33, 111.33, 111.5, 111.5, 112, 112, 117, 117, 120, 120};
    
    
    cout << "Misure ThetaX2:  " << sizeof(ThetaX2)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float ThetaX22[nmisure2] ;
    float sThetaX22[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(ThetaX2[i] == ThetaX2[i+1]){
        ThetaX22[j]= ThetaX2[i] ;
        cout << "ThetaX2" << j <<" : "  <<  ThetaX22[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { ThetaX22[j] = ThetaX2[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.01;
        sThetaX22[i] = 0.167;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
        
        
        
        
        //--------------- FIT Dati -------- //
        
        TCanvas *cThetaX2Conteggi = new TCanvas("cThetaX2Conteggi ","Conteggi(ThetaX2)",700,100,800,500);
        
        
    TGraphErrors *gThetaX2Conteggi = new TGraphErrors(nmisure2 , ThetaX22 ,Conteggi_Secondi2 ,sThetaX22, sConteggi_Secondi2);
        
        
        
        
        // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
        // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
        gThetaX2Conteggi->SetMarkerSize(0.6);
        gThetaX2Conteggi->SetMarkerStyle(21);
        gThetaX2Conteggi->SetTitle("Rate(ThetaX2)");
        
        gThetaX2Conteggi->GetXaxis()->SetTitle("ThetaX2[gradi]");
        gThetaX2Conteggi->GetYaxis()->SetTitle("Rate [1/s] ");
        
        
        
        
        gThetaX2Conteggi->Draw("AP");
    
    
    
    //--
    // create a TF1 with the range from 0 to 3 and 6 parameters
    TF1 *fitFcn = new TF1("fitFcn",MultiGaussianPeaks, 12, 120, 19);
    
    
    
    
    // Polynomial's parameters from background fitting
    
    fitFcn->SetParameter( 0,  6.045);//, 72.5);
    fitFcn->SetParameter( 1,   -3.82880e-02 );//, -0.38);
    fitFcn->SetParameter( 2,   2.16988e-03 );//, 0.000913);
    fitFcn->SetParameter( 3,   -9.45735e-07);//, -1.75e-07);
    
    
    
    
    // Setting MG parameters from par[4] to par[21]
    
    
    fitFcn->SetParameter(4, 16.7 ); // Constant - pol evaluated in get position x
    fitFcn->SetParameter(5, 28.33 ); // Mean
    
    fitFcn->SetParameter(7,  98.42 ); // Constant + 7
    fitFcn->SetParameter(8, 31.5 ); // Mean
    
    fitFcn->SetParameter(10, 5.3); // Constant + 10
    fitFcn->SetParameter(11, 58.83 ); // Mean
    
    fitFcn->SetParameter(13, 21.41 ); // Constant + 10
    fitFcn->SetParameter(14, 66.367); // Mean
    
    fitFcn->SetParameter(16, 4.4); // Constant + 25
    fitFcn->SetParameter(17, 110.5 ); // Mean
   
    
   
    
    
    fitFcn->SetParameter(6, 0.25);//, 32.90); // Width - rough order of mag estimate
    fitFcn->SetParameter(9, 0.30);// , 41.44); // Width - rough order of mag estimate
    fitFcn->SetParameter(12 , 0.40);//, 47.27); // Width - rough order of mag estimate
    fitFcn->SetParameter(15 ,  0.32);//, 50.58); // Width - rough order of mag estimate
    fitFcn->SetParameter(18 , 0.25 );//, 65.15); // Width - rough order of mag estimate
    
    
    
    
    
    
    
    
    // first try without starting values for the parameters
    // this defaults to 1 for each param.
    gThetaX2Conteggi->Fit(fitFcn,"R+");
    // histo->Fit("background");
    //histo->Fit("MultiGaussianPeaks");
    
    
    cout << "Chi^2:" << fitFcn->GetChisquare() << ", number of DoF: " << fitFcn->GetNDF() << " (Probability: " << fitFcn->GetProb() << ")." << endl;
    

    
        
        

    
    }
    











