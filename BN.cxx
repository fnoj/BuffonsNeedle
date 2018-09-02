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

#include "BN.h"
#include "TApplication.h"
#include "TBenchmark.h"

#include <iostream>
using namespace std;

BN::BN(const TGWindow *p,UInt_t w,UInt_t h){
  
  l1 = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY ,2,2,2,2);
  l2 = new TGLayoutHints(kLHintsCenterX | kLHintsCenterY ,2,2,2,2);
  
  TMF1 = new TGMainFrame(p,h,w);
  TMF1 -> SetWMSize(w,h);
  TMF1->SetWindowName("Buffon's Needle");
  TMF1->SetWMSizeHints(w,h,w,h,1,1);
  
  HF1 = new TGHorizontalFrame(TMF1,2,2);
  
  //Group Frames Left______________________________________________________
  VFO1 = new TGVerticalFrame(HF1,2,2);
  
  GF1 = new TGGroupFrame(VFO1,"Parameters",kVerticalFrame);

  HFN = new TGHorizontalFrame(GF1);
  TGLN = new TGLabel(HFN,"N");
  NEN = new TGNumberEntry(HFN,100);
  NEN->SetNumStyle(TGNumberFormat::kNESInteger); 
  NEN->SetNumAttr(TGNumberFormat::kNEANonNegative); 
  NEN->SetLimits(TGNumberFormat::kNELLimitMin,10,10000);
  HFN->AddFrame(TGLN,l2);
  HFN->AddFrame(NEN,l2);

  HFl = new TGHorizontalFrame(GF1);
  TGLl = new TGLabel(HFl,"l");
  NEl = new TGNumberEntry(HFl,1.0);
  NEl->SetNumAttr(TGNumberFormat::kNEANonNegative); 
  NEl->SetLimits(TGNumberFormat::kNELLimitMinMax ,1.0,5.0);
  HFl->AddFrame(TGLl,l2);
  HFl->AddFrame(NEl,l2);

  GF1->AddFrame(HFN,l1);
  GF1->AddFrame(HFl,l1);
  
  //Options__________________________________________________
  GF2 = new TGGroupFrame(VFO1,"Options",kVerticalFrame);
  TGBDraw = new TGTextButton(GF2,"&Draw",1);
  TGBDraw->Connect("Clicked()","BN",this,"Draw()");
  
  TGBClear = new TGTextButton(GF2,"&Clear",3);
  TGBClear->Connect("Clicked()","BN",this,"Clear()");
  
  GF2->AddFrame(TGBDraw,l1);
  GF2->AddFrame(TGBClear,l1);
   
  TGBExit = new TGTextButton(VFO1,"&Exit","gApplication->Terminate(0)");
  
  VFO1->AddFrame(GF1, new TGLayoutHints(kLHintsTop | kLHintsCenterX));
  VFO1->AddFrame(GF2, new TGLayoutHints(kLHintsTop | kLHintsCenterX));
  VFO1->AddFrame(TGBExit, new TGLayoutHints(kLHintsBottom | kLHintsCenterX,3,3,3,3));  
 
  // Canvas Right___________________________________________________________
  VFO2 = new TGVerticalFrame(HF1,2,2,2,2);
  
  TRootEmbeddedCanvas *EC1 = new TRootEmbeddedCanvas("EC1",VFO2,450,450);   
  c1 = EC1->GetCanvas();
  c1->Range(0,0,21,21);
    
  PB = new TGHProgressBar(VFO2,TGProgressBar::kFancy, 450);
  PB->SetFillType(TGProgressBar::kBlockFill);
    
  VFO2->AddFrame(EC1,new TGLayoutHints(kLHintsNormal,1,1,1,1));
  VFO2->AddFrame(PB,new TGLayoutHints(kLHintsNormal,1,1,1,1));
  
  HF1->AddFrame(VFO1,new TGLayoutHints(kLHintsExpandY,10,10,10,10));
  HF1->AddFrame(VFO2,new TGLayoutHints(kLHintsNormal,10,10,10,10));
  
  SB = new TGStatusBar(TMF1);
  SB->SetParts(5);

  TMF1->AddFrame(HF1);
  TMF1->AddFrame(SB,new TGLayoutHints(kLHintsExpandX,1,1,1,1));
  
  Count = new TTimer(10);
  Count->Connect("Timeout()","BN",this,"Run()");

  Nc=0; Nf=0; Nl=0; Nt=0;

  TMF1->MapSubwindows();
  TMF1->Resize(TMF1->GetDefaultSize());
  TMF1->MapWindow();
}

void BN::Draw(){
  c1->Clear();
  PB->Reset();
  Nl=0;
  Nc=0;
  Nf=0;

  r = new TRandom1();
  r->SetSeed(0);

  l=NEl->GetNumber();
  Nt=NEN->GetNumber();
  
  PBinc=100./Nt;

  for(Int_t k=0;k<=24;k=k+l){
    lr = new TLine(k,-3,k,24);
    lr->Draw();
  }

  c1->Update();
  NEl->SetState(false); 
  NEN->SetState(false);
  TGBDraw->SetEnabled(false);
  TGBClear->SetEnabled(false);
  BN::Run();
}


void BN::Run(){
  Count->TurnOn();
  Nl++;
  
  x1= r->Uniform(20);
  y1= r->Uniform(20);
  Theta= r->Uniform(180);
  x2=(l*TMath::Cos(Theta*TMath::Pi()/180))+x1;
  y2=(l*TMath::Sin(Theta*TMath::Pi()/180))+y1;
  
  li = new TLine(x1,y1,x2,y2);
  li->Draw();
  
  for(Int_t j=0;j<=25;j=j+l){ //Cross Needle?
    if((li->GetX1()<=j && li->GetX2()>=j) || (li->GetX1()>=j && li->GetX2()<=j) ){Nc++;}
  }
  Nf=Nt-Nc;

  PB->Increment(PBinc);
  sprintf(CN,"N: %i ",Nl);
  SB->SetText(CN,1);
  sprintf(CNc,"Nc: %i ",Nc);
  SB->SetText(CNc,2);
  sprintf(CNf,"Nf: %i ",Nf);
  SB->SetText(CNf,3);
  
  c1->Update();
  
  pi_exp = (2*(double)Nl)/(double)Nc;
  sprintf(PI,"PI: %f ",pi_exp);
  SB->SetText(PI,0);

  ErrPor = TMath::Abs((pi_exp - TMath::Pi())/TMath::Pi())*100;

  sprintf(EP,"EP: %.2f ",ErrPor);
  SB->SetText(EP,4);

  if(Nl==Nt){Count->TurnOff(); NEl->SetState(true); NEN->SetState(true); TGBClear->SetEnabled(true); TGBDraw->SetEnabled(true);} 

  c1->Update();
}

void BN::Clear(){
  c1->Clear();
  c1->Update();
  PB->Reset();
  Nl=0;
}

BN::~BN(){
  TMF1->Cleanup();
  delete TMF1;
}
