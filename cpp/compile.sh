#!/bin/bash

FLAGS="--std=c++14 -Wall -lm -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -pthread"

if [ "$1" == debug ]; then
	mode=debug
	FLAGS+=" -D DEBUG -O0 -g"
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
[[ -f build/debug/failure ]] && rm build/debug/failure
[[ -d build/debug/lock ]] && rm -r build/debug/lock
[[ ! -d build/release ]] && mkdir build/release
[[ ! -d build/release/obj ]] && mkdir build/release/obj
[[ ! -d build/release/check ]] && mkdir build/release/check
[[ -f build/release/failure ]] && rm -r build/release/failure
[[ -d build/release/lock ]] && rm -r build/release/lock

cp -r src/ "build/$mode/prec"

echo "Precompiling ..."
./prec.py "build/$mode/prec"
cpp_files=$(cd ./build/$mode/prec; find -name "*.cpp") # later used to detect obsolete obj files

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

# find changed_cpp_files & changed_hpp_files
changed_cpp_files=""
for file in $(cd "build/$mode/prec"; find -type f)
do
	file=${file#./}
	check_file="build/$mode/check/${namehashes["$file"]}"
	# if the check file exists and matches
	if [ -f "$check_file" ] && [ "$(cat "$check_file")" == "${filehashes["$file"]}" ]; then
		# and the file is not a .cpp, which didn't compile last time
		if [[ ! "$file" =~ .cpp ]] || [[ -f build/$mode/obj/${file%.cpp}.o ]]; then
			continue
		fi
	fi

	if [[ "$file" =~ .cpp ]]; then
		changed_cpp_files+=" $file"
	else
		changed_hpp_files+=" $file"
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

		for target in $(sed 's/ //g' <<< "$(echo "$incgrep" | grep "[</\"]$hpp")")
		do
			target=${target%%:*}
			if [[ "$target" =~ .cpp ]]; then
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
fun() {
	while true
	do
		[[ ! -s build/$mode/to_compile ]] && break
		if mkdir build/$mode/lock 2>/dev/null; then
			file="$(head build/$mode/to_compile -n 1)"
			sed '1d' -i "build/$mode/to_compile"
			rm -r build/$mode/lock
		else
			sleep 0.01
			continue
		fi
		outputfile="build/$mode/obj/${file%.cpp}.o"
		echo "[$1] Compiling '$file' ..."
		dir=$(dirname "$outputfile")
		[[ ! -d "$dir" ]] && mkdir -p "$dir"
		rm -f "$outputfile"
		if ! g++ "build/$mode/prec/$file" -c -o "$outputfile" -I "build/$mode/prec/" $FLAGS; then
			echo 'yup' > "build/$mode/failure"
		fi
	done
}

for file in $changed_cpp_files
do
	echo $file >> "build/$mode/to_compile"
done

cores=$(nproc)
for ((i=0;i<$cores;i++)) do
	fun $i &
done

wait

rm -rf "build/$mode/prec"

if [ -f "build/$mode/failure" ]; then
	echo -e "\nCompilation Failure!"
	exit
fi

# removing old .obj-files
for obj in $(cd ./build/$mode/obj; find -name "*.o")
do
	if [[ ! $cpp_files =~ ${obj%.o}.cpp ]]; then
		rm build/$mode/obj/$obj
	fi
done

# linking
echo "Linking ..."
obj_files=$(find -wholename "./build/$mode/obj/*.o")
rm -f arrows
g++ $obj_files -o arrows $FLAGS
