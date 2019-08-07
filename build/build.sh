./Build/Premake/premake5 gmake2
if [ "$#" -eq  "0" ]
then
	make
else
	make config="$1"
fi