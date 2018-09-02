///////////////////////////////////////////////////////////////////////////
//                                                                       //
// NOTICE OF COPYRIGHT                                                   //
//                                                                       //
//                Copyright (C) 2013   John Suárez                       //
//                https://github.com/fnoj/BuffonsNeedle                  //
//                                                                       //
// This program is free software; you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation; either version 2 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details:                          //
//                                                                       //
//          http://www.gnu.org/copyleft/gpl.html                         //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#include <RQ_OBJECT.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TGProgressBar.h>
#include <TRandom1.h>
#include <TLine.h>
#include <TGStatusBar.h>
#include <TMath.h>
#include <TTimer.h>
#include <TGClient.h>

class BN{

  RQ_OBJECT("BN");
 
 public:  
  BN(const TGWindow *p,UInt_t w,UInt_t h);
  ~BN();
  void Draw();
  void Run();
  void Clear();
    
 private:

  TGLayoutHints *l1, *l2;  
  TGMainFrame *TMF1;
  TRootEmbeddedCanvas *EC1;
  TCanvas *c1;
  TGVerticalFrame  *VFO1, *VFO2;
  TGHorizontalFrame  *HF1, *HFN, *HFl;
  TGLabel *TGLPI, *TGLN, *TGLl;
  TGNumberEntryField *NEPIvalue;
  TGHProgressBar *PB;
  TRandom1 *r;
  TLine *li, *lr;
  TGNumberEntry *NEN, *NEl;              //NumberEntry Values  Number of Needles and Longitud Value
  TGStatusBar *SB;  
  TGTextButton *TGBDraw, *TGBClear, *TGBExit;
  TGGroupFrame  *GF1, *GF2;              //Group Parameters, Options and Results.
  TTimer *Count;

  Double_t l;
  Double_t Theta;
  Double_t x1,y1,x2,y2;
  Int_t Nc,Nf,Nl,Nt;
  Double_t pi_exp;
  char PI[20];
  char EP[20];
  char CN[20];
  char CNc[20];
  char CNf[20];
  Double_t PBinc;
  Double_t ErrPor;

  ClassDef(BN,0);
};
