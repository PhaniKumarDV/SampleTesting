
#!/bin/sh
#Decrypt the File with a Key

if [ $# != 2 ]; then
    echo "Invalid Usage..."
    exit 1
fi

KEY=KeyWest
ENC_FILE=$1
DEC_FILE=$2

openssl enc -aes-256-cbc -d -in $ENC_FILE -out $DEC_FILE -pass pass:KeyWest
