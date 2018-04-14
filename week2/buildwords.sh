#!/bin/bash

grep -E "<td>..*</td>" | 
sed '1~2d' | tr [A-Z] [a-z] | 
sed 's/<td>//g' | 
sed 's/<\/td>//g' | 
sed 's/<u>//g' | 
sed 's/<\/u>//g' | 
tr "\`" "'" | 
sed "s/ /\n/g" | 
sed "s/,//g" | 
grep -E "^[pk'mnwlhaeiou]*$" | 
sort -u | 
sed '/^\s*$/d' 