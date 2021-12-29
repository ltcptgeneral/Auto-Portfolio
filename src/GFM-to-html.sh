if [ $# != 2 ]
then
	echo "Usage: GFM-to-html <markdown file> <html file>"
	exit 2
fi
data="$(
	cat "$1" \
		| sed 's/"/\\"/g' \
		| sed ':a;N;$!ba;s/\n/\\n/g' \
)"

echo -ne $(curl -s --data "{\"text\":\"$data\",\"mode\":\"gfm\"}" 'https://api.github.com/markdown') > $2