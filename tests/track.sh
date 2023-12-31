#!/bin/bash

sh_name="minishell"
usage='\033cPress Ctrl+C to quit'
echo -e "$usage"
while true; do
	pids=`pgrep $sh_name`
	if [ ! -z "$pids" ]; then
		echo -e "$usage"
		for pid in $pids; do
			echo "minishell ($pid): `lsof -p $pid | wc -l`"
			childs=`pgrep -P $pid`
			if [ -z "$childs" ]; then
				echo '  No childs process.'
			else
				echo '  Childs process:'
				for child in $childs; do
					name=`ps -p $child | tail -n 1 | cut -d ' ' -f 7`
					echo "    $name ($child): `lsof -p $child | wc -l`"
				done
			fi
		done
	fi
	sleep 2
done
