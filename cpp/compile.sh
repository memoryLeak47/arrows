#!/bin/bash

FLAGS="--std=c++14 -Wall -lm -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window"

if [ "$1" == debug ]; then
	mode=debug
	FLAGS+=" -D DEBUG"
elif [ "$1" == release ]; then
	mode=release
	FLAGS+=" -O3"
else
	echo "debug or release?"
	exit 1
fi

[[ ! -d build ]] && mkdir build
[[ ! -d build/debug ]] && mkdir build/debug
[[ ! -d build/debug/obj ]] && mkdir build/debug/obj
[[ ! -d build/debug/prec ]] && mkdir build/debug/prec
[[ ! -d build/debug/prec_buf ]] && mkdir build/debug/prec_buf
[[ ! -d build/release ]] && mkdir build/release
[[ ! -d build/release/obj ]] && mkdir build/release/obj
[[ ! -d build/release/prec ]] && mkdir build/release/prec
[[ ! -d build/release/prec_buf ]] && mkdir build/release/prec_buf

rm -rf "build/$mode/prec_buf"/*
[[ ! -z "$(ls "build/$mode/prec")" ]] && mv "build/$mode/prec"/* "build/$mode/prec_buf"
cp -r src/* "build/$mode/prec"

# fix prec & prec_buf mismatches:
for file in $(cd "build/$mode/prec_buf"; find -type f -name "*.cpp")
do
	file=${file#./}
	if [ ! -f "build/$mode/prec/$file" ]; then
		rm "build/$mode/prec_buf/$file"
		rm -f "build/$mode/obj/${file%.cpp}.o"
	fi
done

echo "Precompiling ..."
./precompiler.py "build/$mode/prec"

tmp_files=$(cd "build/$mode/prec"; find -name "*.cpp" -type f)
for file in $tmp_files
do
	file=${file#./}
	files="$files ${file#"./build/$mode/prec/"}"
done

# compilation
for file in $files
do
	outputfile="build/$mode/obj/${file%.cpp}.o"
	if [ ! -f "$outputfile" ]; then # always compile
		buf_sum="-1"
	elif [ -f "build/$mode/prec_buf/$file" ]; then
		buf_sum="$(md5sum "build/$mode/prec_buf/$file" | cut -d " " -f 1)"
	else
		buf_sum="-1"
	fi
	new_sum="$(md5sum "build/$mode/prec/$file" | cut -d " " -f 1)"
	if [ ! "$buf_sum" == "$new_sum" ]; then
		echo "Compiling '$file' ..."
		dir=$(dirname "$outputfile")
		[[ ! -d "$dir" ]] && mkdir -p "$dir"
		rm "$outputfile"
		g++ "build/$mode/prec/$file" -c -o "$outputfile" -I "build/$mode/prec/" $FLAGS
	fi
done

# linking
echo "Linking ..."
obj_files=$(find -wholename "./build/$mode/obj/*.o")
rm arrows
g++ $obj_files -o arrows $FLAGS
