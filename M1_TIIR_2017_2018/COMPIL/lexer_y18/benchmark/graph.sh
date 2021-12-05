file=fibo.js
rm -f 1_lexer 2_lexer 3_lexer
touch 1_lexer 2_lexer 3_lexer
cd 1_lexer_y18 && make && cd ..
cd 2_lexer_y18 && make && cd ..
cd 3_lexer_y18 && make && cd ..
for i in `seq 0 1 45`
do
cat fibo_base.js > fibo.js
echo "fibo de $i"
echo "print(fibo($i));" >> $file


`./tools/jsp $file > $file.parse`
echo -n "$i " >> 1_lexer
echo -n "$i " >> 2_lexer
echo -n "$i " >> 3_lexer
 /usr/bin/time -f "%e" ./1_lexer_y18/build/bin/unserializer "$file.parse" 2>> 1_lexer 1>/dev/null
 /usr/bin/time -f "%e" ./2_lexer_y18/build/bin/unserializer "$file.parse" 2>> 2_lexer 1>/dev/null
 /usr/bin/time -f "%e" ./3_lexer_y18/build/bin/unserializer "$file.parse" 2>> 3_lexer 1>/dev/null
done
exit 0
