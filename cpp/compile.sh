#!/bin/bash

usage="compile.sh:\tcompile [debug|release]\n\tlock [debug|release]\n\tunlock [debug|release]"

# build/$1/buf/<files> > build/$1/buf.zip
call_lock() {
	[[ -f "build/$1/buf.zip" ]] && rm "build/$1/buf.zip"
	[[ ! -d "build/$1/buf" ]] && mkdir "build/$1/buf"
	zip "build/$1/buf.zip" -0 -r "build/$1/buf" >/dev/null
	rm -r "build/$1/buf"
}

# build/$1/buf.zip > build/$1/buf/<files>
call_unlock() {
	[[ -d "build/$1/buf" ]] && rm -r "build/$1/buf"
	if [[ -f "build/$1/buf.zip" ]]; then
		unzip "build/$1/buf.zip" >/dev/null
		rm "build/$1/buf.zip"
	else
		mkdir "build/$1/buf"
	fi
}

call_compile() {
	trap "{ echo 'locking'; call_lock "$1"; exit 1; }" INT
	[[ ! -d build ]] && mkdir build

	if ! mkdir "build/lock" 2>/dev/null; then
		echo 'Reinitializing build ...'
		rm -rf "build"
		call_compile $*
		return
	fi

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

	[[ ! -d build/debug ]] && mkdir build/debug
	[[ ! -d build/debug/obj ]] && mkdir build/debug/obj
	[[ -f build/debug/failure ]] && rm build/debug/failure
	[[ -f build/debug/to_compile ]] && rm build/debug/to_compile
	[[ ! -d build/release ]] && mkdir build/release
	[[ ! -d build/release/obj ]] && mkdir build/release/obj
	[[ -f build/release/failure ]] && rm build/release/failure
	[[ -f build/release/to_compile ]] && rm build/release/to_compile

	cp -r src/ "build/$mode/prec"

	echo "Precompiling ..."
	./prec.py "build/$mode/prec"

	echo 'Determining Changes ...'
	call_unlock "$mode"

	files_1="$(cd "build/$mode/buf"; find -type f)"
	files_2="$(cd "build/$mode/prec"; find -type f)"
	files_1_new=""
	files_2_new=""

	for file in $files_1
	do
		files_1_new+=" ${file#./}"
	done

	for file in $files_2
	do
		files_2_new+=" ${file#./}"
	done

	files="$(echo ${files_1_new} ${files_2_new} | sed 's/ /\n/g' | sort | uniq)"
	changed_files=""

	for file in $files
	do
		in_prec="false"
		in_buf="false"
		prec_file="build/$mode/prec/$file"
		buf_file="build/$mode/buf/$file"
		[[ -f "$prec_file" ]] && in_prec="true"
		[[ -f "$buf_file" ]] && in_buf="true"

		add="false"

		if [[ "$file" =~ .cpp ]] && [[ "$in_prec" == "true" ]] && [[ ! -f "build/$mode/obj/${file%.cpp}.o" ]]; then
			add="true"
		fi

		if [[ "$in_prec" == "true" ]] && [[ "$in_buf" == "true" ]]; then
			# if they differ
			if ! cmp --silent "$prec_file" "$buf_file"; then
				add="true"
			fi
		fi

		if [[ "$in_prec" == "true" ]] && [[ "$in_buf" == "false" ]]; then
			add="true"
		fi

		if [[ "$file" =~ .cpp ]] && [[ "$in_prec" == "false" ]] && [[ "$in_buf" == "true" ]]; then
			if [[ "$file" =~ .cpp ]]; then
				rm build/$mode/obj/${file%.cpp}.o
			fi
		fi

		if [[ "$in_prec" == "false" ]] && [[ "$in_buf" == "false" ]]; then
			echo 'should not happen'
			exit 1
		fi

		if [[ "$add" == "true" ]]; then
			changed_files+=" $file"
		fi
	done

	rm -r "build/$mode/buf"
	mv "build/$mode/prec" "build/$mode/buf"

	changed_cpp_files=""
	changed_hpp_files=""
	for file in $changed_files
	do
		if [[ "$file" =~ .cpp ]]; then
			changed_cpp_files+=" $file"
		else
			changed_hpp_files+=" $file"
		fi
	done

	# add cpp files, which depend on changed header-files to change
	checked_headers=""
	incgrep="$(sed 's/      //g' <<< "$(sed 's/ //g' <<< "$(cd "build/$mode/buf"; grep "#include" -r --with-filename)")")"

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
			if ! g++ "build/$mode/buf/$file" -c -o "$outputfile" -I "build/$mode/buf/" $FLAGS; then
				echo 'yup' > "build/$mode/failure"
			fi
		done
	}

	changed_cpp_files=${changed_cpp_files##*( )}
	changed_cpp_files=${changed_cpp_files%%( )*}

	if [[ ! -z $changed_cpp_files ]]; then
		echo 'Compiling ...'

		echo $changed_cpp_files | sed 's/ /\n/g' | sort > "build/$mode/to_compile"
		cores=$(nproc)
		for ((i=0;i<$cores;i++)) do
			fun $i &
		done

		wait
	fi

	call_lock "$mode"

	if [ -f "build/$mode/failure" ]; then
		echo -e "\nCompilation Failure!"
		rm -r "build/lock"
		exit
	fi

	if [[ ! -z $changed_cpp_files ]]; then
		# linking
		echo "Linking ..."
		obj_files=$(find -wholename "./build/$mode/obj/*.o")
		rm -f arrows
		g++ $obj_files -o arrows $FLAGS
	fi

	rm -r "build/lock"
}

if [ -z "$1" ]; then
	echo -e "$usage"
	exit 1
fi

if [ "$1" == "compile" ]; then
	call_compile "$2" || call_lock "$2"
elif [ "$1" == "lock" ]; then
	call_lock "$2"
elif [ "$1" == "unlock" ]; then
	call_unlock "$2"
else
	echo -e "$usage"
	exit 1
fi
