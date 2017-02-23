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
[[ ! -d build/debug/check ]] && mkdir build/debug/check
[[ ! -d build/release ]] && mkdir build/release
[[ ! -d build/release/obj ]] && mkdir build/release/obj
[[ ! -d build/release/check ]] && mkdir build/release/check

cp -r src/ "build/$mode/prec"

echo "Precompiling ..."
./prec.py "build/$mode/prec"

echo "Determining Changes ..."
# create namehashes, filehashes
declare -A namehashes
declare -A filehashes

for file in $(cd "build/$mode/prec"; find -type f)
do
	file="${file#./}"
	namehashes[$file]="$(md5sum <<< "$file" | cut -d " " -f 1)"
	filehashes[$file]="$(md5sum "build/$mode/prec/$file" | cut -d " " -f 1)"
done

# rm obsolete checks
checks=$(ls "build/$mode/check")
for file in $(cd "build/$mode/prec"; find -type f)
do
	file=${file#./}
	if [[ "$checks" =~ "${namehashes["$file"]}" ]]; then
		checks="$(sed "s/${namehashes["$file"]}//g" <<< "$checks")"
	fi
done

for check in $checks
do
	if [ -z "$check" ]; then
		die "-z check :/"
	fi
	rm "build/$mode/check/$check"
done

# rm obsolete objs
for obj in $(cd "build/$mode/obj"; find -type f)
do
	obj="${obj#./}"
	if [ -n "$obj" ] && [ ! -f "build/$mode/prec/${obj%.o}.cpp" ]; then
		rm "build/$mode/obj/$obj"
	fi
done

# find changed_cpp_files & changed_hpp_files
changed_cpp_files=""
for file in $(cd "build/$mode/prec"; find -type f)
do
	file=${file#./}
	check_file="build/$mode/check/${namehashes["$file"]}"
	if [ ! -f "$check_file" ] || [ ! "$(cat "$check_file")" == "${filehashes["$file"]}" ]; then
		if [[ "$file" =~ *.cpp ]]; then
			changed_cpp_files+=" $file"
		else
			changed_hpp_files+=" $file"
		fi
	fi
done

# update check
rm -rf "build/$mode/check"/*

for file in $(cd "build/$mode/prec"; find -type f)
do
	file="${file#./}"
        echo "${filehashes["$file"]}" > "build/$mode/check/${namehashes["$file"]}"
done

# add cpp files, which depend on changed header-files to changed_cpp
checked_headers=""
incgrep="$(sed 's/	//g' <<< "$(sed 's/ //g' <<< "$(cd "build/$mode/prec"; grep "#include" -r --with-filename)")")"

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

rm -rf "build/$mode/prec"

# linking
echo "Linking ..."
obj_files=$(find -wholename "./build/$mode/obj/*.o")
rm -f arrows
g++ $obj_files -o arrows $FLAGS
