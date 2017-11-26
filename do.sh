#!/bin/sh

echo -----

text=$(python -c 'import tw_handler; tw_handler.getData(1)')
echo Executed tw_handler getData 1
echo "${text}"
echo -----

noun=$(./analysis.out ${text})
echo Executed analysis.out
echo "${noun}"
echo -----

python image_getter.py <<EOF
${noun}
EOF
echo Executed image_getter.py
echo -----

./processing.out
echo Executed processing.out
echo -----

python -c 'import tw_handler; tw_handler.sendImage()'
echo Executed tw_handler sendImage
echo -----
