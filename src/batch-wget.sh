file=$(cat $1)
for line in $file
do
	readarray -d "," -t array <<<"$line"
	link="$(echo -n ${array[0]})"
	name="$(echo -n ${array[1]}).markdown"
	wget $link -O $name &> /dev/null
done