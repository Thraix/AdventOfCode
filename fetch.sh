#/bin/sh

if [ ! -e cookies.txt ]; then
    echo "No cookies.txt file exists"
    exit 1
fi

list=$(find -name "Day*.cpp" | awk -F '/' '{print $3 "/" $4}' | awk -F '.' '{print $1}' | sed 's/Day//g' | sort)
echo $list

for item in $list; do
    echo $item
    year=$(echo $item | awk -F '/' '{print $1}')
    day=$(echo $item | awk -F '/' '{print $2}')
    echo "year: $year"
    echo "day: $day"
    dir="res/$year/day$day/input.txt"
    echo $dir
    if [ ! -e $dir ]; then
        webitem=$(echo $day | sed 's/^0//g')
        echo "Fetching $dir"
        mkdir -p "res/$year/day$day/"
        touch "res/$year/day$day/test_input.txt"
        curl -s --cookie cookies.txt https://adventofcode.com/$year/day/$webitem/input >$dir
    fi
    exit
done
