#!/bin/bash

#declare global variables
#declare the ref array to save user inputs
declare -a ref[max]
declare -a frame[min]
declare -i count
declare -i n
declare -i nber
declare -i temp
declare -i i
declare -i ch
declare -i counter

#INPUT FUNCTION 
#get sequence input from the user and save it inside the ref array
input() {
    count=0
    read -p "Enter the number of page frames: " n
    read -p "Enter the total reference string: " nber
    echo "Please Enter the values.."
    for (( i=0; i<nber; i++ ))
    do
        count=$(($count+1))
        read ref[$count]
    done
    
}


#FIFO FUNCTION

fifo() {
    declare -i i=0
    declare -i i=0
    declare -i fault=0

    for ((i=0;i<n;i++))
    do
        #set the empty frames to -1 
        frame[$i]=-1
    done
    echo " total" $count
    for ((i=1;i<=$count;i++))
    do
        for ((j=0;j<n;j++))
        do
            #check if the value inside the current frame is similar to the new sequence
            if [[ ${frame[$j]} -eq ${ref[$i]} ]]
            then
                break
            fi
        done
        if [[ $j -eq $n ]]
        then   
            frame[$(($fault%$n))]=${ref[$i]}
            #increase the fault counter
            fault=$(($fault+1))
        fi
        printf "\n\nAfter inserting ${ref[$i]} :"
        for ((j=0;j<n;j++))
        do
            printf " "${frame[$j]}
        done
    done
    echo " "
    echo "End of the reference string"
    echo "Total Page Fault is " $fault
}


#LRU FUNCTION

lruok() {
    #check the frame size and redirect the user to the exact lru function
    read -p "Enter the frame size : " fz
    if [[ $fz -eq 3 ]]
    then
        lru3
    elif [[ $fz -eq 4 ]]
    then
        lru4
    elif [[ $fz -eq 5 ]]
    then
        lru5
        
    fi
    
}


lru3() {
    #set the value of the frames to -1 to indicate that it is empty
    declare -i a frame=(-1 -1 -1)
    declare -i a used=(-1 -1 -1)
    declare -i a ref[20]
    declare -i i
    declare -i flag
    declare -i j
    #length of the reference string         
    declare -i no
    declare -i index
    declare -i value
    declare -i hitcnt=0
    declare -i fault
    #get the length of the reference string from the user  
    read -p "Enter length of reference string : " no
    echo "Enter the reference string values.."  
    for (( i=0; i<no; i++ ))
    do
        read ref[$i]
    done

    for ((i=0;i<no;i++))
    do
        flag=0
        for ((j=0;j<fz;j++))
        do
	    #check if the value of the frame is equal the coming sequence
            if [[ ${frame[$j]} -eq ${ref[$i]} ]]
            then
		#print N if yes
                printf "\n\tN "
                hitcnt=$(($hitcnt+1))
                flag=1
                used[$j]=$cnt
                break
            fi
        done
        if [[ $flag -eq 0 ]]
        then
	    #print y if different
            printf "\n\tY"
            printf "\tBefore :\t"

            for ((j=0;j<fz;j++))
            do          
                printf " %d" ${frame[$j]}
            done
            index=0
            #  fault=0
            value=${used[0]}
            fault=$(($fault+1))
            if [[ $cnt -ne 0 ]]
            then
                for ((j=0;j<fz;j++))
                do         
                    if [[ $value -gt ${used[$j]} ]] && [[ $value -ne ${used[$j]} ]]
                    then
                        index=$j
                        value=${used[$j]}
                    fi
                done
            fi
            
            frame[$index]=${ref[$i]}
            used[$index]=$cnt
            printf "\tAfter :"
            for ((j=0;j<fz;j++))
            do
                printf " %d" ${frame[$j]}
            done

            
        fi
        
        cnt=$(($cnt+1))
    done
    echo " "
    echo "Page fault numbers: " $fault
}

#check LRU 3 comments for the next LRU functions
#####################################################################################
lru4() {
    declare -i a frame=(-1 -1 -1 -1)
    declare -i a used=(-1 -1 -1 -1)
    declare -i a ref[20]
    declare -i i
    declare -i flag
    declare -i j
    declare -i no
    declare -i index
    declare -i value
    declare -i hitcnt=0
    declare -i ratio
    declare -i fault
    read -p "Enter length of reference string : " no
    echo "Enter the reference string values.." 
    for (( i=0; i<no; i++ ))
    do
        read ref[$i]
    done

    for ((i=0;i<no;i++))
    do
        flag=0
        for ((j=0;j<fz;j++))
        do

            if [[ ${frame[$j]} -eq ${ref[$i]} ]]
            then
                printf "\n\tN "
                hitcnt=$(($hitcnt+1))
                flag=1
                used[$j]=$cnt
                break
            fi
        done
        if [[ $flag -eq 0 ]]
        then
            printf "\n\tY"
            printf "\tBefore :\t"

            for ((j=0;j<fz;j++))
            do          
                printf " %d" ${frame[$j]}
            done
            index=0
            value=${used[0]}
            fault=$(($fault+1))
            if [[ $cnt -ne 0 ]]
            then
                for ((j=0;j<fz;j++))
                do         
                    if [[ $value -gt ${used[$j]} ]] && [[ $value -ne ${used[$j]} ]]
                    then
                        index=$j
                        value=${used[$j]}
                    fi
                done
            fi
            
            frame[$index]=${ref[$i]}
            used[$index]=$cnt
            printf "\tAfter :"
            for ((j=0;j<fz;j++))
            do
                printf " %d" ${frame[$j]}
            done

            
        fi
        
        cnt=$(($cnt+1))
    done
    echo " "
    echo "Page fault numbers: " $fault
}
########################################################################################

