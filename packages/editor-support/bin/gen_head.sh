#! /bin/zsh
CURRENT_DIR=`dirname $0`
cd $CURRENT_DIR
./flatc -o ../reader -c ../CreatorReader.fbs