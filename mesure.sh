echo "./mesure.sh N AimedDir Output Extension"

Extension=out
Dir=./TP1
Output=./TP1_2/res.txt
N=0
if [ $# -gt 0 ]
then
N=$1
if [ $# -gt 1 ]
then
Dir=$2
if [ $# -gt 2 ]
then
Output=$3
if [ $# -gt 3 ]
then
Extension=$4
fi
fi
fi
fi

for file in $(ls $Dir) ;do
    if [ "${file##*.}" = "$Extension" ]; then
        Files+=($file)
        Out+=($file)
    fi
done

touch temp.txt
firstline="Script"

for ((n=1;n <= N;n++)); do
firstline=$firstline";Temps $n (s)"
compteur=0
for script in ${Files[@]}; do
    echo "Execution de $Dir/$script"
    /usr/bin/time -o temp.txt $Dir/$script
    save=$( grep -oE "[0-9]*\.[0-9]*user" temp.txt | grep -oE "[0-9]*\.[0-9]*" )
    Out[$compteur]=${Out[$compteur]}";"$save
    compteur=$((compteur+1))
done
done

echo $firstline > $Output
for line in ${Out[@]};
do
echo $line >> $Output
done
cat $Output
rm temp.txt