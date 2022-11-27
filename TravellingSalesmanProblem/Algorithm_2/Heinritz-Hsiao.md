Heinritz-Hsiao algorithm is a more effective algorithm.
According to this algorithm in order to select the next city in the route, you find the closest unvisited city from the current city. If you have visited all the cities
you add the distance between current city and initial city to the total distance. 

At the task_3 we implement a serial version of the algorithm.

At the task_4 we make a change to the algorithm. In order to select the next city in the route, you don't select the closest unvisited city but the second closest 
unvisted city.

At task 5 we implement a parallleized version of task 4.
