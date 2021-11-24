#!/bin/bash

echo "insert 1 hello" | nc kali 1337
echo "insert 1 hello" | nc kali 1337
echo "insert 2 yes" | nc kali 1337
echo "insert 3 no" | nc kali 1337
echo "concat 1 2" | nc kali 1337
echo "concat 1 3" | nc kali 1337
echo "delete 3" | nc kali 1337
echo "delete 4" | nc kali 1337
echo "concat 1 4" | nc kali 1337
echo "update 1 final" | nc kali 1337
echo "concat 1 2" | nc kali 1337

