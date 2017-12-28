#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TROOT.h>
#include <TMath.h>
#include <TParameter.h>
#include <TGraph.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TSystem.h>
#include "rootlibX.h"
// #include <io.h>

int main(int argc, char **argv){
//   int pedeSet = atol(argv[1]);
//   int dataSet = atol(argv[2]);
  int pedeSet = 27;
  int dataSet = 136;
  int fm1=366;  //frame num

  //// setup pede
  pd1Pede pede;
  if(pedeSet>=0){
    char pedeFn[200];
    sprintf(pedeFn,"../data2/topmetal1202/20171107/pede%d.txt",pedeSet);
    pede.setup(pedeFn);
   }

  /// setup data
  placData_1 pd1;
  char fn[200];
  sprintf(fn,"../data2/topmetal1202/20171107/out%d.pd1",dataSet);
  pd1.read(fn);
  pd1.print();

  /// setup plots
  plot pt;
  pt.setupCanvas(1,1,800,800); //设置canvas上图片的行数，列数
  pt.setup2D(1,1,72,72,"hist2d"); //Tcanvas中的图的行数，列数，阵列的行数，列数，图的名字
  //pt.setup2DMinMax(1000,1500);

  init_keyboard();
  int ch=0;


  int adc(0);

//   pt.draw2DFrames(748, 756);
  pt.setup2DMinMax(-10,8);

  //for(int fm1=605; fm1<665; fm1+=pt.nCol*pt.nRow){
    
    int nC = pt.nCol*pt.nRow;
    for(int ic=0; ic<nC; ic++){
      if(fm1+ic>=808) break;
      pd1.getFrame(fm1+ic, adc);
      pede.subPede(pd1.frameDat, adc);  //subtract pede 不加第二个参数，会操作所有通道的数据
      //pede.getSignificance(pd1.frameDat, adc); 
      pt.loadData2Hist2D(pd1.frameDat,ic);

      char str[20];
      sprintf(str, "frame %d", fm1+ic);
      pt.h2[ic]->SetTitle(str);
     }
    pt.draw2D();
    pt.c->SaveAs(TString::Format("../data2/topmetal1202/20171107/%d_%d_%d.png", pedeSet,dataSet,fm1));
  // }
  //pt.c->SaveAs("signal_example.png");
  ch=readch();

/// dump numbers from histograms
   ofstream fout(TString::Format("../data2/topmetal1202/20171107/matrixdata_%d_%d_%d.out", pedeSet,dataSet,fm1)); 
   for(int i=0; i<pt.nCol*pt.nRow; i++){
     if(!pt.h2[i]) continue;
     fout << "# frame " << pt.h2[i]->GetTitle() << endl;
     for(int iCol=0; iCol<72; iCol++)
       for(int iRow=0; iRow<72; iRow++){
         fout << iCol << " " << iRow << " " << pt.h2[i]->GetBinContent(iCol+1, iRow+1) << endl;
      }
    }
   fout.close();

//   return;

//   std::vector< std::pair<int, float> > pxIDs;
//   pxIDs.reserve(10);
// 
//   for(int i=0;i<pd1.nFrame();i++){
//     if(i%20==0) cout<<i<<endl;
//   
//     if(kbhit()){
//       ch=readch();
//       break;
//      }
// 
//     pd1.getFrame(i, adc);  // 输入帧数和adc通道数，不加adc通道数这个参数，会获取所有通道的数据
//   
//     if(pedeSet>=0){
//       pt.loadData2Hist2D(pd1.frameDat,0);
//       pede.subPede(pd1.frameDat, adc);  //subtract pede 不加第二个参数，会操作所有通道的数据
//       pt.loadData2Hist2D(pd1.frameDat,1);
//       pede.getSignificance(pd1.frameDat, adc);  //calculate significance
//       pt.loadData2Hist2D(pd1.frameDat,2);
// 
//       pxIDs.clear();
//       pede.getSignalCandidates(pd1.frameDat, adc, pxIDs);
// 
//       if(pxIDs.size()){
//         cout << "Frame "<< i;
//         for(int iv=0; iv<pxIDs.size(); iv++) cout << " -> " << pxIDs[iv].first << "(" << pxIDs[iv].first/(72*72) << "," << pxIDs[iv].first/72 << "," << pxIDs[iv].first%72 << "):" << pxIDs[iv].second;
//         cout << endl;
//      } }
// 
//     pt.draw2D();
// 
// 
// //     pt.draw2DOrder1X8(pd1.frameDat,72,72);  //要画图的数据，阵列的行数，列数
//    }
// 

  //// cleaning
  close_keyboard();
  cout<<"end"<<endl;
  return 0;
}
