#!/bin/bash

F=
while ! test -f "$F" || ! test -x "$F"; do
    read -p "Dati un fisier executabil: " F
done
