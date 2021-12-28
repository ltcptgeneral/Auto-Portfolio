data="$(
    cat "$1" \
      | sed 's/"/\\"/g' \
      | sed ':a;N;$!ba;s/\n/\\n/g' \
)"

echo $(curl -s --data "{\"text\":\"$data\",\"mode\":\"gfm\"}" 'https://api.github.com/markdown')