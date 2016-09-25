# README #

##Info##

This is an implementation of the Pool Adjacent Violators Algorithm (PAV algorithm or PAVA) for isotonic regression 
(with all intial weights equal to one) such as detailed here:  
http://stat.wikia.com/wiki/Isotonic_regression  
https://en.wikipedia.org/wiki/Isotonic_regression

##To compile##

gcc pava.c -o pava -O3


##To execute##

./pava val.txt res.txt  
val.txt should contain the values to fit with isotonic regression separated by any white space.  
Will print the result in res.txt "n v" on each line.  
"n" is the number of values equal to "v".

##Initial contributors##

Maximilien Danisch  
January 2016  
http://bit.ly/maxdan94  
maximilien.danisch@telecom-paristech.fr
