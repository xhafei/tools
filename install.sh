# do a command until sucess
#!/bin/sh
ac=$1
echo $ac
while true
do
$ac
if [ $? -eq 0 ]
then
echo 'every thing done!~~~'
break
fi
sleep 1
done
