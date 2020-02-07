#!/bin/sh
 
intputFile="temp.txt";
i=0;
j=1;
temp=0;
#nfTemp=$(awk '{print NF}' sendData.txt);

#printf ' \n\n2b 2b 2b 52 6f 6d 3a 01 00 00 00 00 '
#for (( i=0; i<$nfTemp/10000; i++ ))  
#do  	   
	   #temp=$i+1;
	   #temp="$1"
        #echo -n $((temp))' '
	   #awk '{print $i   }' sendData.txt
	   
	   #a="awk "
	   #b="'{print $"
	   #c="   }' sendData.txt";
	   #commend=$a$b$((temp))$c
	   
	   #commend='awk ''{print  $'$((temp))''  }' /s/Users/USER/Documents/CASE/test/FlashWR2/sendData.txt'
	   #printf '\n\n%s \n\n' $commend
	   #echo 	   $commend
	   #$commend
		
	   #if [ $((i%10)) == 0 ] && [ $i != 0 ];then
		#printf ' \n\n2b 2b 2b 52 6f 6d 3a 01 %2x %2x %2x %2x ' $(((j>>24)&0xff)) $(((j>>16)&0xff)) $(((j>>8)&0xff)) $((j&0xff))
		#j=$(($((j))+1));
	   #fi
	   
	   #awk -F"|" 'BEGIN{sum=0}{sum=sum+$('$i')}END{printf("%d\n", sum)}' sendData.txt
#done  

awk -F"," '{
	   pageSize=1024;
	   j=0;
        for(i=0;i<NF;i++) 
	   {
			if ( ((i%pageSize) == 0) || i==0)
			{
		        printf " \n\n2b 2b 2b 52 6f 6d 3a 01 %2x %2x %2x %2x " ,and(rshift(j,24),0xff),and(rshift(j,16),0xff),and(rshift(j,8),0xff),and(j,0xff);
		        j++;
	          }
			  
			printf $(i+1)" "
        }
}' $intputFile

  
