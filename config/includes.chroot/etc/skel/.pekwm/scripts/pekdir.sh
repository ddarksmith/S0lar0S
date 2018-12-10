#!/bin/sh
# Auteur :      thuban <thuban@yeuxdelibad.net>
# licence :     MIT

# browse directory

HOMEDIR=~/
BROWSE="pcmanfm"

echo "Dynamic {"
for W in $(ls $HOMEDIR); do
	echo "Entry = \"$W\" { Actions = \"Exec $BROWSE $HOMEDIR/$W\" }"
done
echo "}"
exit

