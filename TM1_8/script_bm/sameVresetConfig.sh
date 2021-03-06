script_BM=../script_bm
temp=$1
version=$2
Vreset=$3
dacParName=dacPar.txt
mkdir ../data/dataBase/temp${temp}_v${version}/Vreset${Vreset}
cd ../data/dataBase/temp${temp}_v${version}/Vreset${Vreset}
echo ${Vreset}  ${Vreset} ${Vreset} ${Vreset} ${Vreset} ${Vreset} ${Vreset} ${Vreset} > ${dacParName}

cd ../../../
cd ${script_BM}
cp  ../data/dataBase/temp${temp}_v${version}/Vreset${Vreset}/${dacParName} ../daq/
cd ../daq

dacPar=dacPar.txt
i=1
j=0
k=2
declare -a array=(0 0 0 0 0 0 0 0)
for ID in $(cat ${dacPar})
do
        NUM=$i
        S_ID=$( awk 'NR='$NUM' {print $'$i'}' ${dacPar} )
        T_ID=$( awk 'NR='$NUM' {print $'$k'}' ${dacPar} )
        array[$j]=${S_ID}
        echo $i "${array[${j}]}"
        #echo ${S_ID}
        #echo ${T_ID}
        : $(( i++ ))
        : $(( j++ ))
        : $(( k++ ))
done
echo ${array[0]} ${array[1]} ${array[2]} ${array[3]} ${array[4]} ${array[5]} ${array[6]} ${array[7]}

cd ../daq
./dacConfigNewBoard.sh  ${array[0]} ${array[1]} ${array[2]} ${array[3]} ${array[4]} ${array[5]} ${array[6]} ${array[7]}
./mytcp -c dacNewBoard.c
########################################################################

cd ${script_BM}
