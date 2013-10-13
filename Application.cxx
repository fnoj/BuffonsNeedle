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

#ifndef __CINT__

#ifndef ROOT_TApplication
#include "TApplication.h"
#endif
#include "BN.h"
#endif

#ifdef __CINT__
#include "BN.cxx"
#endif

int Application(){
  BN *App = new BN(gClient->GetRoot(),600,520);
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv){
  TApplication BuffonsNeedleApp("BuffonsNeedleApp", &argc, argv);
  int retVal = Application();
  BuffonsNeedleApp.Run();
  return retVal;
}
#endif

