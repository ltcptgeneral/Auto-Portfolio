if [ $# != 2 ]
then
	echo "Usage: run-auto-portfolio <spec file> <config file>"
	exit 2
fi

spec=$(cat $1)
config=$(cat $2)

names=()

for line in $spec
do
	readarray -d "," -t array <<<"$line"
	link="$(echo -n ${array[0]})"
	name="$(echo -n ${array[1]}).markdown"
	wget $link -O $name &> /dev/null
	./GFM-to-html.sh $name $name
	names+=("$(echo -n ${array[1]})")
done

for name in $names
do
	echo $name
done