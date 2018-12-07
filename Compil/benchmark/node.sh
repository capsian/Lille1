file=fibo2.js
rm -f 4_nodejs
touch 4_nodejs
for i in `seq 0 1 40`
do
cat fibo_base.js > fibo2.js
echo "fibo de $i"
echo "console.log(fibo($i));" >> $file

echo -n "$i " >> 4_nodejs
 /usr/bin/time -f "%e" nodejs fibo2.js 2>> 4_nodejs 1>/dev/null
done
exit 0
