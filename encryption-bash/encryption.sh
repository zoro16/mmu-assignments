#!/bin/bash

# SIMPLE KEY CIPHER AND RAIL FENCE CIPHER

#get a choice from user
echo "Please enter A to encrypt the file or B to decrypt the file : "
read choice
#user would have to enter keyword with any choices
echo "Please enter your keyword: "
read keyword
clear
echo "Your keyword is $keyword"
#get the keyword length
keywordlength=${#keyword}
#i is the counter to read all characters
i=0
#drop the duplicate keyword
while [ "$i" -lt "$keywordlength" ]; do
	temp=${keyword:i:1} 								#temp is to get current character 
	duplicated=false 									#duplicated is to compare current character to the remaining characters, 
														#the condition is always false for the current character
	((j=i+1)) #to count the next character
	while [ $j -lt "$keywordlength" ]; do 				#compare current character to all all remaining characters
		if [ "$temp" = ${keyword:j:1} ]; then
			duplicated=true
		fi
		((j++))
	done
	if [ "$duplicated" = true ]; then
		: #do nothing
	else
		key+=$temp 											#append the current character into key
	fi
	((i++))
done
echo "Your final key is $key" 								#show the final key (without duplicated)

#rearrange the plaintext with keyword
p="ABCDEFGHIJKLMNOPQRSTUVWXYZ" #plaintext
KEY=`echo $key | tr '[:lower:]' '[:upper:]'` 				#translate the key to capital letters
KEYlength=${#KEY} #get key length
plength=${#p} #get plaintext length
i=0
c+=$KEY 													  # append the capital letters key
															  # drop the key alphabets in plaintext and append to c
while [ "$i" -lt "$plength" ]; do
	temp=${p:i:1}
	duplicated=false
	j=0
	while [ "$j" -lt "$KEYlength" ]; do
		if [ "$temp" = "${KEY:j:1}" ]; then
			duplicated=true
			j=$KEYlength
    		else
      			((j++))
    		fi
	done
	if [ "$duplicated" = true ]; then
		:
	else
		c+=$temp
	fi
	((i++))
done
#user chose A to encrypt the file
#first encryption using Key Cipher
if [ "$choice" = A ] || [ "$choice" = a ]; then
	OUT=`cat $1 | tr '[:lower:]' '[:upper:]' | tr $p $c` 		 # $1 is the first argument which is a text file for this program and translate 
																 # all the text into capital letters and encrypt the text with key cipher 
	echo $OUT > $1												 # replace original text with the encrypted text
	
#second encryption using Rail Fence Cipher
	t=`cat $1` #t is to get content from the encrypted file
	z=0 #z is the counter to read all characters
	plength=${#t} #get the length of the content in the file
	space=" "
	counter=1
	flow=down
	max=4
	min=1
	while [ "$z" -lt "$plength" ]; do
		temp=${t:z:1} 											#temporarily store the current character
		if [ "$temp" = "$space" ]; then
			: 													#do nothing
		else
			if [ "$flow" = down ]; then
				case "$counter" in 								#append the current character to the particular row
					1) firstrow+=$temp;;
					2) secondrow+=$temp;;
					3) thirdrow+=$temp;;
					4) fourthrow+=$temp;;
				esac
				if [ "$counter" = "$max" ]; then
					flow=up
					((counter--))
				else
					((counter++))
				fi
			else
				case "$counter" in
        				1) firstrow+=$temp;;
        				2) secondrow+=$temp;;
        				3) thirdrow+=$temp;;
        				4) fourthrow+=$temp;;
      				esac
      				if [ "$counter" = "$min" ]; then
        				flow=down
        				((counter++))
      				else
        				((counter--))
      				fi
    			fi
  		fi
		((z++))
	done
	#combine 4 rows characters
	f+=$firstrow$secondrow$thirdrow$fourthrow
	echo $f > $1 												#replace the original text with second encrypted text
	echo "Your file has been encrypted."
	
#user chose B to decrypt the file
else if [ "$choice" = b ] || [ "$choice" = B ]; then
	q=`cat $1` #q is to get content from the file
	qlength=${#q} 												#get the text length inside the file
	x=0 														#x is the counter to read all the characters
	counter=1
	flow=down
	min=1
	max=4
	firstrow=0 
	secondrow=0
	thirdrow=0
	fourthrow=0
	while [ "$x" -lt "$qlength" ]; do
		if [ "$flow" = down ]; then
			case "$counter" in
		#to know how many alphabets should be at row1/row2/row3/row4
			1) ((firstrow++));;
			2) ((secondrow++));;
			3) ((thirdrow++));;
			4) ((fourthrow++));;
			esac
			if [ "$counter" = "$max" ]; then
				flow=up
				((counter--))
			else
				((counter++))
			fi
		else
			case "$counter" in
        		1) ((firstrow++));;
        		2) ((secondrow++));;
        		3) ((thirdrow++));;
        		4) ((fourthrow++));;
      			esac
      			if [ "$counter" = "$min" ]; then
        			flow=down
        			((counter++))
      			else
        			((counter--))
      			fi
    		fi
	((x++))
	done
	#get the content for particular row
	row1=${q:0:firstrow}
	row2=${q:((0+firstrow)):secondrow}
	row3=${q:((0+firstrow+secondrow)):thirdrow}
	row4=${q:((0+firstrow+secondrow+thirdrow)):fourthrow}

	#rearrange the alphabets
	flow2=down
	y=0 #y 
	k=0
	counter2=1
	while [ "$y" -lt "$qlength" ]; do
		if [ "$flow2" = down ]; then
			case "$counter2" in
			1)temp2+=${row1:k:1};;
			2)temp2+=${row2:k:1};;
			3)temp2+=${row3:k:1};;
			4)temp2+=${row4:k:1};;
			esac
			if [ "$counter2" = "$max" ]; then
				flow2=up
        			((counter2--))
				((k++))
      			else
        			((counter2++))
      			fi
    		else
      			case "$counter2" in
                        1)temp2+=${row1:k:1};;
                        2)temp2+=${row2:k:1};;
                        3)temp2+=${row3:k:1};;
                        4)temp2+=${row4:k:1};;
                        esac
      			if [ "$counter2" = "$min" ]; then
        			flow2=down
        			((counter2++))
				((k++))
      			else
        			((counter2--))
      			fi
    		fi
  	((y++))
	done
	#decrypt using Key Cipher
	OUT=`echo $temp2 | tr '[:lower:]' '[:upper:]' | tr $c $p`
        echo $OUT > $1
	echo "Your file has been decrypted."
else
	#choice must be a/A or b/B
	echo "Your choice is incorrect."
fi
fi
