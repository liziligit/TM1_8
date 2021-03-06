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
#include "rootlib.h"
// #include <io.h>

int main(int argc, char **argv){
	int pedeSet;
	pedeSet = atol(argv[1]);
	int dataSet;
	dataSet = atol(argv[2]);
pd1Pede pede;
char pedeFn[200];
if(pedeSet>=0){
sprintf(pedeFn,"../data/pedeData/pede%d.txt",pedeSet);
pede.setup(pedeFn);
}

placData_1 pd1;
char fn[200];
sprintf(fn,"../data/out%d.pd1",dataSet);
pd1.read(fn);
pd1.print();


plot pt;
pt.setupCanvas(8,2); //设置canvas上图片的行数，列数
pt.setup2D(8,1,72,72,"hist2d"); //Tcanvas中的图的行数，列数，阵列的行数，列数，图的名字
//pt.setup2DMinMax(1000,1500);

init_keyboard();
int ch=0;
float *sssum;
for(int i=0;i<100;i++){
//if(i%20==0)cout<<i<<endl;

if(kbhit()){
ch=readch();
break;
}

pd1.getFrame(i,0);  // 输入帧数和adc通道数，不加adc通道数这个参数，会获取所有通道的数据

if(pedeSet>=0){
pede.subPede(pd1.frameDat,0);  //subtract pede 不加第二个参数，会操作所有通道的数据
sssum+=pd1.frameDat;
sssum++;
}
}

pt.draw2DOrder1X8(sssum/100,72,72);  //要画图的数据，阵列的行数，列数
//}


close_keyboard();

cout<<"end"<<endl;

	return 0;
}
