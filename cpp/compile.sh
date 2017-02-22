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
		rm -f "build/$mode/prec_buf/$file"
		rm -f "build/$mode/obj/${file%.cpp}.o"
	fi
done

echo "Precompiling ..."
./prec.py "build/$mode/prec"

echo "Determining Changes ..."
# find changed_cpp_files
changed_cpp_files=""
for x in $(cd "build/$mode/prec"; find -type f -name "*.cpp")
do
	x=${x#./}
	if [[ ! -f "build/$mode/prec_buf/$x" ]] || [[ ! $(md5sum "build/$mode/prec/$x" | cut -d " " -f 1) == $(md5sum "build/$mode/prec_buf/$x" | cut -d " " -f 1) ]]; then
		changed_cpp_files+=" $x"
	fi
done

# find changed_header_files
changed_hpp_files=""
for x in $(cd "build/$mode/prec"; find -type f -not -name "*.cpp")
do
	x=${x#./}
	if [[ ! -f "build/$mode/prec_buf/$x" ]] || [[ ! $(md5sum "build/$mode/prec/$x" | cut -d " " -f 1) == $(md5sum "build/$mode/prec_buf/$x" | cut -d " " -f 1) ]]; then
		changed_hpp_files+=" $x"
	fi
done

# add cpp files, which depend on changed header-files to changed_cpp
checked_headers=""
incgrep="$(sed 's/	//g' <<< "$(sed 's/ //g' <<< "$(cd build/$mode/prec; grep "#include" -r --with-filename)")")"

unchecked_headers="$changed_hpp_files"
while true
do
	new_unchecked_headers=""
	for hpp in $unchecked_headers
	do
		hpp=${hpp##*/}

		# XXX if "Controller" is ment, also "PlayerController" will trigger

		for target in $(sed 's/ //g' <<< "$(echo "$incgrep" | grep "$hpp")")
		do
			target=${target%%:*}
			if [[ $target =~ .*".cpp" ]]; then
				if [[ ! $changed_cpp_files =~ $target ]]; then
					changed_cpp_files+=" $target"
				fi
			elif [[ ! $checked_headers =~ $target ]] && [[ ! $new_unchecked_headers =~ $target ]] && [[ ! $unchecked_headers =~ $target ]]; then
				new_unchecked_headers+=" $target"
			fi
		done
	done
	if [ -z "$new_unchecked_headers" ]; then
		break
	fi
	checked_headers+=" $unchecked_headers"
	unchecked_headers="$new_unchecked_headers"
done

# compilation
for file in $changed_cpp_files
do
	outputfile="build/$mode/obj/${file%.cpp}.o"
	echo "Compiling '$file' ..."
	dir=$(dirname "$outputfile")
	[[ ! -d "$dir" ]] && mkdir -p "$dir"
	rm -f "$outputfile"
	g++ "build/$mode/prec/$file" -c -o "$outputfile" -I "build/$mode/prec/" $FLAGS
done

# linking
echo "Linking ..."
obj_files=$(find -wholename "./build/$mode/obj/*.o")
rm -f arrows
g++ $obj_files -o arrows $FLAGS