lru5() {
    declare -i a frame=(-1 -1 -1 -1 -1)
    declare -i a used=(-1 -1 -1 -1 -1)
    declare -i a ref[20]
    declare -i i
    declare -i flag
    declare -i j
    declare -i no
    declare -i index
    declare -i value
    declare -i hitcnt=0
    declare -i ratio
    declare -i fault
    read -p "Enter length of reference string : " no
    echo "Enter the reference string values...." 
    for (( i=0; i<no; i++ ))
    do
        read ref[$i]
    done

    for ((i=0;i<no;i++))
    do
        flag=0
        for ((j=0;j<fz;j++))
        do

            if [[ ${frame[$j]} -eq ${ref[$i]} ]]
            then
                printf "\n\tN "
                hitcnt=$(($hitcnt+1))
                flag=1
                used[$j]=$cnt
                break
            fi
        done
        if [[ $flag -eq 0 ]]
        then
            printf "\n\tY"
            printf "\tBefore :\t"

            for ((j=0;j<fz;j++))
            do          
                printf " %d" ${frame[$j]}
            done
            index=0
            value=${used[0]}
            fault=$(($fault+1))
            if [[ $cnt -ne 0 ]]
            then
                for ((j=0;j<fz;j++))
                do         
                    if [[ $value -gt ${used[$j]} ]] && [[ $value -ne ${used[$j]} ]]
                    then
                        index=$j
                        value=${used[$j]}
                    fi
                done
            fi
            
            frame[$index]=${ref[$i]}
            used[$index]=$cnt
            printf "\tAfter :"
            for ((j=0;j<fz;j++))
            do
                printf " %d" ${frame[$j]}
            done

            
        fi
        
        cnt=$(($cnt+1))
    done
    echo " "
    echo "Page fault numbers: " $fault
}


#OPTIMAL FUNCTION
optimalok() {
    declare -i a frame=(-1 -1 -1)
    declare -i a used=(-1 -1 -1)
    declare -i a ref[20]
    declare -i i
    declare -i cnt=0
    declare -i fz
    declare -i flag
    declare -i j
    declare -i no
    declare -i index
    declare -i val1
    declare -i val2
    declare -i val3
    declare -i fault
    read -p "Enter length of reference string : " no
    echo "Enter the reference string values...."   
    for (( i=0; i<no; i++ ))
    do
        read ref[$i]
    done

    for ((i=0;i<no;i++))
    do
        flag=0
        for ((j=0;j<3;j++))
        do

            if [[ ${frame[$j]} -eq ${ref[$i]} ]]
            then
                flag=1
                printf "\n\tN"
                hitcnt=$(($hitcnt+1))
                break
            fi
        done

        if [[ $flag -eq 0 ]]
        then
            fault=$(($fault+1))
            printf "\n\tY"
            if [[ $cnt -lt 3 ]]
            then
                frame[$cnt]=${ref[$i]}
                printf "\tStatus :"
                for ((j=0;j<3;j++))
                do

                    printf " "${frame[$j]}
                done
                cnt=$(($cnt+1))   
            else
                printf "\tBefore :"
                for ((j=0;j<3;j++))
                do   
                    printf " "${frame[$j]}
                done
                val1=${frame[0]}
                flag=0
                for ((j=i;j<no;j++))
                do
                    if [[ ${ref[$j]} -eq $val1 ]]
                    then
                        val1=$j
                        flag=1
                        break
                    fi
                done
                
                if [[ $flag -eq 0 ]]
                then
                    val1=$no
                fi
                val2=${frame[1]}
                flag=0
                for ((j=i;j<no;j++))
                do
                    if [[ ${ref[$j]} -eq $val2 ]]
                    then
                        val2=$j
                        flag=1
                        break
                    fi
                done

                if [[ $flag -eq 0 ]]
                then
                    val2=$no
                fi
                val3=${frame[2]}
                flag=0
                for ((j=i;j<no;j++))
                do
                    if [[ ${ref[$j]} -eq $val3 ]]
                    then
                        val3=$j
                        flag=1
                        break
                    fi
                done
                if [[ $flag -eq 0 ]]
                then
                    val3=$no
                fi
                

                if [[ $val1 -lt $val2 ]]
                then
                    if [[ $val3 -lt $val2 ]]
                    then
                        index=1
                    else
                        index=2
                    fi
                else

                    if [[ $val3 -lt $val1 ]]
                    then
                        index=0
                    else
                        index=2
                    fi fi   
                frame[$index]=${ref[$i]}
            fi
            printf "  After:"
            for ((j=0;j<3;j++))
            do
                printf " "${frame[$j]}
            done
        fi
    done
    echo " "
    echo "    Total Page Fault is " $fault
    echo " "
    echo " "    
}


echo " "

# menu function
while [[ $ch -ne 4 ]]
do
    echo " "
    echo " Paging Algorithm Simulation" 
    echo " Please enter the number to select:"
    echo " 1) FIFO"
    echo " 2) LRU"
    echo " 3) LFU"
    echo " 4) Exit"
    echo " "
    read -p " Please Enter Choice: " ch
    
    if [[ $ch -eq 1 ]]
    then
        input
        fifo   
    elif [[ $ch -eq 2 ]]
    then
        lruok
    elif [[ $ch -eq 3 ]]
    then
        optimalok   
    elif [[ $ch -eq 4 ]]
    then
        exit 1   
    else
        echo "Wrong Input"
    fi
done

