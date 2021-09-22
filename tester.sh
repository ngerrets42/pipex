#!/bin/sh

# check bonus
BONUS=0
if [ $1 ]
then
	BONUS=1
fi

normal() {
	echo "\n	COMMAND: < $INFILE $1 | $2 > out.txt"
	echo "		pipex:	" | tr -d '\n'
	./pipex "$INFILE" "$1" "$2" out.txt;
	sleep .1;
	cat -e out.txt;
	rm -f out.txt;
	echo "		shell:	" | tr -d '\n'
	< $INFILE $1 | $2 > out.txt; cat -e out.txt;
	rm -f out.txt;
}

bonus3() {
	echo "\n	COMMAND: < $INFILE $1 | $2 | $3 > out.txt"
	echo "		pipex:	" | tr -d '\n'
	./pipex "$INFILE" "$1" "$2" "$3" out.txt;
	sleep .1;
	cat -e out.txt;
	rm -f out.txt;
	echo "		shell:	" | tr -d '\n'
	< $INFILE $1 | $2 | $3 > out.txt; cat -e out.txt;
	rm -f out.txt;
}

bonus4() {
	echo "\n	COMMAND: < $INFILE $1 | $2 | $3 | $4 > out.txt"
	echo "		pipex:	" | tr -d '\n'
	./pipex "$INFILE" "$1" "$2" "$3" "$4" out.txt;
	sleep .1;
	cat -e out.txt;
	rm -f out.txt;
	echo "		shell:	" | tr -d '\n'
	< $INFILE $1 | $2 | $3 | $4 > out.txt; cat -e out.txt;
	rm -f out.txt;
}

HEREDOC=$(cat <<- EOF
	1 this
	2 is
	3 a
	4 heredoc
	5 END
	END
	EOF
)

heredoc() {
	echo "\n	COMMAND: $1 << END | $2 | $3 > out.txt"
	echo "		pipex:	" | tr -d '\n'
	echo "$HEREDOC" | ./pipex here_doc END "$1" "$2" "$3" out.txt;
	sleep .1;
	cat -e out.txt;
	rm -f out.txt;
	echo "		shell:	" | tr -d '\n'
	($1 <<- END
		1 this
		2 is
		3 a
		4 heredoc
		5 END
		END
	) | $2 | $3 > out.txt; cat -e out.txt;
	rm -f out.txt;
}

argtest() {
	echo "\n	Too few arguments:"
	echo "		1 arg: " | tr -d '\n'
	./pipex cat
	echo "		2 args: " | tr -d '\n'
	./pipex "$INFILE" out.txt;
	echo "		3 args: " | tr -d '\n'
	./pipex "$INFILE" cat out.txt;
	if [ $BONUS = 0 ]
	then
		echo "\n	Too many arguments (if no bonus):"
		echo "		5 args: " | tr -d '\n'
		./pipex "$INFILE" cat cat cat out.txt;
		echo ""
		echo "		6 args: " | tr -d '\n'
		./pipex "$INFILE" cat cat cat cat out.txt;
	fi
}

# Tests

echo "\n====NO BONUS====\n"
INFILE="in.txt"
normal cat "grep 1"
normal cat "wc -l"
normal "wc -l" cat
normal "wc -l" "wc -l" 
echo "ERROR TEST:"
normal "wc -l" non_existant_command
normal "wc -l" ""
argtest

if [ $BONUS = 1 ]
then
	echo "\n=====BONUS =====\n"
	bonus3 "grep a" "wc -l" "cat"
	bonus3 "wc -l" "cat" "wc -l"
	bonus3 "wc -l" "wc -l" 'tr -d "$"'
	bonus4 cat "grep a" "wc -l" "cat"
	bonus4 "wc -l" "grep a" "cat in.txt" "wc -l"
	bonus4 cat cat cat "grep 5"
	echo "HEREDOC:"
	heredoc cat cat "wc -l"
	heredoc "wc -l" cat cat
	heredoc "grep this" "cat" "cat -e"
	echo "ERROR TEST:"
	bonus3 cat non_existant_command "grep 5"
	bonus4 "wc -l" "wc -l" 'tr -d "$"' ""
	heredoc "grep this" "cat" "||||"
	heredoc "wc -l" cat non_existant_command
fi

echo "\n====LARGE FILE TEST====\n"
INFILE="/usr/share/dict/words"
echo "NO BONUS:"
normal "grep A" "wc -l"
if [ $BONUS = 1 ]
then
	echo "BONUS:"
	bonus4 cat "grep a" "grep b" "wc -l"
fi

