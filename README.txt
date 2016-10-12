Mateo Zoto
10082263
Assignment 3/CPSC 441

=============================================
How to compile:
=============================================
gcc a3.c -o a3.o
=============================================
How to configure
=============================================
To use:

./a3.o mapfile.txt homesfile.txt algorithmnumber

Where algorithmnumber is a number from 1 to 4 where 1 invokes SHP, 2 invokes SDP, 3 invokes STP, 4 invokes FTP.
Example:

./a3.o canadamap.txt canadahomes.txt 1 (for SHP)

NOTE** Dwarves are categorized in alphabetical order of their vertices.
=============================================
Results
=============================================
Shortest Hop Path (SHP)
Destination is always Bilbo's home at node B

Hobbit  Home    Hops    Dist    Time    Gold    Trolls  Path
-----------------------------------------------------------------
Balin  	 	A       		1       100     10      		3       1        AB                      
Dori   		D       		2       500     90      		15     9        DCB                     
Fili    		F       		2       200     60      		5       7        FAB                     
Gloin   	G       		1       700     30      		12     7        GB                      
Bifur   		I       		3       900     100     	30     14      IDCB                    
Kili    		K       		3       300     80      		6       10      KFAB                    
Bombur  M       		3       1000   130     	23     11      MHCB                    
Nori    		N      		4       1100   140         37     22      NIDCB                   
Oin     		O       		5       1600    190     	33     15      OJEDCB                  
Ori     		R       		4       1200    190     	33     15      RMHCB                   
Thorin  	T       		6       1900    220        34     18      TOJEDCB                 
Bofur   	U       		5       900      230     	16     18      UPKFAB                  
Dwalin  	W 	        5       1300    220        39     17      WRMHCB                  
-----------------------------------------------------------------
AVERAGE 			3.38     900.0   130.0    22.0    12.6

Shortest Distance Path (SDP)
Destination is always Bilbo's home at node B

Hobbit  Home    Hops    Dist    Time    Gold    Trolls  Path
-----------------------------------------------------------------

Balin   		A       		1       100     	10      	3       1       AB                      
Dori    		D    		    2       500     	90       15      9       DCB                     
Fili    		F 		        2       200     	60       5        7       FAB                     
Gloin   	G 	        3       400     	140     8        8       GFAB                    
Bifur   		I       		3       700     	200     17      13     IHCB                    
Kili    		K       		3       300     	80       6        10      KFAB                    
Bombur  M       		5       900     	270     14      12      MLGFAB                  
Nori    		N       		4       900     	240     24      21      NIHCB                   
Oin     		O      	 	5       1000    	250     28      23      ONIHCB                  
Ori     		R       		6       1000    	340     24      22      RQLGFAB                 
Thorin  	T       		6       1300    	280     29      26      TONIHCB                 
Bofur   	U       		5       900     	230     16      18      UPKFAB                  
Dwalin  	W       		7       1100    	370     30      24      WRQLGFAB                
-----------------------------------------------------------------
AVERAGE 			  4.00    715.4   196.9   16.8    14.9

Shortest Time Path (STP)
Destination is always Bilbo's home at node B

Hobbit  Home    Hops    Dist    Time    Gold    Trolls  Path
-----------------------------------------------------------------

Balin   		A   		    1       100      10      3      	1       AB                      
Dori    		D       		2       500      90      15   		9       DCB                     
Fili    		F       		2       200      60      5       	7       FAB                     
Gloin   	G       		1       700      30      12      	7       GB                      
Bifur   		I       		3       900      100     30      14      IDCB                    
Kili    		K       		3       300       80      6        10      KFAB                    
Bombur  M       		3       1000    130     23      11      MHCB                    
Nori    		N       		4       1100    140     37      22      NIDCB                   
Oin     		O       		5       1200    150     41      24      ONIDCB                  
Ori     		R       		4       1200    190     33      15      RMHCB                   
Thorin  	T       		6       1500    180     42      27      TONIDCB                 
Bofur   	U       		5       900      230     16      18      UPKFAB                  
Dwalin  	W       		7       2000    210     54      29      WXSNIDCB                
-----------------------------------------------------------------
AVERAGE 			3.54    892.3   123.1   24.4    14.9

Fewest Trolls Path (FTP)
Destination is always Bilbo's home at node B

Hobbit  Home    Hops    Dist    Time    Gold    Trolls  Path
-----------------------------------------------------------------

Balin   		A       		1       100      10      	3   	    1       AB                      
Dori    		D       		2       500      90      	15      	9       DCB                     
Fili    		F       		2       200      60      	5       	7       FAB                     
Gloin   	G       		1       700      30      	12      	7       GB                      
Bifur   		I       		3       700      200     	17       13      IHCB                    
Kili    		K       		3       300      80      	 6        10      KFAB                    
Bombur  M       		3       1000    130     	 23      11      MHCB                    
Nori    		N       		6       1700    200     	 37      17      NOJEDCB                 
Oin     		O       		5       1600    190     	 33      15      OJEDCB                  
Ori     		R       		4       1200    190    	 33      15      RMHCB                   
Thorin  	T       		6       1900     220     	 34      18      TOJEDCB                 
Bofur   	U       		5       900       230     	 16      18      UPKFAB                  
Dwalin  	W       		5       1300     220     	 39      17      WRMHCB                  
-----------------------------------------------------------------
AVERAGE 			3.54    930.8   142.3   	21.0    12.2
=============================================
Routing Summary
=============================================
STP and FTP both result in the same average of hops however the individual results
present are different in both. The distance on FTP, SHP and STP are all around 900 +-30
whereas on SDP that value goes down by 100. The amount of hops is the greatest on
SDP. SDP and STP both produce the same amount of average trolls encountered whereas
SHP has a very close proximity to FTP in regards to how many trolls were seen. Not
including STP, SHP has the shortest time to get to Bilbo, whereas FTP comes 2nd and SDP comes
last. STP produces the most amount of gold out of all 4 algorithms with SHP, FTP and SDP following.
Path sizes are naturally smaller on SHP as paths are determined by the vertices which is what SHP
is designed to be greedy about. All four algorithms use the same method of Dijkstra's which runs in
|E| + |V| log |V| meaning run time and the decision making on all four algorithms is the same. A pattern
amongst all four algorithms is vertices closer to the destination have a shorter path then those
further away from it, but that's something we can simply take for granted.
=============================================
Testing/What Doesnt Work
=============================================
Everything should work as expected.