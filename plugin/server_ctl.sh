#!/bin/bash

ROOT_PATH=$(pwd)
conf=${ROOT_PATH}/conf/server.conf 
ser=$ROOT_PATH/udp_server

ip=$(grep -E "^IP:" ${conf} | awk -F: '{print $NF}')
port=$(grep -E "^PORT:" ${conf} | awk -F: '{print $NF}')
#$ser $ip $port


if
fi
