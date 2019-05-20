
#!/bin/sh
#Encrypt the file with a Key

if [ $# != 2 ]; then
    echo "Invalid Usage..."
    exit 1
fi

KEY=KeyWest
ORIG_FILE=$1
ENC_FILE=$2

openssl enc -aes-256-cbc -salt -in $ORIG_FILE -out $ENC_FILE -pass pass:$KEY
