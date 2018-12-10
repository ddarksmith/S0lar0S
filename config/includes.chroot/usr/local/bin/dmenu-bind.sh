#!/bin/bash
#include personnal bin folder
if [ -e "$HOME/bin" ]; then
	PATH="$HOME/bin:$PATH"
fi
# launch dmenu
exe=`dmenu_run -b -fn "Hack-10" -nb '#090909' -nf '#eeeeee' -sb '#2F5B91' -sf '#F9F9F9' -p 'exec:'` && eval "exec $exe" &
exit 0
