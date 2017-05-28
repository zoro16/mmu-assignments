### To compile all the files:
    * make

### to run the files
    * mpirun -np 1 serial
    * mpirun -np 2 dual

    * to run on cluster
        - copy the compiled "clust" file to all the salve machines
            $scp clust tsn3151@10.106.47.xxx
        - use $ifconfig to get the ip address from each node in the cluster.
        - add the ip address to hostfile
        - run the program on the cluster

        mpirun --hostfile hostfile -np 4 clust
