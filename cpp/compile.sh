#!/bin/bash

if [ "$1" == debug ]; then
	mode=debug
elif [ "$1" == release ]; then
	mode=release
else
	echo "debug or release?"
	exit 1
fi

[[ ! -d build ]] && mkdir build
[[ ! -d build/prec ]] && mkdir build/prec
[[ ! -d build/prec_buf ]] && mkdir build/prec_buf
[[ ! -d build/debug ]] && mkdir build/debug
[[ ! -d build/release ]] && mkdir build/release

rm -rf build/prec_buf/*
[[ ! -z "$(ls build/prec)" ]] && mv build/prec/* build/prec_buf
cp -r src/* build/prec

# fix prec & prec_buf mismatches:
for file in $(cd build/prec_buf; find -type f -name "*.cpp")
do
	file=${file#./}
	if [ ! -f "build/prec/$file" ]; then
		rm "build/prec_buf/$file"
		rm -f "build/debug/${file%.cpp}.o"
		rm -f "build/release/${file%.cpp}.o"
	fi
done

echo "Calling the Precompiler ..."
./precompiler.py build/prec

tmp_files=$(cd build/prec; find -name "*.cpp" -type f)
for file in $tmp_files
do
	file=${file#./}
	files="$files ${file#"./build/prec/"}"
done

# compilation
for file in $files
do
	outputfile="build/$mode/${file%.cpp}.o"
	if [ ! -f "$outputfile" ]; then # always compile
		buf_sum="-1"
	elif [ -f "build/prec_buf/$file" ]; then
		buf_sum="$(md5sum "build/prec_buf/$file" | cut -d " " -f 1)"
	else
		buf_sum="-1"
	fi
	new_sum="$(md5sum "build/prec/$file" | cut -d " " -f 1)"
	if [ ! "$buf_sum" == "$new_sum" ]; then
		echo "Compiling '$file' ..."
		dir=$(dirname "$outputfile")
		[[ ! -d "$dir" ]] && mkdir -p "$dir"
		g++ "build/prec/$file" -c -o "$outputfile" -I src
	fi
done

# linking
obj_files=$(find -wholename "./build/$mode/*.o")
g++ $obj_files -o arrows -lm -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
