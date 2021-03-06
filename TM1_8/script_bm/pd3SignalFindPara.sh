###When signal is on, find the maximum value of pixel ###
script_BM=../script_bm
cd ../daq
fileNum=0
runData=../data/runData/beam

if [ -f "${runData}_${fileNum}.pd1" ]
then
rm ${runData}_${fileNum}.pd1
echo delete========== ${runData}_${fileNum}.pd1
fi



while [ ! -f "${runData}_${fileNum}.pd1" ]; 
do
	echo "${runData}_${fileNum}.pd1 don't exist!"
	./readDdrContinue.ce -out ${runData}
done 

cd ${script_BM}
./pd1Topd3.sh ${fileNum} 

  
  
dataFile=../data/runData/placData3_beam_${fileNum}.pd3  
cppPath=../topmetal1X8

upLimitPixel=$1


root -L  -l -q  "${cppPath}/pd3_signalFindPara.cpp++(\"${dataFile}\",${upLimitPixel})" 
