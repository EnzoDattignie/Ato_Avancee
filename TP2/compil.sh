InputDir="./Precompil"
OutputDir="./exe"

for file in $(ls $InputDir) ;do
    filename="${file%.*}"
    for i in $(seq 0 5); do
        gcc -O$i $InputDir"/"$file -lm -o $OutputDir"/"$filename"O"$i".out" 
    done
done