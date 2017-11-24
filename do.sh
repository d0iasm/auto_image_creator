#!/bin/sh

echo -----

text=$(python text_getter.py)
echo Executed text_getter.py
echo "${text}"
echo -----

noun=$(./analysis.out ${text})
echo Executed analysis.out
echo "${noun}"
echo -----

python image_getter.py <<EOF
"${noun}"
EOF
echo Executed image_getter.py
echo -----

./processing.out
echo Executed processing.out
